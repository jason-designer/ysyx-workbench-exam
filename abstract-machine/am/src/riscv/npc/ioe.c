#include <am.h>
#include <klib-macros.h>

void __am_timer_init();
void __am_gpu_init();
void __am_timer_rtc(AM_TIMER_RTC_T *);
void __am_timer_uptime(AM_TIMER_UPTIME_T *);
void __am_input_keybrd(AM_INPUT_KEYBRD_T *);
void __am_gpu_config(AM_GPU_CONFIG_T *cfg);
void __am_gpu_status(AM_GPU_STATUS_T *);
void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *);

static void __am_timer_config(AM_TIMER_CONFIG_T *cfg) { cfg->present = true; cfg->has_rtc = true; }
static void __am_input_config(AM_INPUT_CONFIG_T *cfg) { cfg->present = true;  }
static void __am_uart_config(AM_UART_CONFIG_T *cfg)   { cfg->present = false; }

typedef void (*handler_t)(void *buf);
static void *lut[128] = {
  [AM_TIMER_CONFIG] = __am_timer_config,
  [AM_TIMER_RTC   ] = __am_timer_rtc,
  [AM_TIMER_UPTIME] = __am_timer_uptime,
  [AM_INPUT_CONFIG] = __am_input_config,
  [AM_INPUT_KEYBRD] = __am_input_keybrd,
  [AM_UART_CONFIG ] = __am_uart_config,
  [AM_GPU_CONFIG  ] = __am_gpu_config,
  [AM_GPU_FBDRAW  ] = __am_gpu_fbdraw,
  [AM_GPU_STATUS  ] = __am_gpu_status
};

static void fail(void *buf) { panic("access nonexist register"); }

bool ioe_init() {
  for (int i = 0; i < LENGTH(lut); i++)
    if (!lut[i]) lut[i] = fail;
  __am_timer_init();
  __am_gpu_init();
  return true;
}

void ioe_read (int reg, void *buf) { ((handler_t)lut[reg])(buf); }
void ioe_write(int reg, void *buf) { ((handler_t)lut[reg])(buf); }

/************************** device reg implemention ***************************/
// decice addr define
#define DEVICE_BASE 0xa0000000
#define MMIO_BASE 0xa0000000
#define SERIAL_PORT     (DEVICE_BASE + 0x00003f8)
#define KBD_ADDR        (DEVICE_BASE + 0x0000060)
#define RTC_ADDR        (DEVICE_BASE + 0x0000048)
#define VGACTL_ADDR     (DEVICE_BASE + 0x0000100)
#define AUDIO_ADDR      (DEVICE_BASE + 0x0000200)
#define DISK_ADDR       (DEVICE_BASE + 0x0000300)
#define FB_ADDR         (MMIO_BASE   + 0x1000000)
#define AUDIO_SBUF_ADDR (MMIO_BASE   + 0x1200000)
// common function
static inline uint8_t  inb(uintptr_t addr) { return *(volatile uint8_t  *)addr; }
static inline uint16_t inw(uintptr_t addr) { return *(volatile uint16_t *)addr; }
static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }

static inline void outb(uintptr_t addr, uint8_t  data) { *(volatile uint8_t  *)addr = data; }
static inline void outw(uintptr_t addr, uint16_t data) { *(volatile uint16_t *)addr = data; }
static inline void outl(uintptr_t addr, uint32_t data) { *(volatile uint32_t *)addr = data; }
// rtc
static uint64_t start_time;

void __am_timer_init() {
	start_time=(uint64_t)inl(RTC_ADDR)+(((uint64_t)inl(RTC_ADDR+4))<<32);
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
	uptime->us = (uint64_t)inl(RTC_ADDR)+(((uint64_t)inl(RTC_ADDR+4))<<32)-start_time;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
// keyboard
#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
	uint32_t x = inl(KBD_ADDR);
  kbd->keydown = x & 0x8000;
	kbd->keycode = x & 0x7fff;
}
// gpu
#define SYNC_ADDR (VGACTL_ADDR + 4)

void __am_gpu_init() {}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = 0, .height = 0,
    .vmemsz = 0
  };
	uint32_t ctl=inl(VGACTL_ADDR);
	cfg->width=ctl>>16;
	cfg->height=ctl&0x0000ffff;
	cfg->vmemsz=(cfg->width)*(cfg->height)*(sizeof(uint32_t));
}

void cp(int x,int y,uint32_t v)
{
	outl(FB_ADDR+4*(y*400+x),v);
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
	int x,y,w,h;
	int i,j;
	uint32_t* p=ctl->pixels;
	uint32_t W,H;
	W=inl(VGACTL_ADDR)>>16;
	H=inl(VGACTL_ADDR)&0x0000ffff;
	x=ctl->x;
	y=ctl->y;
	w=ctl->w;
	h=ctl->h;
	for(j=y;j<(y+h) && j<H;j++)
	{
		for(i=x;i<(x+w) && i<W;i++) cp(i,j,p[w*(j-y)+(i-x)]);
	}
	//outl(SYNC_ADDR, 1);//不要立即刷新时注释掉
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}



