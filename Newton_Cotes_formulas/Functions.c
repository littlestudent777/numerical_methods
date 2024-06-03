#include "Functions.h"
#pragma warning(disable : 4996)
#define A 0.0
#define B 3.0
#define COEF 3.0/8

double MyFunc(double x) {
	return pow(x, 5) - 8.2 * pow(x, 3) + 4.5 * x * x - 7 * x;
}

Error_t ResComparison(double (*func)(double), double eps, int maxN) {
	double current_err, newS, prevS = DBL_MAX;
	Error_t err;
	err.it = 0;
	PartialSums_t sum = { 0, 0 }; // S1 = 0, S2 = 0
	for (int N = 3; N < maxN; N *= 2) {
		err.it++;
		newS = CubicParabolas(func, N, &sum);
		//Runge's rule, m = 4
		current_err = fabs(newS - prevS)/15.0;
		if (current_err < eps) {
			err.res = newS;
			break;
		}
		prevS = newS;
	}
	return err;
}

double CubicParabolas(double (*func)(double), int n, PartialSums_t *current_sum) {
	double length = (B - A) / n;
	double x2, x3;
	if (n == 3) {
		x2 = A + length;
		x3 = x2 + length;
		current_sum->S1 += func(A);
		current_sum->S1 += func(B);
		current_sum->S2 += func(x2);
		current_sum->S2 += func(x3);
	}

	else {
	/*Every segment contains four points, the first point was already counted.
	It was counted above or in the even segment as x4 */
		double x4;
		x3 = A - length; //that seems bad, but it's for first loop to work 
		double f_x1, f_x4;
		double double_length = 2 * length;
		//loop for the segments:
		for (int segment = 0; segment < n / 3; segment++) {
			if (segment % 2 == 0) {
				x2 = x3 + double_length;
				x4 = x2 + double_length;
				current_sum->S2 += func(x2);
				f_x4 = func(x4);
				current_sum->S1 += f_x4;
			}
			else {
				f_x1 = f_x4;
				current_sum->S1 += f_x1;
				x3 = x4 + double_length;
				current_sum->S2 += func(x3);
			}
		}
	}
	return COEF * length * (3 * current_sum->S2 + current_sum->S1);
}

void ErrAndItFromEps(double (*func)(double), int maxN) {
	FILE* ERR = fopen("err_from_eps.txt", "w");
	FILE* EPS = fopen("it_from_eps.txt", "w");
	CheckFopen(ERR);
	CheckFopen(EPS);

	double eps = 0.1;
	for (int i = 1; i <= 10; i++) {
		Error_t err = ResComparison(func, eps, maxN);
		//fprintf(ERR, "%e, %.15lf, %d\n", pow(10, -i), err.res, err.N);
		fprintf(ERR, "%e, %.15lf\n", pow(10, -i), err.res);
		fprintf(EPS, "%e, %d\n", pow(10, -i), err.it);
		eps *= 0.1;
	}

	fclose(ERR);
	fclose(EPS);
	CheckFclose(ERR);
	CheckFclose(EPS);
}

void ErrFromLen(double (*func)(double), int maxN) {
	FILE* ERR = fopen("err_from_len.txt", "w");
	CheckFopen(ERR);
	PartialSums_t sum = { 0, 0 }; // S1 = 0, S2 = 0
	double newS, prevS = 0;
	for (int N = 3; N < maxN; N *= 2) {
		newS = CubicParabolas(func, N, &sum);
		fprintf(ERR, "%e, %.15lf\n", (B - A) / N, newS);
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