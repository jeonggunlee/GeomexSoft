#include <immintrin.h>

#define MAX 5000000

__m256 va [MAX];
__m256 vb [MAX];

void main() {
  int ctr, i;
  for (ctr=0; ctr<1000; ctr++) {  
    for(i=0; i<MAX; i++) {
      va[i] = _mm256_add_ps(va[i], vb[i]);
    }
  }
}

