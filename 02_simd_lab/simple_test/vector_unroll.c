#include <immintrin.h>
#define MAX 50000
__m256 va [MAX];
__m256 vb [MAX];

void main() {
  int i, ctr;
  for (ctr=0; ctr<1000; ctr++) {  
    for(i=0; i<MAX; i+=8) {
      va[i] = va[i] + vb[i];
      va[i+1] = va[i+1] + vb[i+1];
      va[i+2] = va[i+2] + vb[i+2];
      va[i+3] = va[i+3] + vb[i+3];
      va[i+4] = va[i+4] + vb[i+4];
      va[i+5] = va[i+5] + vb[i+5];
      va[i+6] = va[i+6] + vb[i+6];
      va[i+7] = va[i+7] + vb[i+7];
    }
  }
}

