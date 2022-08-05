#include <stdio.h>
#include <NDL.h>

int main() {
  NDL_Init(0);
  char buf[64];
  while (1) {
    if (NDL_PollEvent(buf, sizeof(buf))) {
      printf("receive event: %s\n", buf);
    }
  }
  return 0;
}
