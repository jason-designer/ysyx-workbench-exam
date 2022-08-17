#include"trace.h"


CPU_Commit_Info commit_info = {.commit = false, .pc = 0, .inst = 0, .ren = false, .raddr = 0, .wen = false, .waddr = 0};
void commit_info_fetch(unsigned char commit, long long pc, int inst, unsigned char ren, long long raddr, unsigned char wen, long long waddr){
    commit_info.commit  = commit;
    commit_info.pc      = pc;
    commit_info.inst    = inst;
    commit_info.ren     = ren;
    commit_info.raddr   = raddr;
    commit_info.wen     = wen;
    commit_info.waddr   = waddr;
}

Dmem_Info dmem_info = {.valid = false, .pc = 0, .inst = 0, .ren = false, .raddr = 0, .rdata = 0, .wen = 0, .waddr = 0, .wdata = 0, .wmask = 0};
void dmem_info_fetch( unsigned char valid, long long pc, int inst, unsigned char ren, long long raddr, long long rdata, unsigned char wen, long long waddr, long long wdata, char wmask){
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

void dmem_trace(){
    Dmem_Info& d = dmem_info;
    printf("%d %llx %08lx %d %016llx %016llx %d %016llx %016llx %02x\n",d.valid, d.pc, d.inst, d.ren, d.raddr, d.rdata, d.wen, d.waddr, d.wdata, d.wmask);
}


// iringbuf
#define IRINGBUF_SIZE 30
char iringbuf[IRINGBUF_SIZE][100];
int iringbuf_index;

void iringbuf_init(){
    iringbuf_index = IRINGBUF_SIZE - 1;
}

void iringbuf_log_once(char* str){
    iringbuf_index++;
    if(iringbuf_index >= IRINGBUF_SIZE) iringbuf_index = 0;
    strcpy(iringbuf[iringbuf_index], str);
}

void iringbuf_print(){
    int i;
    printf("------------------------- iringbuf ---------------------------\n");
    for(i = 0; i < IRINGBUF_SIZE; i++){
        if(i == iringbuf_index) printf("-->[%2d]%s\n", i, iringbuf[i]);
        else printf("   [%2d]%s\n", i, iringbuf[i]);
    }
    printf("--------------------------------------------------------------\n");
}
