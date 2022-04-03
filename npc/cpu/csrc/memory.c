#include "memory.h"
#include <malloc.h>

uint8_t* mem = (uint8_t*)malloc(MEM_SIZE);

uint64_t load_program(char* img_file){
    if (img_file == NULL) {
    Log("No image is given. Use the default build-in image.");
    uint32_t* m = (uint32_t*)mem;
    m[0] = 0x00000093;  //li  ra,0
    m[1] = 0x00000393;  //li  t2,0
    m[2] = 0x00200193;  //li  gp,2
    m[3] = 0x00108713;  //addi    a4,ra,1
    m[4] = 0x00708713;  //addi    a4,ra,7
    m[5] = 0x00000513;  //li  a0,0
    m[6] = 0x00100073;  //ebreak
    return 28; // built-in image size
    }
    FILE *fp = fopen(img_file, "rb");
    assert(fp);
    fseek(fp, 0, SEEK_END);
    uint64_t size = ftell(fp);
    Log("The image is %s, size = %ld", img_file, size);
    fseek(fp, 0, SEEK_SET);
    int ret = fread(mem, size, 1, fp);
    assert(ret == 1);
    fclose(fp);
    return size;
}

uint64_t read_memory(uint64_t addr, int length){
    if(addr == 0) return 0;
    assert(addr >= RESET_VECTOR && addr < (RESET_VECTOR + MEM_SIZE));
    switch(length){
        case 1: return *(uint8_t*)(mem + addr - RESET_VECTOR);
        case 2: return *(uint16_t*)(mem + addr - RESET_VECTOR);
        case 4: return *(uint32_t*)(mem + addr - RESET_VECTOR);
        case 8: return *(uint64_t*)(mem + addr - RESET_VECTOR);
        default: assert(0);
    }
}
    