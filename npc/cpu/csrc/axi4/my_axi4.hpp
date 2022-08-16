#ifndef __AXI4_H__
#define __AXI4_H__

#include<stdint.h>

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


template <unsigned int A_WIDTH = 64, unsigned int D_WIDTH = 64, unsigned int ID_WIDTH = 4>
class axi4 {
    private:
    uint8_t* mem;
    uint64_t mem_size;


    public:


};

#endif