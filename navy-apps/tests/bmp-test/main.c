#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <NDL.h>
#include <BMP.h>

int main() {
  printf("BMP_Load ends! Spinning...\n");
  NDL_Init(0);
  int w, h;
  void* bmp = BMP_Load("/share/pictures/projectn.bmp", &w, &h);
  printf("BMP_Load ends! Spinning...\n");
  assert(bmp);

  NDL_OpenCanvas(&w, &h);

  printf("w:%d,h:%d\n", w, h);
  NDL_DrawRect(bmp, 100, 100, w, h);
  free(bmp);
  NDL_Quit();
  printf("Test ends! Spinning...\n");
  while (1);
  return 0;
}
