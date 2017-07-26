#include<stdafx.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>

const long int N = 10000000;
void main()
{  
	int i, k=10;
	int *A, *B, *C;

	A = (int *)malloc(N*sizeof(int));
	B = (int *)malloc(N*sizeof(int));
	C = (int *)malloc(N*sizeof(int));

	clock_t startTime = clock();

	//#pragma omp parallel for
	for (i = 0; i<N; i++) {
		A[i] = B[i] + k*C[i];
	}
	printf("Elpase Time: %d\n", clock() - startTime);

}
