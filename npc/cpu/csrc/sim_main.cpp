#include "VSimTop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "common.h"
#include "memory.h"
#include "halt.h"
#include "reg.h"
#include "difftest.h"
#include "device.h"
#include "trace.h"
#include <sys/time.h>

/***************** sdb config *******************/ 
#define DIFFTEST
#define TRACE_WAVE
#define ITRACE
// #define MTRACE 
#define DTRACE

#define SIM_RESET_TIME 3
/************************************************/
#include "axi4.hpp"

void axi_to_cpu(VSimTop* top, axi4<64,64,4>& axi){
    // aw
    top->io_master_awready  = axi.io.awready;
    // w
    top->io_master_wready   = axi.io.wready;
    // b
    top->io_master_bvalid   = axi.io.bvalid;
    top->io_master_bresp    = axi.io.bresp;
    top->io_master_bid      = axi.io.bid;
    // ar
    top->io_master_arready  = axi.io.arready;
    // r
    top->io_master_rvalid   = axi.io.rvalid;
    top->io_master_rresp    = axi.io.rresp;
    top->io_master_rdata    = axi.io.rdata;
    top->io_master_rlast    = axi.io.rlast;
    top->io_master_rid      = axi.io.rid;
}

void cpu_to_axi(VSimTop* top, axi4<64,64,4>& axi){
    // aw
    axi.io.awvalid = top->io_master_awvalid;
    axi.io.awaddr  = top->io_master_awaddr - 0x80000000;
    axi.io.awid    = top->io_master_awid;
    axi.io.awlen   = top->io_master_awlen;
    axi.io.awsize  = top->io_master_awsize;
    axi.io.awburst = top->io_master_awburst;
    // w
    axi.io.wvalid  = top->io_master_wvalid;
    axi.io.wdata   = top->io_master_wdata;
    axi.io.wstrb   = top->io_master_wstrb;
    axi.io.wlast   = top->io_master_wlast;
    // b
    axi.io.bready  = top->io_master_bready;
    // ar
    axi.io.arvalid = top->io_master_arvalid;
    axi.io.araddr  = top->io_master_araddr - 0x80000000;
    axi.io.arid    = top->io_master_arid;
    axi.io.arlen   = top->io_master_arlen;
    axi.io.arsize  = top->io_master_arsize;
    axi.io.arburst = top->io_master_arburst;
    // r
    axi.io.rready  = top->io_master_rready;
}

/***********************************************************/
void init_disasm(const char *triple);
void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);

void init_sdb(){
    init_disasm("riscv64-pc-linux-gnu");
    iringbuf_init();
}

uint64_t get_sys_time_us(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    uint64_t us = tv.tv_sec * 1000000 + tv.tv_usec;
    return us;
}

typedef struct {
  char* program_name;
  bool fail;
  uint64_t sim_time;
  uint64_t clock_number;
  uint64_t inst_number;
  uint64_t start_sys_time;
  uint64_t end_sys_time;
  double ipc;
  uint64_t clock_per_sec;
} Sdb_end_info;

char* get_program_name(char* img_file){
    int len = strlen(img_file);
    int i;
    for(i = len - 1; i >= 0; i--){
        if(img_file[i] == '/') break;
    }
    char* name = (char*)malloc((len - i));
    strcpy(name, img_file + i + 1);
    return name;
}

Sdb_end_info* sim_main(int argc, char** argv, char* tfp_file, char* diff_file, char* img_file){
    VerilatedContext* contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    VSimTop* top = new VSimTop{contextp};           // top is the name of Module
    //trace on
    Verilated::traceEverOn(true);                   // open trace, so that it can generate waveforms
    VerilatedVcdC* tfp = new VerilatedVcdC;         // it is used for generating waveforms
    top->trace(tfp, 99);                            // Trace 99 levels of hierarchy,1 level means only trace top level signals
    tfp->open(tfp_file);                            // set the path of the vcd file, you need to mkdir before running it
    /****************************************************************************/
    // init axi
    axi4<64,64,4> axi(0x8000000);
    axi.load_img(img_file);
    // 
    setbuf(stdout, NULL);
    uint64_t size = load_program(img_file);
    device_init();
    // 
    #ifdef DIFFTEST
    // init_difftest("/home/zgs/project/ysyx-workbench/nemu/build/riscv64-nemu-interpreter-so", size, DIFFTEST_PORT);
    // init_difftest("/home/zgs/project/ysyx-workbench/nemu/tools/spike-diff/build/riscv64-spike-so", size, DIFFTEST_PORT);
    init_difftest(diff_file, size, DIFFTEST_PORT);
    #else
    commit_info.commit = 0;
    #endif

    // 
    uint64_t start_sys_time = get_sys_time_us();
    int sdb_state = SDB_RUNNING;
    int sim_time = 0;                             // sim time
    int inst_number = 0;
    // difftest 
    bool start_difftest = false;
    uint64_t pc = 0;
    uint64_t pre_pc = 0;
    // 
    while (sdb_state == SDB_RUNNING) { 
        // device
        device_update(&sdb_state);
        // clock and reset
        top->reset = sim_time < SIM_RESET_TIME ? 1 : 0;
        top->clock = sim_time % 2;                                                          
        top->eval();   

        if(sim_time % 2 == 1){
            cpu_to_axi(top, axi);
            axi.beat();
            axi_to_cpu(top, axi);
            top->eval();
        }

        // trace
        #ifdef TRACE_WAVE           
        tfp->dump(contextp->time());
        #endif
        // SDL quit
        if(sdb_state == SDB_QUIT) break;
        
        // do every clk
        if(sim_time >= SIM_RESET_TIME && sim_time % 2 == 0){
            // itrace
            #ifdef ITRACE 
            if(commit_info.commit){
                char str[100];
                uint32_t inst = commit_info.inst;
                uint32_t pc = commit_info.pc;
                disassemble(str, 100, pc, (uint8_t*)&inst, 4);
                // printf("pc = %lx : %08x : %s\n", commit_info.pc, commit_info.inst, str);
                char buf[100];
                sprintf(buf, "time = %ld pc = %lx : %08x : %s", sim_time, commit_info.pc, commit_info.inst, str);
                iringbuf_log_once(buf);
            }
            #endif
            // mtrace
            #ifdef MTRACE 
            if(dmem_info.valid == 1 && (dmem_info.ren == 1 || dmem_info.wen == 1)){
                // void dmem_trace();
                // dmem_trace();
                Dmem_Info& d = dmem_info;
                printf("%d %d %llx %08lx %d %016lx %016lx %d %lx %016lx %02x\n",sim_time,d.valid, d.pc, d.inst, d.ren, d.raddr, d.rdata, d.wen, d.waddr, d.wdata, d.wmask);

            }
            #endif

            // DTRACE
            #ifdef DTRACE
            // if()
            #endif

            // halt
            if((uint8_t)cpu_halt == 1) {
                Log("Detected ebreak, sim quit");
                if(!cpu_gpr[10]) sdb_state = SDB_HIT_GOOD_TRAP;
                else sdb_state = SDB_HIT_BAD_TRAP;
                break;
            }
            // difftest
            #ifdef DIFFTEST
            if(start_difftest == false){  //这是为了跳过第一个valid
                if(commit_info.commit) {
                    start_difftest = true;
                    pre_pc = pc;
                    pc = commit_info.pc;
                }
            }
            else{
                if(commit_info.commit){
                    inst_number++;  //记录commit的指令数
                    pre_pc = pc;
                    pc = commit_info.pc;
                    isa_reg_update(pc, cpu_gpr);

                    bool read_device = commit_info.ren == 1 && commit_info.raddr >= DEVICE_BASE;
                    bool write_device = commit_info.wen == 1 && commit_info.waddr >= DEVICE_BASE;
                    if(read_device || write_device){            // is device, skip difftest
                        difftest_skip_ref();
                    }
                    else{                                       // difftest
                        if(!difftest_step(pre_pc)) {
                            sdb_state = SDB_DIFFTEST_WRONG;
                        break;
                    }
                }
                }
            }
            #else
            if(commit_info.commit){
                inst_number++;  //记录commit的指令数
            }
            #endif

        } 
        contextp->timeInc(1);
        sim_time++;
    }
    switch(sdb_state){
        case SDB_HIT_GOOD_TRAP:     Logc(ASNI_FG_GREEN,"hit good trap"); break;
        case SDB_HIT_BAD_TRAP:      Logc(ASNI_FG_RED,"hit bad trap"); break;
        case SDB_DIFFTEST_WRONG:    Logc(ASNI_FG_RED, "difftest detect wrong, sim quit"); break;
        case SDB_QUIT:              Logc(ASNI_FG_RED, "sim quit by SDL singal"); break;
    }
    int fail = 1;
    if(sdb_state == SDB_HIT_GOOD_TRAP) fail = 0;

    /***********************************************************************/
    #ifdef ITRACE
    if(sdb_state != SDB_HIT_GOOD_TRAP) iringbuf_print();
    #endif
    /***********************************************************************/
    tfp->close();
    delete top;
    delete contextp;
 
    //pack up end info 
    Sdb_end_info *res = (Sdb_end_info*)malloc(sizeof(Sdb_end_info));
    res->program_name = get_program_name(img_file);
    res->fail = fail;
    res->sim_time = sim_time;
    res->clock_number = (sim_time - SIM_RESET_TIME) / 2;
    res->inst_number = inst_number;
    res->end_sys_time = get_sys_time_us();
    res->start_sys_time = start_sys_time;
    res->ipc = (double)res->inst_number / (double)res->clock_number;
    res->clock_per_sec = (double)res->clock_number / ((double)(res->end_sys_time - res->start_sys_time) / (double)1000000);
    return res;
}

int main(int argc, char** argv, char** env) {
    // 初始化
    bool fail = false;
    init_sdb();
    //
    int program_num = argc - 3;
    char* tfp_file = argv[1];
    char* diff_file = argv[2];
    printf("---------------------%s\n%s\n%s\n",argv[0],argv[1],argv[2]);
    // 加载默认程序
    if(program_num == 0){
        sim_main(argc, argv, tfp_file, diff_file, NULL);
    }
    // 回归测试
    Sdb_end_info *program_end_info[program_num];
    Sdb_end_info *info;
    int total_clock = 0, total_inst = 0;
    int fail_num = 0;
    // sim
    for(int i = 0; i < program_num; i++){
        char* img_file = argv[i + 3];
        Sdb_end_info *res;
        program_end_info[i] = sim_main(argc, argv, tfp_file, diff_file, img_file);
        fail_num += program_end_info[i]->fail;
    }
    // printf result
    printf("------------------------simulation report------------------------\n");
    for(int i = 0; i < program_num; i++){
        info = program_end_info[i];
        printf("%-30s: simtime=%6ld  ipc=%f clk/s=%6ld  ", info->program_name, info->sim_time, info->ipc, info->clock_per_sec);
        if(info->fail) Logc(ASNI_FG_RED, "FAIL");
        else Logc(ASNI_FG_GREEN, "PASS");
        if(info->fail) fail = true;
        total_clock += info->clock_number;
        total_inst  += info->inst_number;
    }
    double ipc = (double)total_inst / (double)total_clock;
    printf("total program number:%d, fail:%d, IPC=%f\n", program_num, fail_num, ipc);
    printf("-----------------------------------------------------------------\n");
    return fail;
}
