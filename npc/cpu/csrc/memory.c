#include "memory.h"
#include <malloc.h>

uint8_t* mem = (uint8_t*)malloc(MEM_SIZE);

uint64_t load_program(char* img_file){
    if (img_file == NULL) {
    Log("No image is given. Use the default build-in image.");
    uint32_t* m = (uint32_t*)mem;
    // 无现关性冲突
    m[0] = 0x00000093;  //li  ra,0
    m[1] = 0x00000393;  //li  t2,0
    m[2] = 0x00200193;  //li  gp,2
    m[3] = 0x00000513;  //li  a0,0
    m[4] = 0x00100073;  //ebreak
    return 20;          // built-in image size
    // 无现关性冲突的跳转用例
    00200193            //li	gp,2
    00000093          	//li	ra,0
    00100113          	//li	sp,1
    m[1] = 0x00000393;  //li  t2,0
    m[3] = 0x00000513;  //li  a0,0
    00209663    //bne	ra,sp,80000018
    m[4] = 0x00100073;  //ebreak
    return 20;          // built-in image size
    // 现关性冲突
    // m[0] = 0x00000093;  //li  ra,0
    // m[1] = 0x00000393;  //li  t2,0
    // m[2] = 0x00200193;  //li  gp,2
    // m[3] = 0x00108713;  //addi    a4,ra,1
    // m[4] = 0x00708713;  //addi    a4,ra,7
    // m[5] = 0x00000513;  //li  a0,0
    // m[6] = 0x00100073;  //ebreak
    // return 28; // built-in image size
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
    // if(addr != 0){
    //     printf("-----%llx, %d\n",addr, length);
    //     printf("mem=%lx\n",*(uint32_t*)(mem + addr - RESET_VECTOR));
    // }
    if(addr == 0) return 0;
    if(!(addr >= RESET_VECTOR && addr < (RESET_VECTOR + MEM_SIZE))) return 0;
    assert(addr >= RESET_VECTOR && addr < (RESET_VECTOR + MEM_SIZE));
    switch(length){
        case 1: return *(uint8_t*)(mem + addr - RESET_VECTOR);
        case 2: return *(uint16_t*)(mem + addr - RESET_VECTOR);
        case 4: return *(uint32_t*)(mem + addr - RESET_VECTOR);
        case 8: return *(uint64_t*)(mem + addr - RESET_VECTOR);
        default: assert(0);
    }
}

void write_memory(uint64_t addr, uint64_t data, int length){
    //if(addr == 0) return;
    assert(addr >= RESET_VECTOR && addr < (RESET_VECTOR + MEM_SIZE));
    switch(length){
        case 1: *(uint8_t*)(mem + addr - RESET_VECTOR) = (uint8_t)data; break;
        case 2: *(uint16_t*)(mem + addr - RESET_VECTOR) = (uint16_t)data; break;
        case 4: *(uint32_t*)(mem + addr - RESET_VECTOR) = (uint32_t)data; break;
        case 8: *(uint64_t*)(mem + addr - RESET_VECTOR) = (uint64_t)data; break;
        default: assert(0);
    }
}

uint64_t wmask_to_64bit(uint8_t wmask){
    uint64_t x = 0;
    for(int i = 0; i < 8; i++){
        uint64_t m = 0;
        if((wmask >> i) & 0x01) m = 0xff;
        else m = 0;
        x = x | (m << (i * 8));
    }
    return x;
}

void imem_read(unsigned char ren, long long raddr, int *rdata) {
    //Logc(ASNI_FG_YELLOW,"imem read mem, raddr = %lx, ren = %d",raddr, ren);
    if(ren) *rdata = read_memory(raddr, 4);
}

void pmem_read(unsigned char ren, long long raddr, long long *rdata) {
    // 总是读取地址为`raddr & ~0x7ull`的8字节返回给`rdata`
    //Logc(ASNI_FG_YELLOW,"dmem read mem, raddr = %llx, ren = %d",raddr, ren);
    if(ren) *rdata = read_memory(raddr & 0xfffffffffffffff8, 8);
}
void pmem_write(unsigned char wen, long long waddr, long long wdata, char wmask) {
    // 总是往地址为`waddr & ~0x7ull`的8字节按写掩码`wmask`写入`wdata`
    // `wmask`中每比特表示`wdata`中1个字节的掩码,
    // 如`wmask = 0x3`代表只写入最低2个字节, 内存中的其它字节保持不变
    //Logc(ASNI_FG_YELLOW,"dmem write mem, wen = %d, waddr = %llx, wdata = %llx, wmask = %x", wen, waddr, wdata, wmask);
    if(wen){
        uint64_t x = read_memory(waddr & 0xfffffffffffffff8, 8);
        uint64_t mask = wmask_to_64bit(wmask);
        x = x & (~mask);
        x = x | (mask & wdata);
        write_memory(waddr & 0xfffffffffffffff8, x, 8);
    }
}



    