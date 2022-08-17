#ifndef __AXI4_H__
#define __AXI4_H__

#include"common.h"
#include<math.h>
#include"device.h"

template <unsigned int A_WIDTH = 64, unsigned int D_WIDTH = 64, unsigned int ID_WIDTH = 4>
struct axi4_io {
    // aw
    uint8_t     awid;    
    uint64_t    awaddr;   
    uint8_t     awlen;    
    uint8_t     awsize;   
    uint8_t     awburst; 
    bool        awvalid; 
    bool        awready; 
    // w
    uint64_t    wdata;    
    uint8_t     wstrb;     
    bool        wlast;   
    bool        wvalid;  
    bool        wready;    
    // b
    uint8_t     bid;      
    uint8_t     bresp;   
    bool        bvalid;    
    bool        bready;    
    // ar
    uint8_t     arid;    
    uint64_t    araddr;   
    uint8_t     arlen;   
    uint8_t     arsize;  
    uint8_t     arburst;  
    bool        arvalid;  
    bool        arready;   
    // r
    uint8_t     rid;       
    uint64_t    rdata;     
    uint8_t     rresp;    
    bool        rlast;     
    bool        rvalid;    
    bool        rready;    
};

enum axi_resp_type {
    RESP_OKEY   = 0,
    RESP_EXOKEY = 1,
    RESP_SLVERR = 2,
    RESP_DECERR = 3
};
enum axi_burst_type {
    BURST_FIXED = 0,
    BURST_INCR  = 1,
    BURST_WRAP  = 2,
    BURST_RESERVED  = 3
};

struct read_info{
    // read info 
    uint8_t     id;
    uint64_t    addr;
    uint8_t     burst;
    uint64_t    size;   // convert to real size, not 0,1,2,3...
    uint8_t     len;
    // 
    uint64_t    delay;
    uint8_t     state;
    // burst flag
    uint64_t    cur_addr;
    uint64_t    cur_times;
    bool        need_to_read;
};
enum read_state{
    R_IDLE = 0,
    R_DELAY = 1,
    R_FETCH = 2
};

struct write_info{
    // write info 
    uint8_t     id;
    uint64_t    addr;
    uint8_t     burst;
    uint64_t    size;   // convert to real size, not 0,1,2,3...
    uint8_t     len;
    // 
    uint64_t    delay;
    uint8_t     state;
    // burst flag
    uint64_t    cur_addr;
    uint64_t    cur_times;
};
enum write_state{
    W_IDLE = 0,
    W_WRITE = 1,
    W_DELAY = 2,
    W_RESP = 3
};

// 暂时只支持64,64,4
// write_channel不支持resp，resp一直返回正确
template <unsigned int A_WIDTH = 64, unsigned int D_WIDTH = 64, unsigned int ID_WIDTH = 4>
class axi4 {
private:
    uint8_t* mem;
    uint64_t mem_size;
    uint64_t delay;
public:
    axi4_io<A_WIDTH,D_WIDTH,ID_WIDTH> io;
    axi4(uint64_t size, uint64_t delay_input = 0){
        mem = (uint8_t*)malloc(size);
        mem_size = size;
        delay = delay_input;
        assert(A_WIDTH == 64 && D_WIDTH == 64 && ID_WIDTH == 4);
        // init output
        io.awready = false;
        io.wready = false;
        io.bvalid = false;
        io.bresp = 0;
        io.bid = 0;
        io.arready = false;
        io.rvalid = false;
        io.rresp = 0;
        io.rdata = 0;
        io.rlast = false;
        io.rid = 0;
        // init state
        r.state = R_IDLE;
        w.state = W_IDLE;
    }
    ~axi4() {
        free(mem);
    }
    bool read_mem(off_t start_addr, size_t size, uint8_t* buffer) {
        if (start_addr + size <= mem_size) {
            memcpy(buffer,&mem[start_addr],size);
            return true;
        }
        else return false;
    }
    bool write_mem(off_t start_addr, size_t size, const uint8_t* buffer) {
        if (start_addr + size <= mem_size) {
            memcpy(&mem[start_addr],buffer,size);
            return true;
        }
        else return false;
    }
    uint64_t load_img(char* img_file){
        if (img_file == NULL) Logc(ASNI_FG_RED,"No image is given.");
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
    void beat(){
        read_channel();
        write_channel();
    }
private:
    read_info r;
    write_info w;
    // 返回的数据要字节对齐
    uint64_t strb_8_to_64(uint8_t strb){
        uint64_t mask = 0;
        int i;
        for(i = 0; i < 8; i++){
            if((strb >> i) & 0x01) mask |= 0xff << (i * 8);
        }
        return mask;
    }
    axi_resp_type do_read(uint64_t addr, uint64_t size, uint64_t* data){
        assert(A_WIDTH == 64 && D_WIDTH == 64 && ID_WIDTH == 4);
        assert(size <= 8);
        assert((addr + size) <= ((addr & ~0x7) + 8));

        if((addr + RESET_VECTOR) >= DEVICE_BASE) {
            mmio_read_device(addr + RESET_VECTOR, (long long*)data);
            return RESP_OKEY;
        }
        if(addr + size <= mem_size) {
            uint64_t rounding_addr = addr & ~0x7;
            memcpy((uint8_t*)data, &mem[rounding_addr], 8);
            // rounding data accounding to D_WIDTH
            *data = *data << ((addr % 8) << 3);
            return RESP_OKEY;
        }
        return RESP_DECERR;
    }
    void do_write(uint64_t addr, uint64_t size, uint64_t data, uint8_t strb){
        assert(A_WIDTH == 64 && D_WIDTH == 64 && ID_WIDTH == 4);
        assert(size <= 8);
        assert((addr + size) <= ((addr & ~0x7) + 8));

        if((addr + RESET_VECTOR) >= DEVICE_BASE) {
            mmio_write_device(addr + RESET_VECTOR, data, strb);
            return;
        }
        if(addr + size <= mem_size) {
            uint64_t rounding_addr = addr & ~0x7;
            uint64_t mask = strb_8_to_64(strb);
            uint64_t buffer;
            memcpy((uint8_t*)&buffer, &mem[rounding_addr], 8);
            buffer = (buffer & (~mask)) | (data & mask);
            memcpy(&mem[rounding_addr], (uint8_t*)&buffer, 8);
            return;
        }
        assert(0);
    }
    void read_channel(){
        switch(r.state){
            case R_IDLE:    
                            io.arready = false;
                            io.rid = 0;
                            io.rdata = 0;
                            io.rresp = 0;
                            io.rlast = false;
                            io.rvalid = false;
                            if(io.arvalid == true){
                                r.state = R_DELAY;
                                // output
                                io.arready = true;
                                // set delay
                                r.delay = delay;
                                // markdown read info
                                r.id    = io.arid;
                                r.addr  = io.araddr;
                                r.burst = io.arburst;
                                r.size  = pow(2, io.arsize);
                                r.len   = io.arlen;
                            }
                            break;
            case R_DELAY:
                            io.arready = false;
                            io.rid = 0;
                            io.rdata = 0;
                            io.rresp = 0;
                            io.rlast = false;
                            io.rvalid = false;
                            if(r.delay == 0){
                                r.state = R_FETCH;
                                // init do read
                                r.cur_addr = r.addr;
                                r.cur_times = 0;
                                r.need_to_read = true;
                                break;
                            }
                            r.delay--;
                            break;
            case R_FETCH:
                            io.arready = false;
                            io.rvalid   = true;
                            io.rid      = r.id;
                            io.rlast    = r.len == r.cur_times;
                            // make sure only read once every transfer
                            if(r.need_to_read){
                                io.rresp    = do_read(r.cur_addr, r.size, (uint64_t*)&io.rdata);
                                r.need_to_read = false;
                            }
                            // fetch done
                            if(io.rready == true && io.rlast == true){
                                r.state = R_IDLE;
                                // clean r
                                r.id            = 0;
                                r.addr          = 0;
                                r.burst         = 0;
                                r.size          = 0;
                                r.len           = 0;
                                r.cur_addr      = 0;
                                r.cur_times     = 0;
                                r.need_to_read  = false;
                                break;
                            }
                            // update new cur_addr
                            if(io.rready == true){
                                switch(r.burst){
                                    case BURST_FIXED:   break;
                                    case BURST_INCR:    r.cur_addr += r.size; break;
                                    default: assert(0);
                                }
                                r.cur_times++;
                                r.need_to_read = true;
                            }
                            break;
        }
    }
    void write_channel(){
        switch(w.state){
            case W_IDLE:
                            io.awready  = false;
                            io.wready   = false;
                            io.bid      = 0;
                            io.bresp    = 0;
                            io.bvalid   = false;
                            if(io.awvalid == true){
                                w.state = W_WRITE;
                                // output
                                io.awready = true;
                                // markdown write info
                                w.id    = io.awid;
                                w.addr  = io.awaddr;
                                w.burst = io.awburst;
                                w.size  = pow(2, io.awsize);
                                w.len   = io.awlen;
                                // init do write
                                w.cur_addr  = w.addr;
                                w.cur_times = 0;
                            }
                            break;
            case W_WRITE:   
                            io.awready  = false;
                            io.wready   = true;
                            io.bid      = 0;
                            io.bresp    = 0;
                            io.bvalid   = false;
                            if(io.wvalid == true){
                                assert(w.cur_times <= w.len);
                                do_write(w.cur_addr, w.size, io.wdata, io.wstrb);
                                // update cur_addr and cur_times
                                w.cur_times++;
                                switch(w.burst){
                                    case BURST_FIXED:   break;
                                    case BURST_INCR:    w.cur_addr += w.size; break;
                                    default: assert(0);
                                }
                            }
                            if(io.wvalid && io.wlast){
                                w.state = W_DELAY;
                                w.delay = delay;
                            }
                            break;
            case W_DELAY:
                            io.awready  = false;
                            io.wready   = false;
                            io.bid      = 0;
                            io.bresp    = 0;
                            io.bvalid   = false;
                            if(w.delay == 0){
                                w.state = W_RESP;
                                break;
                            }
                            w.delay--;
                            break;
            case W_RESP:
                            io.awready  = false;
                            io.wready   = false;
                            io.bid      = w.id;
                            io.bresp    = RESP_OKEY;
                            io.bvalid   = true;
                            if(io.bready == true){
                                w.state = W_IDLE;
                            }
                            break;
        }
    }


};

#endif