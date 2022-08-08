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

int SDL_ShowCursor(int toggle) {
  return 0;
}

void SDL_WM_SetCaption(const char* title, const char* icon) {
}
