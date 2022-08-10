#include "device.h"
#include <sys/time.h>
#include <SDL2/SDL.h>

/************************ common macro ************************/
#define concat_temp(x, y) x ## y
#define concat(x, y) concat_temp(x, y)
/************************ keyboard ************************/
// key map
#define KEYDOWN_MASK 0x8000
#define MAP(c, f) c(f)
#define _KEY_NAME(k) _KEY_##k,
#define _KEYS(f) \
  f(ESCAPE) f(F1) f(F2) f(F3) f(F4) f(F5) f(F6) f(F7) f(F8) f(F9) f(F10) f(F11) f(F12) \
f(GRAVE) f(1) f(2) f(3) f(4) f(5) f(6) f(7) f(8) f(9) f(0) f(MINUS) f(EQUALS) f(BACKSPACE) \
f(TAB) f(Q) f(W) f(E) f(R) f(T) f(Y) f(U) f(I) f(O) f(P) f(LEFTBRACKET) f(RIGHTBRACKET) f(BACKSLASH) \
f(CAPSLOCK) f(A) f(S) f(D) f(F) f(G) f(H) f(J) f(K) f(L) f(SEMICOLON) f(APOSTROPHE) f(RETURN) \
f(LSHIFT) f(Z) f(X) f(C) f(V) f(B) f(N) f(M) f(COMMA) f(PERIOD) f(SLASH) f(RSHIFT) \
f(LCTRL) f(APPLICATION) f(LALT) f(SPACE) f(RALT) f(RCTRL) \
f(UP) f(DOWN) f(LEFT) f(RIGHT) f(INSERT) f(DELETE) f(HOME) f(END) f(PAGEUP) f(PAGEDOWN)

enum {
  _KEY_NONE = 0,
  MAP(_KEYS, _KEY_NAME)
};

#define SDL_KEYMAP(k) keymap[concat(SDL_SCANCODE_, k)] = concat(_KEY_, k);
static uint32_t keymap[256] = {};

static void init_keymap() {
  MAP(_KEYS, SDL_KEYMAP)
}

#define KEY_QUEUE_LEN 1024
static int key_queue[KEY_QUEUE_LEN] = {};
static int key_f = 0, key_r = 0;
// 
static uint32_t *i8042_data_port_base = NULL;

void init_i8042() {
  i8042_data_port_base = (uint32_t *)malloc(4);
  i8042_data_port_base[0] = _KEY_NONE;
  init_keymap();
}

static void key_enqueue(uint32_t am_scancode) {
  key_queue[key_r] = am_scancode;
  key_r = (key_r + 1) % KEY_QUEUE_LEN;
  Assert(key_r != key_f, "key queue overflow!");
}

static uint32_t key_dequeue() {
  uint32_t key = _KEY_NONE;
  if (key_f != key_r) {
    key = key_queue[key_f];
    key_f = (key_f + 1) % KEY_QUEUE_LEN;
  }
  return key;
}

void send_key(uint8_t scancode, bool is_keydown) {
  if (keymap[scancode] != _KEY_NONE) {
    uint32_t am_scancode = keymap[scancode] | (is_keydown ? KEYDOWN_MASK : 0);
    key_enqueue(am_scancode);
  }
}

uint64_t i8042_read_data() {
  i8042_data_port_base[0] = key_dequeue();
  return i8042_data_port_base[0];
}

/************************************************/
bool is_device_read(uint64_t addr, int length){
    return addr >= DEVICE_BASE;
}
uint64_t mmio_read(uint64_t addr, int length){
    if(addr == SERIAL_PORT){        // uart
        return 0;
    }
    if(addr == RTC_ADDR){           // uptime
        struct timeval tv;
        gettimeofday(&tv, NULL);
        uint64_t us = tv.tv_sec * 1000000 + tv.tv_usec;
        return us;
    }
    if(addr == KBD_ADDR){
        return i8042_read_data();
    }
    return 0; // TODO why it will read addr which is not device 
    assert(0);
}
bool is_device_write(uint64_t addr, int length){
    return addr >= DEVICE_BASE;
}
void mmio_write(uint64_t addr, uint64_t data, int length){
    if(addr == SERIAL_PORT){        // uart
        char c = data;
        printf("%c",c);
        return;
    }
    assert(0);
}
/************************************************/
void device_sdl_init(){
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(1280,720,0,&window,&renderer);
}

void device_init(){
    init_i8042();
    device_sdl_init();
}

void device_update(int *sdb_state){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:
                *sdb_state = SDB_QUIT;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP: {
                uint8_t k = event.key.keysym.scancode;
                bool is_keydown = (event.key.type == SDL_KEYDOWN);
                send_key(k, is_keydown);
                break;
            }
            default: break;
        }
    }
}
