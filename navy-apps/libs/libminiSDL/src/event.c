#include <NDL.h>
#include <SDL.h>
#include <string.h>

#define keyname(k) #k,

static const char* keyname[] = {
  "NONE",
  _KEYS(keyname)
};

static uint8_t keystate[83] = {};

int SDL_PushEvent(SDL_Event* ev) {
  printf("SDL_PushEvent\n");
  assert(0);
  return 0;
}

int SDL_PollEvent(SDL_Event* ev) {

  char ndl_event[32];
  // return 0 if no NDL events
  if (!NDL_PollEvent(ndl_event, sizeof(ndl_event)))
    return 0;

  char kb_state[5];
  char kb_name[20];
  // prase NDL events, <kd/ku> <keyname> 
  sscanf(ndl_event, "%s %s", kb_state, kb_name);
  // printf(ndl_event, "%s %s \n", kb_state, kb_name);
  // pack SDL_event form NDL events
  ev->type = (!strcmp(kb_state, "kd")) ? SDL_KEYDOWN : SDL_KEYUP;
  ev->key.keysym.sym = SDLK_NONE;
  // get sdl keyname
  for (size_t i = 0; i < 83; i++) {
    if (!strcmp(kb_name, keyname[i])) {
      ev->key.keysym.sym = i;
      keystate[i] = (!strcmp(kb_state, "kd")) ? 1 : 0;
      // printf("match key:%s\n", keyname[i]);
      break;
    }
  }
  return 1;
}

/**
 * @brief 阻塞等待事件
 *
 * @param event
 * @return int 1:有事件 0:无事件
 */
int SDL_WaitEvent(SDL_Event* event) {

  char ndl_event[32];
  // wait for NDL events
  while (!NDL_PollEvent(ndl_event, sizeof(ndl_event)));
  char kb_state[5];
  char kb_name[20];
  // prase NDL events, <kd/ku> <keyname> 
  sscanf(ndl_event, "%s %s", kb_state, kb_name);
  //printf(ndl_event, "%s %s \n", kb_state, kb_name);
  // pack SDL_event form NDL events
  event->type = (!strcmp(kb_state, "kd")) ? SDL_KEYDOWN : SDL_KEYUP;
  event->key.keysym.sym = SDLK_NONE;
  // get sdl keyname
  for (size_t i = 0; i < 83; i++) {
    if (!strcmp(kb_name, keyname[i])) {
      //printf("match key:%s\n", keyname[i]);
      event->key.keysym.sym = i;
      keystate[i] = (!strcmp(kb_state, "kd")) ? 1 : 0;
      break;
    }
  }

  return 1;
}

int SDL_PeepEvents(SDL_Event* ev, int numevents, int action, uint32_t mask) {
  printf("SDL_PeepEvents\n");
  assert(0);
  return 0;
}
// TODO:PAL

uint8_t* SDL_GetKeyState(int* numkeys) {
  //printf("SDL_GetKeyState\n");
  return &keystate[0];
  //return NULL;
}
