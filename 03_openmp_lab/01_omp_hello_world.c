#include<stdafx.h>
#include<stdio.h>
#include<time.h>
#include<omp.h>
#include<windows.h> 

int main()
{
	#pragma omp parallel
	{
		printf("Hello World !\n");
	}
}
