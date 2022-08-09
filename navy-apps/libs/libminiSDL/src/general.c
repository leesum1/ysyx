#include <NDL.h>
#include <stdio.h>
#include <stdarg.h>
static char sdlerrbuf[1024];

int SDL_Init(uint32_t flags) {
  return NDL_Init(flags);
}

void SDL_Quit() {
  NDL_Quit();
}

char* SDL_GetError() {
  return sdlerrbuf;
}

int SDL_SetError(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsprintf(sdlerrbuf, fmt, args);
  va_end(args);
  return -1;
}
// pal
int SDL_ShowCursor(int toggle) {
  printf("SDL_ShowCursor\n");
  assert(0);
  return 0;
}
// pal
void SDL_WM_SetCaption(const char* title, const char* icon) {
  printf("SDL_WM_SetCaption\n");
  //assert(0);
}
