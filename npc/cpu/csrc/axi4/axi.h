#ifndef __AXI_H__
#define __AXI_H__

#include "../common.h"
#include "axi4.hpp"
#include "axi4_slave.hpp"
#include "axi4_mem.hpp"

template <unsigned int A_WIDTH = 64, unsigned int D_WIDTH = 64, unsigned int ID_WIDTH = 4>
uint64_t axi_load_program(char* img_file, axi4_mem<A_WIDTH,D_WIDTH,ID_WIDTH> &mem){
    if (img_file == NULL) {
        Logc(ASNI_FG_RED,"No image is given. axi-simulation do not support default build-in image.");
        assert(0);
    }
    FILE *fp = fopen(img_file, "rb");
    assert(fp);
    fseek(fp, 0, SEEK_END);
    uint64_t size = ftell(fp);
    Log("The image is %s, size = %ld", img_file, size);
    fseek(fp, 0, SEEK_SET);
    // fetch data to buf
    uint8_t* buf = (uint8_t*)malloc(size);
    int ret = fread(buf, size, 1, fp);
    assert(ret == 1);
    // write to mem
    bool ret2 = mem.write(0, size, buf);
    assert(ret2);
    // done
    free(buf);
    fclose(fp);
    return size;
}


#endif
