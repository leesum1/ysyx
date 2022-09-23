#include "trap.h"

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

  return 0;
}
