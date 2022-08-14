#include"trace.h"


CPU_Commit_Info commit_info = {.commit = false, .pc = 0, .inst = 0};
void commit_info(unsigned char commit, long long pc, int inst){
    commit_info.commit = commit;
    commit_info.pc = pc;
    commit_info.inst = inst;
}

Dmem_Info dmem_info = {.valid = false, .pc = 0, .inst = 0, .ren = false, .raddr = 0, .rdata = 0, .wen = 0, .waddr = 0, .wdata = 0, .wmask = 0};
void dmem_info( unsigned char valid, long long pc, int inst, unsigned char ren, long long raddr, long long rdata, unsigned char wen, long long waddr, long long wdata, char wmask){
    dmem_info.valid = valid;
    dmem_info.pc = pc;
    dmem_info.inst = inst;                        
    dmem_info.ren = ren;
    dmem_info.raddr = raddr;
    dmem_info.rdata = rdata;
    dmem_info.wen = wen;
    dmem_info.waddr = waddr;
    dmem_info.wdata = wdata;
    dmem_info.wmask = wmask;
}

// void dmem_trace(){
//     Dmem_Info& d;
//     d = dmem_info
//     printf("");
// }
