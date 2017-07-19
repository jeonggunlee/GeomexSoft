#include <immintrin.h>

#define MAX 5000000

__m256d va [MAX];
__m256d vb [MAX];

void main() {
  int ctr, i;
  for (ctr=0; ctr<1000; ctr++) {  
    for(i=0; i<MAX; i++) {
      va[i] = _mm256_add_pd(va[i], vb[i]);
    }
  }
}

