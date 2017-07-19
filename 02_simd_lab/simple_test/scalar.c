#define MAX (500000 * 8)
float a [MAX];
float b [MAX];
void main() {
int i, ctr;
for (ctr=0; ctr<100; ctr++) {
for(i=0; i<MAX; i++) {
a[i] = a[i] + b[i];
}
}
}
