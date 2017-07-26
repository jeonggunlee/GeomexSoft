#include<stdafx.h>
#include<stdio.h>
#include<omp.h>

double pooh(int id, double *A)
{
	printf("In thread id[%d]\n", id);

	return A[id];
}

void main()
{
	double A[1000];
	
	omp_set_num_threads(4); // API
	#pragma omp parallel
	{
		int ID = omp_get_thread_num();
		pooh(ID, A);
	}
	printf("all done\n");
}
