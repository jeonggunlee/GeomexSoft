#include<stdafx.h>
#include<stdio.h>
#include<time.h>
#include<omp.h>
#include<windows.h> 

int main(int argc, char* argv[])
{
	omp_set_num_threads(4);
	clock_t startTime = clock();

#pragma omp parallel 
	{
		int threadCount = omp_get_num_threads();
#pragma omp for schedule(static)
		for (int i = 0; i < threadCount * 5; i++)
		{
			Sleep(i * 100);
			printf("Thread Num: %d, counter = %i\n", omp_get_thread_num(), i);
		}
		printf("Thread Num: %d, Finished\n", omp_get_thread_num());
	}
	printf("Elpase Time: %d\n", clock() - startTime);
}
