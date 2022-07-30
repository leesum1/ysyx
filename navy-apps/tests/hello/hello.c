#include <unistd.h>
#include <stdio.h>

int main() {
  write(1, "Hello World!\n", 13);
  int i = 2;
  volatile int j = 0;
  // extern char etext, edata, end; /* The symbols must have some type,
  //                                or "gcc -Wall" complains */
  // printf("First address past:\n");
  // printf("    program text (etext)      %10p\n", &etext);
  // printf("    initialized data (edata)  %10p\n", &edata);
  // printf("    uninitialized data (end)  %10p\n", &end);

  while (1) {
    j++;
    if (j == 10000) {
      printf("Hello World from Navy-apps for the %dth time!\n", i++);
      j = 0;
    }
  }

  return 0;

}
