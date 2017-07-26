#include<stdafx.h>
#include<stdio.h>
#include<time.h>
#include<omp.h>
#include<windows.h> 

int main(int argc, char* argv[])
{
	double pi = 0.0;
	const int iterationCount = 200000000;

	clock_t startTime = clock();
	/*
	for (int i = 0; i < iterationCount; i++)
	{
		pi += 4 * (i % 2 ? -1 : 1) / (2.0 * i + 1.0);
	}
	*/
	
	#pragma omp parallel
	{
		double temp = 0.0;

		#pragma omp for
		for (int i = 0; i < iterationCount; i++)
		{
			//#pragma omp atomic
			//pi += 4 * (i % 2 ? -1 : 1) / (2.0 * i + 1.0);
			temp += 4 * (i % 2 ? -1 : 1) / (2.0 * i + 1.0);
		}

		#pragma omp atomic
		pi += temp;

	}	
	
	printf("Elpase Time : %d\n", clock() - startTime);
	printf("pi = %.8f\n", pi);

}
