#include "VSimTop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "common.h"
#include "memory.h"
#include "halt.h"
#include "reg.h"
#include "difftest.h"
#include "device.h"
#include <sys/time.h>

/***************** sdb config *******************/ 
#define DIFFTEST
#define TRACE
#define SIM_RESET_TIME 2
/************************************************/

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
    setbuf(stdout, NULL);
    uint64_t size = load_program(img_file);
    device_init();

    #ifdef DIFFTEST
    //init_difftest("/home/zgs/project/ysyx-workbench/nemu/build/riscv64-nemu-interpreter-so", size, DIFFTEST_PORT);
    init_difftest("/home/zgs/project/ysyx-workbench/nemu/tools/spike-diff/build/riscv64-spike-so", size, DIFFTEST_PORT);
    #else
    cpu_difftest_valid = 0;
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
        // trace
        #ifdef TRACE                      
        tfp->dump(contextp->time());
        #endif
        // SDL quit
        if(sdb_state == SDB_QUIT) break;
        // rtl debug
        if(sim_time >= SIM_RESET_TIME && sim_time % 2 == 0){
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
                if(cpu_difftest_valid) {
                    start_difftest = true;
                    pre_pc = pc;
                    pc = cpu_pc;
                }
            }
            else{
                if(cpu_difftest_valid){
                    inst_number++;  //记录commit的指令数
                    pre_pc = pc;
                    pc = cpu_pc;
                    isa_reg_update(pc, cpu_gpr);
                    if(!difftest_step(pre_pc)) {
                    sdb_state = SDB_DIFFTEST_WRONG;
                    break;
                }
                }
            }
            #else
            if(cpu_difftest_valid){
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
        printf("%-30s: simtime=%6ld  ipc=%f clk/s=%ld  ", info->program_name, info->sim_time, info->ipc, info->clock_per_sec);
        if(info->fail) Logc(ASNI_FG_RED, "FAIL");
        else Logc(ASNI_FG_GREEN, "PASS");
        total_clock += info->clock_number;
        total_inst  += info->inst_number;
    }
    double ipc = (double)total_inst / (double)total_clock;
    printf("total program number:%d, fail:%d, IPC=%f\n", program_num, fail_num, ipc);
    printf("-----------------------------------------------------------------\n");
}
