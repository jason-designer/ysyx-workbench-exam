#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "common.h"

#define DEVICE_BASE 0xa0000000
#define MMIO_BASE   0xa0000000

#define RTC_ADDR        (DEVICE_BASE + 0x0000048)
#define KBD_ADDR        (DEVICE_BASE + 0x0000060)
#define VGACTL_ADDR     (DEVICE_BASE + 0x0000100)
#define AUDIO_ADDR      (DEVICE_BASE + 0x0000200)
#define DISK_ADDR       (DEVICE_BASE + 0x0000300)
#define SERIAL_PORT     (DEVICE_BASE + 0x00003f8)
#define FB_ADDR         (MMIO_BASE   + 0x1000000)
#define AUDIO_SBUF_ADDR (MMIO_BASE   + 0x1200000)

void device_init();
void device_update(int* sdb_state);

bool is_device_read(uint64_t addr, int length);
uint64_t mmio_read(uint64_t addr, int length);
bool is_device_write(uint64_t addr, int length);
void mmio_write(uint64_t addr, uint64_t data, int length);


#endif