#include <stdio.h>
#include <xmmintrin.h>
#include <immintrin.h>
#include <time.h>

void avx_add(float* x, float* y, float* z, size_t n){
	__m256 a, b;

	for (size_t i = 0; i < n; i += 8){
		a = _mm256_load_ps(x + i);
		b = _mm256_load_ps(y + i);
		b = _mm256_add_ps(a, b);
		_mm256_store_ps(z + i, b);
	}

	// operate on remaining data
	for (size_t i = n - n % 8; i < n; ++i)
		z[i] = x[i] + y[i];
}

int main(){

	size_t n = 12800000;

	// avx requires 32 bytes aligned memory
	float* x = (float*)_mm_malloc(n*sizeof(float), 32);
	float* y = (float*)_mm_malloc(n*sizeof(float), 32);
	float* z = (float*)_mm_malloc(n*sizeof(float), 32);

	for (size_t i = 0; i < n; ++i){
		x[i] = i*0.45;
		y[i] = 1 + i*0.76;
		z[i] = 0.;
	}

	clock_t start = clock();
	avx_add(x, y, z, n);
	clock_t elapse = clock() - start;
	printf("AVX Time: %ld\n", elapse);

	start = clock();
	for (size_t i = 0; i < n; ++i){
		z[i] = x[i] + y[i];
	}
    elapse = clock() - start;
	printf("w/o AVX Time: %ld\n", elapse);

	_mm_free(x);
	_mm_free(y);
	_mm_free(z);

	return 0;
}