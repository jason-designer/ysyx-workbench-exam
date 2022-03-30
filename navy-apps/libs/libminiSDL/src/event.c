#include <NDL.h>
#include <SDL.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define keyname(k) #k,

static const char *keyname[] = {
  "NONE",
  _KEYS(keyname)
};

int SDL_PushEvent(SDL_Event *ev) {
  assert(0);
  return 0;
}

int SDL_PollEvent(SDL_Event *ev) {
  char buf[30];
  if(NDL_PollEvent(buf, 30) == 0) return 0;
  char keybuf[10];
  char keydown;
  sscanf(buf, "k%c %s\n",&keydown,keybuf);
  switch(keydown){
    case 'd': ev->type = SDL_KEYDOWN; ev->key.type = SDL_KEYDOWN; break;
    case 'u': ev->type = SDL_KEYUP; ev->key.type = SDL_KEYUP; break;
    default : assert(0);
  }
    for(int i=0; i < 82; i++){
      if(strcmp(keybuf, keyname[i]) == 0){
        ev->key.keysym.sym = i;
        break;
      }
    }
  printf("---%d\n",ev->key.keysym.sym);
  printf("---%d\n", ev->key.type);
  return 1;
}

int SDL_WaitEvent(SDL_Event *event) {
  char buf[30];
  while(NDL_PollEvent(buf, 30) == 0);
  char keybuf[10];
  char keydown;
  sscanf(buf, "k%c %s\n",&keydown,keybuf);
  switch(keydown){
    case 'd': event->type = SDL_KEYDOWN; event->key.type = SDL_KEYDOWN; break;
    case 'u': event->type = SDL_KEYUP; event->key.type = SDL_KEYUP; break;
    default : assert(0);
  }
    for(int i=0; i < 82; i++){
      if(strcmp(keybuf, keyname[i]) == 0){
        event->key.keysym.sym = i;
        break;
      }
    }
  printf("---%d\n",event->key.keysym.sym);
  printf("---%d\n", event->key.type);
  return 1;
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  assert(0);
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
  assert(0);
  return NULL;
}



