#include <NDL.h>
#include <SDL.h>
#include <string.h>
#define keyname(k) #k,

static const char* keyname[] = {
  "NONE",
  _KEYS(keyname)
};

int SDL_PushEvent(SDL_Event* ev) {
  return 0;
}

int SDL_PollEvent(SDL_Event* ev) {
  return 0;
}

int SDL_WaitEvent(SDL_Event* event) {

  char ndl_event[32];
  while (!NDL_PollEvent(ndl_event, sizeof(ndl_event)));
  char kb_state[5];
  char kb_name[20];
  sscanf(ndl_event, "%s %s", kb_state, kb_name);
  printf(ndl_event, "%s %s \n", kb_state, kb_name);

  event->type = (!strcmp(kb_state, "kd")) ? SDL_KEYDOWN : SDL_KEYUP;
  event->key.keysym.sym = SDLK_NONE;
  for (size_t i = 0; i < 83; i++) {
    if (!strcmp(kb_name, keyname[i])) {
      event->key.keysym.sym = i;
      printf("match key:%s\n", keyname[i]);
      break;
    }
  }

  return 1;
}

int SDL_PeepEvents(SDL_Event* ev, int numevents, int action, uint32_t mask) {
  return 0;
}

uint8_t* SDL_GetKeyState(int* numkeys) {
  return NULL;
}
