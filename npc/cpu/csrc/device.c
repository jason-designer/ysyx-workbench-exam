#include "device.h"
#include <sys/time.h>
#include <SDL2/SDL.h>

/************************ common macro ************************/
#define concat_temp(x, y) x ## y
#define concat(x, y) concat_temp(x, y)
/************************ timer device ************************/
static void* rtc_port_base = NULL;

void init_timer(){
    rtc_port_base = malloc(8);
}
/************************ keyboard device ************************/
// keyboard map
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
// keyboard mmio
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

/************************ vga device ************************/
#define SCREEN_W 400
#define SCREEN_H 300
// vmem and gpu_config port, gpu_status is always ready, so it is not needed
static void *vmem = NULL;
static uint32_t *vgactl_port_base = NULL;

static uint32_t screen_width()  {return SCREEN_W;}
static uint32_t screen_height() {return SCREEN_H;}
static uint32_t screen_size()   {return screen_width() * screen_height() * sizeof(uint32_t);}

static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

static void init_screen() {
  SDL_Window *window = NULL;
  char title[128];
  sprintf(title, "%s-NPC", "riscv64");
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer);
  SDL_SetWindowTitle(window, title);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STATIC, SCREEN_W, SCREEN_H);
}

static inline void update_screen() {
  SDL_UpdateTexture(texture, NULL, vmem, SCREEN_W * sizeof(uint32_t));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void vga_update_screen() {
  if(vgactl_port_base[1]){
		update_screen();
		vgactl_port_base[1]=0;
	}
}

void init_vga() {
    vmem = malloc(screen_size());
    vgactl_port_base = (uint32_t *)malloc(8);
    vgactl_port_base[0] = (screen_width() << 16) | screen_height();
    init_screen();
    memset(vmem, 0, screen_size());
}

/************************************************/
void device_init(){
    init_timer();
    init_i8042();
    init_vga();
}

void device_update(int *sdb_state){
    // update keyboard
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
    // update gpu
    vga_update_screen();
}

/************************************************/
/*          len     write   read
uart        1       1       0
timer       8       0       1
keyboard    4       0       1
vgactl      8       1       1
fb                  1       0       */

uint64_t mem_read_help(void* addr, int length){
    switch(length){
        case 1: return *(uint8_t*)addr;
        case 2: return *(uint16_t*)addr;
        case 4: return *(uint32_t*)addr;
        case 8: return *(uint64_t*)addr;
        default: assert(0);
    }
    return 0;
}

void mem_write_help(void* addr, uint64_t data, int length){
    switch(length){
        case 1: *(uint8_t*)addr = data; return;
        case 2: *(uint16_t*)addr = data; return;
        case 4: *(uint32_t*)addr = data; return;
        case 8: *(uint64_t*)addr = data; return;
        default: assert(0);
    }
}

void mmio_read_device(long long raddr, long long *rdata){
    uint64_t addr = raddr & 0xfffffffffffffff8;
    switch(addr){
        case RTC_ADDR:      {
                            struct timeval tv;
                            gettimeofday(&tv, NULL);
                            uint64_t us = tv.tv_sec * 1000000 + tv.tv_usec;
                            *rdata = us;
                            break;
                            }
        case KBD_ADDR:      *rdata = key_dequeue();
                            break;
        case VGACTL_ADDR:   *rdata = *(uint64_t*)vgactl_port_base;
                            break;
        default:            break;
    }
    //Assert(0, "raddr = %llx", raddr);
}

void mmio_write_device(long long waddr, long long wdata, char wmask){
    uint64_t addr, data;
    int length;
    addr = waddr & 0xfffffffffffffff8;
    data = wdata;
    switch((uint8_t)wmask){
        case 0x01: length = 1; addr += 0; data = (data & 0x00000000000000ff) >> 0;  break;
        case 0x02: length = 1; addr += 1; data = (data & 0x000000000000ff00) >> 8;  break;
        case 0x04: length = 1; addr += 2; data = (data & 0x0000000000ff0000) >> 16; break;
        case 0x08: length = 1; addr += 3; data = (data & 0x00000000ff000000) >> 24; break;
        case 0x10: length = 1; addr += 4; data = (data & 0x000000ff00000000) >> 32; break;
        case 0x20: length = 1; addr += 5; data = (data & 0x0000ff0000000000) >> 40; break;
        case 0x40: length = 1; addr += 6; data = (data & 0x00ff000000000000) >> 48; break;
        case 0x80: length = 1; addr += 7; data = (data & 0xff00000000000000) >> 56; break;
        case 0x03: length = 2; addr += 0; data = (data & 0x000000000000ffff) >> 0;  break;
        case 0x0c: length = 2; addr += 2; data = (data & 0x00000000ffff0000) >> 16; break;
        case 0x30: length = 2; addr += 4; data = (data & 0x0000ffff00000000) >> 32; break;
        case 0xc0: length = 2; addr += 6; data = (data & 0xffff000000000000) >> 48; break;
        case 0x0f: length = 4; addr += 0; data = (data & 0x00000000ffffffff) >> 0;  break;
        case 0xf0: length = 4; addr += 4; data = (data & 0xffffffff00000000) >> 32; break;
        case 0xff: length = 8; addr += 0; data = data;                              break;
        default: assert(0);
    }
    if(addr == SERIAL_PORT && length == 1){
        printf("%c", (uint8_t)wdata);
        return;
    }
    if(VGACTL_ADDR <= addr && (addr + length) <= (VGACTL_ADDR + 8)){
        uint8_t* p = (uint8_t*)vgactl_port_base;
        p = p + addr - VGACTL_ADDR;
        mem_write_help(p, data, length);
        return;
    }
    if(FB_ADDR <= addr && ((addr + length) <= (FB_ADDR + 300*400*4))){
        uint8_t* p = (uint8_t*)vmem;
        p = p + addr - FB_ADDR;
        mem_write_help(p, data, length);
        return;
    }
    //Assert(0,"waddr=%llx wdata=%lld wmask=%d", waddr, wdata, wmask);
}