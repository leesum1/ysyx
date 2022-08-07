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
  printf(ndl_event, "%s %s %s\n", kb_state, kb_name, keyname[0]);

  event->type = (!strcmp(kb_state, "kd")) ? SDL_KEYDOWN : SDL_KEYUP;

  // for (size_t i = 0; i < sizeof(keyname); i++) {
  //   /* code */
  // }

  // event->key.keysym = 
  // event->key = 
  return 1;
}

int SDL_PeepEvents(SDL_Event* ev, int numevents, int action, uint32_t mask) {
  return 0;
}

uint8_t* SDL_GetKeyState(int* numkeys) {
  return NULL;
}
