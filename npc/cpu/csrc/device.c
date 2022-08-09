#include "device.h"
#include <sys/time.h>

bool is_device_read(uint64_t addr, int length){
    return addr >= DEVICE_BASE;
}
uint64_t mmio_read(uint64_t addr, int length){
    if(addr == 0xa0000048){
        struct timeval tv;
        gettimeofday(&tv, NULL);
        uint64_t us = tv.tv_sec * 1000000 + tv.tv_usec;
        return us;
    }
}
bool is_device_write(uint64_t addr, int length){
    return addr >= DEVICE_BASE;
}
void mmio_write(uint64_t addr, uint64_t data, int length){
    if(addr==0xa00003f8){
        char c = data;
        printf("%c",c);
        return;
    }
}
