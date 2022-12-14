#include <NDL.h>
#include <sdl-timer.h>
#include <stdio.h>
#include <assert.h>

SDL_TimerID SDL_AddTimer(uint32_t interval, SDL_NewTimerCallback callback, void *param) {
  assert(0);
  return NULL;
}

int SDL_RemoveTimer(SDL_TimerID id) {
  assert(0);
  return 1;
}

uint32_t SDL_StartTime;
uint32_t SDL_GetTicks() {
  return NDL_GetTicks() - SDL_StartTime;
}

void SDL_Delay(uint32_t ms) {
  //assert(0);
  uint64_t t0 = NDL_GetTicks();
  while((NDL_GetTicks()-t0) < ms);
}
