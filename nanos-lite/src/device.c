#include <common.h>

#if defined(MULTIPROGRAM) && !defined(TIME_SHARING)
# define MULTIPROGRAM_YIELD() yield()
#else
# define MULTIPROGRAM_YIELD()
#endif

#define NAME(key) \
  [AM_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [AM_KEY_NONE] = "NONE",
  AM_KEYS(NAME)
};

size_t serial_write(const void *buf, size_t offset, size_t len) {
  for(int i = 0; i < len; i++) putch(*((char *)buf+i));
  return len;
}


size_t events_read(void *buf, size_t offset, size_t len) {
  char cbuf[30];
  AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
  if (ev.keycode == AM_KEY_NONE) return 0;
  int size = sprintf(cbuf, "k%s %s\n", ev.keydown ? "d" : "u", keyname[ev.keycode]);
  int i;
  for(i = 0; i < 30 && i < len && i < (size + 1); i++){ //把\0也复制过去,所以要加1
    *((char *)buf+i) = cbuf[i];
  }
  //printf("------------%s--------%d\n", cbuf, size);
  //printf("------------%d %d\n", cbuf[5], cbuf[6]);
  return i;
}

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  int w = io_read(AM_GPU_CONFIG).width;
  int h = io_read(AM_GPU_CONFIG).height;
  char cbuf[50];
  int size = sprintf(cbuf, "WIDTH :%d\nHEIGHT:%d", w, h);
  int i;
  for(i = offset; i < 50 && (i - offset) < len && i < (size + 1); i++){ //把\0也复制过去,所以要加1
    *((char *)buf + i - offset) = cbuf[i];
  }
  return i - offset;
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  uint32_t *p = (uint32_t *)buf;
  io_write(AM_GPU_FBDRAW, p[0], p[1], p+4, p[2], p[3], true);
  return len;
}

void init_device() {
  Log("Initializing devices...");
  ioe_init();
}
