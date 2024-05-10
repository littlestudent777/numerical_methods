#ifndef LAB_H
#define LAB_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

typedef struct error {
	double res;
	int N;
	double h;
}Error_t;

double Func(double x);

//function to do research and write data to the files
void ErrAndItFromEps();
void ErrFromLen();

//comparing results from the different length given
Error_t ResComparison(double eps);

//method
double CubicParabolas(int n);
//counting method for the first segmentation
double CubicParabolasInit(double length);
//counting method for other segmentations
double CountCubicParabolas(int n, double length);
/*they are separated for the efficient use of time resources*/

//various help functions
void CheckFopen(FILE* DATA);
void CheckFclose(FILE* DATA);

#endif