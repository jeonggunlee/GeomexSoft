#include <stdio.h>
#include <xmmintrin.h>
#include <immintrin.h>
#include <time.h>

void avx_matvec(float* x, float* y, float* z, size_t n){
	__m256 a, b;
	// float* vecCon = (float*)_mm_malloc(8 * sizeof(float), 32);
    float vecCon[8] __attribute__((aligned(32)));

	for (size_t i = 0; i < n; i ++){
		// Sets all the elements of a float32 vector to zero and returns the float32 vector.
		__m256 acc = _mm256_setzero_ps();

		for (size_t j = 0; j < n; j += 8){
			a = _mm256_load_ps(x + n*i + j);
			b = _mm256_load_ps(y + j);
			acc = _mm256_add_ps(acc, _mm256_mul_ps(a, b));
			// acc = _mm256_fmadd_ps(a, b, acc);
		}

		acc = _mm256_hadd_ps(acc, acc);
        //_mm256_store_ps(vecCon, acc);
        //printf("1: %f, %f, %f, %f, %f, %f, %f, %f \n", vecCon[0], vecCon[1], vecCon[2], vecCon[3], vecCon[4], vecCon[5], vecCon[6], vecCon[7]);

		acc = _mm256_hadd_ps(acc, acc);
        // _mm256_store_ps(vecCon, acc);
        // printf("2: %f, %f, %f, %f, %f, %f, %f, %f \n", vecCon[0], vecCon[1], vecCon[2], vecCon[3], vecCon[4], vecCon[5], vecCon[6], vecCon[7]);

		acc = _mm256_hadd_ps(acc, acc);
        // _mm256_store_ps(vecCon, acc);
        // printf("3: %f, %f, %f, %f, %f, %f, %f, %f \n", vecCon[0], vecCon[1], vecCon[2], vecCon[3], vecCon[4], vecCon[5], vecCon[6], vecCon[7]);

		_mm256_store_ps(vecCon, acc);
		z[i] = vecCon[0];
	}
}


int main(){

	size_t n = 8192;
	// sse requires 32 bytes aligned memory
	float* x = (float*)_mm_malloc(n*n*sizeof(float), 32);
	float* y = (float*)_mm_malloc(n*sizeof(float), 32);
	float* z = (float*)_mm_malloc(n*sizeof(float), 32);

	for (size_t i = 0; i < n; ++i){
		for (size_t j = 0; j < n; ++j)
			x[n*i + j] = i*0.45;
		y[i] = 1 + i*0.76;
		z[i] = 0.;
	}

	clock_t start = clock();
	for (size_t i = 0; i < n; ++i) {
		z[i] = 0.0;
		for (size_t j = 0; j < n; ++j)
			z[i] += x[n*i + j] * y[j];
	}
	clock_t elapse = clock() - start;
	printf("w/o AVX Time: %ld\n", elapse);

    for(size_t i = n-10; i < n; ++i)
        printf(" %f ", z[i]);
    printf("\n");

    // AVX Matrix Vector 
    start = clock();

    avx_matvec(x,y,z,n);

    elapse = clock() - start;
	printf("AVX Time: %ld\n", elapse);

    for(size_t i = n-10; i < n; ++i)
        printf(" %f ", z[i]);
    printf("\n");

    _mm_free(x);
    _mm_free(y);
    _mm_free(z);

    return 0;
}