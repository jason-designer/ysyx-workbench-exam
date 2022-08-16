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
// #define ITRACE
// #define MTRACE 
#define DTRACE

#define SIM_RESET_TIME 2
/************************************************/
#include "./axi4/axi.h"
#include "./axi4/my_axi4.hpp"
#include <iostream>

using std::cout;
using std::endl;

void dump_axi_read(axi4_ref<64,64,4> &axi) {
    cout << "arid\t" << (unsigned long)axi.arid << endl;
    // cout << "araddr\t" << (unsigned long)axi.araddr << endl;
    printf("araddr\t%016lx\n",axi.araddr);
    cout << "arlen\t" << (unsigned long)axi.arlen << endl;
    cout << "arsize\t" << (unsigned long)axi.arsize << endl;
    cout << "arburst\t" << (unsigned long)axi.arburst << endl;
    cout << "arvalid\t" << (unsigned long)axi.arvalid << endl;
    cout << "arready\t" << (unsigned long)axi.arready << endl;
    cout << "rid\t" << (unsigned long)axi.rid << endl;
    // cout << "rdata\t" << (unsigned long)axi.rdata << endl;
    printf("rdata\t%016lx\n",axi.rdata);
    cout << "rresp\t" << (unsigned long)axi.rresp << endl;
    cout << "rlast\t" << (unsigned long)axi.rlast << endl;
    cout << "rvalid\t" << (unsigned long)axi.rvalid << endl;
    cout << "rready\t" << (unsigned long)axi.rready << endl;
}

void axi_to_cpu(VSimTop* top, axi4_ref<64,64,4>& axi_ref){
    // aw
    top->io_master_awready  = axi_ref.awready;
    // w
    top->io_master_wready   = axi_ref.wready;
    // b
    top->io_master_bvalid   = axi_ref.bvalid;
    top->io_master_bresp    = axi_ref.bresp;
    top->io_master_bid      = axi_ref.bid;
    // ar
    top->io_master_arready  = axi_ref.arready;
    // r
    top->io_master_rvalid   = axi_ref.rvalid;
    top->io_master_rresp    = axi_ref.rresp;
    top->io_master_rdata    = axi_ref.rdata;
    top->io_master_rlast    = axi_ref.rlast;
    top->io_master_rid      = axi_ref.rid;
}

void cpu_to_axi(VSimTop* top, axi4_ref<64,64,4>& axi_ref){
    // aw
    axi_ref.awvalid = top->io_master_awvalid;
    axi_ref.awaddr  = top->io_master_awaddr - 0x80000000;
    axi_ref.awid    = top->io_master_awid;
    axi_ref.awlen   = top->io_master_awlen;
    axi_ref.awsize  = top->io_master_awsize;
    axi_ref.awburst = top->io_master_awburst;
    // w
    axi_ref.wvalid  = top->io_master_wvalid;
    axi_ref.wdata   = top->io_master_wdata;
    axi_ref.wstrb   = top->io_master_wstrb;
    axi_ref.wlast   = top->io_master_wlast;
    // b
    axi_ref.bready  = top->io_master_bready;
    // ar
    axi_ref.arvalid = top->io_master_arvalid;
    axi_ref.araddr  = top->io_master_araddr - 0x80000000;
    axi_ref.arid    = top->io_master_arid;
    axi_ref.arlen   = top->io_master_arlen;
    axi_ref.arsize  = top->io_master_arsize;
    axi_ref.arburst = top->io_master_arburst;
    // r
    axi_ref.rready  = top->io_master_rready;
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

Sdb_end_info* sim_main(int argc, char** argv, char* tfp_file, char* img_file){
    VerilatedContext* contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    VSimTop* top = new VSimTop{contextp};           // top is the name of Module
    //trace on
    Verilated::traceEverOn(true);                   // open trace, so that it can generate waveforms
    VerilatedVcdC* tfp = new VerilatedVcdC;         // it is used for generating waveforms
    top->trace(tfp, 99);                            // Trace 99 levels of hierarchy,1 level means only trace top level signals
    tfp->open(tfp_file);                            // set the path of the vcd file, you need to mkdir before running it
    /****************************************************************************/
    axi4_mem<64,64,4> mem(0x8000000);
    axi4<64,64,4> axi;
    axi4_ref<64,64,4> axi_ref(axi);

    uint64_t s = axi_load_program<64,64,4> (img_file, mem);


    setbuf(stdout, NULL);
    uint64_t size = load_program(img_file);
    device_init();

    #ifdef DIFFTEST
    init_difftest("/home/zgs/project/ysyx-workbench/nemu/build/riscv64-nemu-interpreter-so", size, DIFFTEST_PORT);
    // init_difftest("/home/zgs/project/ysyx-workbench/nemu/tools/spike-diff/build/riscv64-spike-so", size, DIFFTEST_PORT);
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
    while (sdb_state == SDB_RUNNING && sim_time <= 100) { 
        // device
        device_update(&sdb_state);
        // clock and reset
        top->reset = sim_time < SIM_RESET_TIME ? 1 : 0;
        top->clock = sim_time % 2;                                                          
        top->eval();   
        if(sim_time % 2 == 1){
            cpu_to_axi(top, axi_ref);
            mem.beat(axi_ref);
            axi_to_cpu(top, axi_ref);
            dump_axi_read(axi_ref);
            printf("---------------\n");
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
                disassemble(str, 100, 0x80000000, (uint8_t*)&inst, 4);
                // printf("pc = %lx : %08x : %s\n", commit_info.pc, commit_info.inst, str);
                char buf[100];
                sprintf(buf, "pc = %lx : %08x : %s", commit_info.pc, commit_info.inst, str);
                iringbuf_log_once(buf);
            }
            #endif
            // mtrace
            #ifdef MTRACE 
            if(dmem_info.valid == 1 && (dmem_info.ren == 1 || dmem_info.wen == 1)){
                void dmem_trace();
                dmem_trace();
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
    iringbuf_print();
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
    init_sdb();
    //
    int program_num = argc - 2;
    char* tfp_file = argv[1];
    // 加载默认程序
    if(program_num == 0){
        sim_main(argc, argv, tfp_file, NULL);
    }
    // 回归测试
    Sdb_end_info *program_end_info[program_num];
    Sdb_end_info *info;
    int total_clock = 0, total_inst = 0;
    int fail_num = 0;
    // sim
    for(int i = 0; i < program_num; i++){
        char* img_file = argv[i + 2];
        Sdb_end_info *res;
        program_end_info[i] = sim_main(argc, argv, tfp_file, img_file);
        fail_num += program_end_info[i]->fail;
    }
    // printf result
    printf("------------------------simulation report------------------------\n");
    for(int i = 0; i < program_num; i++){
        info = program_end_info[i];
        printf("%-30s: simtime=%6ld  ipc=%f clk/s=%6ld  ", info->program_name, info->sim_time, info->ipc, info->clock_per_sec);
        if(info->fail) Logc(ASNI_FG_RED, "FAIL");
        else Logc(ASNI_FG_GREEN, "PASS");
        total_clock += info->clock_number;
        total_inst  += info->inst_number;
    }
    double ipc = (double)total_inst / (double)total_clock;
    printf("total program number:%d, fail:%d, IPC=%f\n", program_num, fail_num, ipc);
    printf("-----------------------------------------------------------------\n");
}
