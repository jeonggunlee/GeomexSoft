// vec1.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <immintrin.h>
#include <time.h>

#define MAX 5000000*2


__m256 va[MAX];
__m256 vb[MAX];

void main() {

    int ctr, i;

    clock_t startTime = clock();

    for (ctr = 0; ctr<1000; ctr++) {
        for (i = 0; i<MAX; i++) {
            va[i] = _mm256_add_ps(va[i], vb[i]);
        }
    }
    printf("Elapase Time : %ld\n", clock() - startTime);
}


// double va[4 * MAX];
// double vb[4 * MAX];

// void main() {
// int i, ctr;

// clock_t startTime = clock();

// for (ctr = 0; ctr<1000; ctr++) {
//     for (i = 0; i<4 * MAX; i++) {
//         va[i] = va[i] + vb[i];
// }
// }
// printf("Elapase Time : %ld\n", clock() - startTime);

// }
