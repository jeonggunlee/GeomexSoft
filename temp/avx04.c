#include <stdio.h>
#include <xmmintrin.h>
#include <immintrin.h>
#include <time.h>

int main()
{
    float a[8] __attribute__((aligned(32))) = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    float b[8] __attribute__((aligned(32))) = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8};    
    float vecCon[8] __attribute__((aligned(32)));

    __m256 acc_a = _mm256_load_ps(a);
    __m256 acc_b = _mm256_load_ps(b);

    __m256 acc = _mm256_hadd_ps(acc_a, acc_b);
    _mm256_store_ps(vecCon, acc);
    printf("1: %f, %f, %f, %f, %f, %f, %f, %f \n", vecCon[0], vecCon[1], vecCon[2], vecCon[3], vecCon[4], vecCon[5], vecCon[6], vecCon[7]);

}