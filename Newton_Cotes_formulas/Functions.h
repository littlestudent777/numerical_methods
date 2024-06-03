#ifndef LAB_H
#define LAB_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <float.h>

typedef struct error {
	double res;
	int it;
}Error_t;

// what was in S1 and S2 in previous iteration, stays in S1 and S2 in the new one
typedef struct sums {
	double S1;
	double S2;
}PartialSums_t;

double MyFunc(double x);

//function to do research and write data to the files
void ErrAndItFromEps(double (*func)(double), int maxN);
void ErrFromLen(double (*func)(double), int maxN);

//comparing results from the different length given
Error_t ResComparison(double (*func)(double), double eps, int maxN);

//method
double CubicParabolas(double (*func)(double), int n, PartialSums_t *current_sum);

//various help functions
void CheckFopen(FILE* DATA);
void CheckFclose(FILE* DATA);

#endif