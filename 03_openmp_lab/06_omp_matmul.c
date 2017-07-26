#include<stdafx.h>
#include<stdio.h>
#include<time.h>
#include<omp.h>
#include<windows.h> 

/* matrix.cpp */
const int size = 1000;

float a[size][size];
float b[size][size];
float c[size][size];

int main()
{
	double wtime;

	// Initialize buffers.
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			a[i][j] = (float)i + j;
			b[i][j] = (float)i - j;
			c[i][j] = 0.0f;
		}
	}

	wtime = omp_get_wtime();
	// Compute matrix multiplication.
	// C <- C + A x B
	// #pragma omp parallel for shared(a,b,c)
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			for (int k = 0; k < size; ++k) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	wtime = omp_get_wtime() - wtime;
	printf("  Elapsed seconds = %g\n", wtime);

	printf("C[size-1][size-1] = %f\n", c[size-1][size-1]);

	return 0;
}
