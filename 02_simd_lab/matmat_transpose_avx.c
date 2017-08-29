// Tested on a Linux
// Much higher performance when compared with the version without pre-transpose.

#include <iostream>
#include <xmmintrin.h>
#include <immintrin.h>
#include <chrono>

void avx_matmat(float* x, float* y, float* z, size_t n){
	__m256 a, b;
	float* vecCon = (float*)_mm_malloc(8 * sizeof(float), 32);
	float	temp;

	// Transpose MATRIX Y
	for (size_t i = 0; i < n; i++)
		for(size_t j = i+1; j < n; j++) {
			temp = y[n*i + j];
			y[n*i + j] = y[i + n*j];
			y[i + n*j] = temp;
		}

	for (size_t i = 0; i < n; i++){
		for (size_t j = 0; j < n; j++){
			// Sets all the elements of a float32 vec to zero and returns the float32 vec
			__m256 acc = _mm256_setzero_ps();

			for (size_t k = 0; k < n; k += 8){
				a = _mm256_load_ps(x + n*i + k);
				b = _mm256_load_ps(y + n*j + k);
				acc = _mm256_add_ps(acc, _mm256_mul_ps(a, b));
				//acc = _mm256_fmadd_ps(a, b, acc);
			}
			acc = _mm256_hadd_ps(acc, acc);
			acc = _mm256_hadd_ps(acc, acc);
			acc = _mm256_hadd_ps(acc, acc);

			_mm256_store_ps(vecCon, acc);
			z[n*i + j] = vecCon[0];
		}  // for j
	}  // for i
}


int main(){

	size_t n = 1024;
	// sse requires 32 bytes aligned memory
	float* x = (float*)_mm_malloc(n*n*sizeof(float), 32);
	float* y = (float*)_mm_malloc(n*n*sizeof(float), 32);
	float* z = (float*)_mm_malloc(n*n*sizeof(float), 32);

	for (size_t i = 0; i < n; ++i){
		for (size_t j = 0; j < n; ++j) {
			x[n*i + j] = 2.0 + i*1.0;
			y[n*i + j] = 1.0*j + 1.0;
			z[n*i + j] = 0.0;
		}
	}
	/*
	std::cout << "MATRIX A ___" << std::endl;
	for(size_t i = 0; i < n; ++i) {
	for(size_t j = 0; j < n; ++j)
	std::cout << x[n*i+j] << "  ";
	std::cout << std::endl;
	}
	std::cout << "MATRIX B ___" << std::endl;
	for(size_t i = 0; i < n; ++i) {
	for(size_t j = 0; j < n; ++j)
	std::cout << y[n*i+j] << "  ";
	std::cout << std::endl;
	}
	*/
	// Performance of Conventional Matrix x Matrix Computation
	auto start = std::chrono::system_clock::now();
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			z[n*i + j] = 0.0;
			for (size_t k = 0; k < n; ++k)
				z[n*i + j] += x[n*i + k] * y[n*k + j];
		}
	}
	std::chrono::duration<double> time = std::chrono::system_clock::now() - start;
	std::cout << "W/O AVX = " << time.count() << std::endl;

	// Final Result for the MATRIX x MATRIX computation
	/*
	for(size_t i = 0; i < n; ++i) {
	for(size_t j = 0; j < n; ++j)
	std::cout << z[n*i+j] << "  ";
	std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
	*/
	// Re-Initialize MATRIXs
	for (size_t i = 0; i < n; ++i){
		for (size_t j = 0; j < n; ++j) {
			x[n*i + j] = 2.0 + i*1.0;
			y[n*i + j] = 1.0*j + 1.0;
			z[n*i + j] = 0.0;
		}
	}

	std::cout << "AVX MxM Computation Start !" << std::endl;
	start = std::chrono::system_clock::now();
	avx_matmat(x, y, z, n);
	time = std::chrono::system_clock::now() - start;
	std::cout << "AVX = " << time.count() << std::endl;
	/*
	for(size_t i = 0; i < n; ++i) {
	for(size_t j = 0; j < n; ++j)
	std::cout << z[n*i+j] << "  ";
	std::cout << std::endl;
	}
	*/
	_mm_free(x);
	_mm_free(y);
	_mm_free(z);

	return 0;
}
