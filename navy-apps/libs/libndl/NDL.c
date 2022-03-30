#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <assert.h>

static int evtdev = -1;
static int fbdev = -1;
static int screen_w = 0, screen_h = 0;
static int W = 0, H = 0;

uint32_t NDL_GetTicks() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec/1000;
}

int NDL_PollEvent(char *buf, int len) {
  int fd = open("/dev/keyboard", O_RDONLY);
  int size = read(fd, buf, len);
  close(fd);
  return size != 0;
}

void NDL_OpenCanvas(int *w, int *h) {
  char dbuf[50];
  int width, height;
  int fd = open("/proc/dispinfo", O_RDONLY);
  read(fd, dbuf, 50);
  close(fd);
  sscanf(dbuf, "WIDTH :%d\nHEIGHT:%d", &width, &height);
  W = width;
  H = height;
  screen_w = *w; screen_h = *h;
  if(screen_w == 0 && screen_h == 0){
    screen_w = W;
    screen_h = H;
  }
  assert(screen_w <= W && screen_h <= H && screen_w > 0 && screen_h > 0);
  //
  if (getenv("NWM_APP")) {
    int fbctl = 4;
    fbdev = 5;
    screen_w = *w; screen_h = *h;
    if(screen_w == 0 && screen_h == 0){
      screen_w = W;
      screen_h = H;
    }
    assert(screen_w <= W && screen_h <= H && screen_w > 0 && screen_h > 0);
    char buf[64];
    int len = sprintf(buf, "%d %d", screen_w, screen_h);
    // let NWM resize the window and create the frame buffer
    write(fbctl, buf, len);
    while (1) {
      // 3 = evtdev
      int nread = read(3, buf, sizeof(buf) - 1);
      if (nread <= 0) continue;
      buf[nread] = '\0';
      if (strcmp(buf, "mmap ok") == 0) break;
    }
    close(fbctl);
  }
}

void NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h) { 
  //buf前四个元素放xywh，剩下的复制pixels.
  int size = w * h;
  uint32_t* buf = (uint32_t *)malloc(4 * (size + 4));//必须用malloc才行，用数组会有奇怪的问题。
  buf[0] = x + W/2 - screen_w/2; //三
  buf[1] = y + H/2 - screen_h/2;
  buf[2] = w;
  buf[3] = h;
  for(int i = 0; i < size; i++) buf[i+4] = pixels[i];
  int fd = open("/dev/fb", O_WRONLY);
  write(fd, buf, 4 * (size + 4));
  close(fd);
}

void NDL_OpenAudio(int freq, int channels, int samples) {
}

void NDL_CloseAudio() {
}

int NDL_PlayAudio(void *buf, int len) {
  return 0;
}

int NDL_QueryAudio() {
  return 0;
}

int NDL_Init(uint32_t flags) {
  if (getenv("NWM_APP")) {
    evtdev = 3;
  }
  return 0;
}

void NDL_Quit() {
}
