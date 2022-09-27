#include "trap.h"
#include <stdio.h>
#define N 10
int a[N];

int main() {
  int i, j;
  for (i = 0; i < N; i++)
    a[i] = i * 10;

  for (i = 0; i < N; i++)
    for (j = 1; j < N + 1; j++)
      a[i] *= j;
  for (i = 0; i < N; i++)
    for (j = 1; j < N + 1; j++)
      a[i] /= j;

  for (i = 0; i < N; i++)
    check(a[i] == i * 10);

  int divident = -1;
  int divisor = 1;
  int out;
  int rem;

  for (uint32_t divident_i = 1; i < 0xffffffff; divident_i++) {
    for (uint32_t divisor_i = 1; i < 0xffffffff; divisor_i++) {
      //printf("divident_i:%d,divisor_i:%d\n",divident_i,divisor_i);
      out = (int)divident_i / (int)divisor_i;
      rem = (int)divident_i % (int)divisor_i;
      //printf("out:%d,rem:%d\n",out,rem);
    }
  }

  //check(1);
  out = divident / divisor;
  rem = divident % divisor;
  //printf("out:%d,rem:%d\n",out,rem);
  //check(1);
  divident = 100;
  out = divident / divisor;
  rem = divident % divisor;
  //printf("out:%d,rem:%d\n",out,rem);
  divident = 100;
  divisor = 101;
  out = divident / divisor;
  rem = divident % divisor;
  //printf("out:%d,rem:%d\n",out,rem);

  rem = out + 1;
  out = rem + 1;
  return 0;
}
