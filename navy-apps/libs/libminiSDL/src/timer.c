#include <NDL.h>
#include <sdl-timer.h>
#include <stdio.h>

SDL_TimerID SDL_AddTimer(uint32_t interval, SDL_NewTimerCallback callback, void* param) {
  printf("SDL_AddTimer\n");
  assert(0);
  return NULL;
}

int SDL_RemoveTimer(SDL_TimerID id) {
  printf("SDL_RemoveTimer\n");
  assert(0);
  return 1;
}

uint32_t SDL_GetTicks() {
  return  NDL_GetTicks();
}
// 速度过慢,不需要延迟
void SDL_Delay(uint32_t ms) {
  // printf("SDL_Delay\n");
  // uint32_t now = SDL_GetTicks();
  // while (SDL_GetTicks() - now < ms) {
  //   //printf("SDL_Delay\n");
  // }
  //assert(0);
}
