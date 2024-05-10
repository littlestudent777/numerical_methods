#include "Functions.h"
#pragma warning(disable : 4996)
#define A 0.0
#define B 3.0

double Func(double x) {
	return pow(x, 5) - 8.2 * pow(x, 3) + 4.5 * x * x - 7 * x;
}

int it;

/*we make them global to save results from previous iterations
because what was in S1 and S2 in previous iteration, stays in S1 and S2 in the new one*/
double S1, S2;

Error_t ResComparison(double eps) {
	double current_err, newS, prevS = 0;
	Error_t err;
	for (int N = 3; N < 5000; N *= 2) {
		it++;
		newS = CubicParabolas(N);
		//Runge's rule, m = 4
		current_err = fabs(newS - prevS)/15.0;
		if (current_err < eps) {
			err.res = newS;
			err.N = N;
			err.h = (B - A) / N;
			break;
		}
		prevS = newS;
	}
	return err;
}

double CubicParabolas(int n) {
	double length = (B - A) / n;
	if (n == 3) {
		return CubicParabolasInit(length);
	}
	else {
		return CountCubicParabolas(n, length);
	}
}

double CubicParabolasInit(double length) {
	//integral = 3/8*h (s1 + 3s2 + 3s3 + s4)
	//the coefficients before s1 and s4; s2 and s3 are the same -> we can count it together
	//integral = 3/8*h (S1 + 3S2); S1 = s1 + s4; S2 = s2 + s3
	double x1, x2, x3, x4;
	x1 = A;
	x2 = A + length;
	x3 = A + 2 * length;
	x4 = B;
	S1 += Func(x1);
	S1 += Func(x4);
	S2 += Func(x2);
	S2 += Func(x3);
	return 3 * length * (3 * S2 + S1) / 8.0;
}

double CountCubicParabolas(int n, double length) {
	/*Every segment contains four points, the first point was counted in the previous iteration.
	It was counted in the Init function or in the even segment as x4 */
	double x2, x3, x4;
	double f_x1, f_x4;
	//loop for the segments:
	for (int segment = 0; segment < n / 3; segment++) {
		if (segment % 2 == 0) {
			x2 = A + (3 * segment + 1) * length;
			x4 = A + 3 * (segment + 1) * length;
			S2 += Func(x2);
			f_x4 = Func(x4);
			S1 += f_x4;
		}
		else {
			f_x1 = f_x4;
			S1 += f_x1;
			x3 = A + (3 * segment + 2) * length;
			S2 += Func(x3);
		}
	}
	return 3 * length * (3 * S2 + S1) / 8.0;
}

void ErrAndItFromEps() {
	FILE* ERR = fopen("err_from_eps.txt", "w");
	FILE* EPS = fopen("it_from_eps.txt", "w");
	CheckFopen(ERR);
	CheckFopen(EPS);

	double eps = 0.1;
	for (int i = 1; i <= 10; i++) {
		it = 0;
		S1 = 0;
		S2 = 0;
		Error_t err = ResComparison(eps);
		fprintf(ERR, "%e, %.15lf, %d\n", pow(10, -i), err.res, err.N);
		fprintf(EPS, "%.15lf, %d\n", pow(10, -i), it);
		eps *= 0.1;
	}

	fclose(ERR);
	fclose(EPS);
	CheckFclose(ERR);
	CheckFclose(EPS);
}

void ErrFromLen() {
	FILE* ERR = fopen("err_from_len.txt", "w");
	CheckFopen(ERR);
	S1 = 0;
	S2 = 0;
	double newS, prevS = 0;
	for (int N = 3; N < 2000; N *= 2) {
		newS = CubicParabolas(N);
		fprintf(ERR, "%e, %.15lf, %d\n", (B - A) / N, newS, N);
	}
	fclose(ERR);
	CheckFclose(ERR);
}

void CheckFopen(FILE* DATA) {
	if (!DATA) {
		printf("Error opening file\n");
		exit(1);
	}
}

void CheckFclose(FILE* DATA) {
	if (DATA == EOF) {
		printf("Error closing file\n");
		exit(1);
	}
}