#include "VSimTop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "common.h"
#include "memory.h"
#include "halt.h"
#include "reg.h"
#include "difftest.h"


enum { SDB_RUNNING, SDB_HIT_GOOD_TRAP, SDB_HIT_BAD_TRAP, SDB_DIFFTEST_WRONG, SDB_END_TIME};

#define SIM_END_TIME 20000



int sim_main(int argc, char** argv, char* tfp_file, char* img_file){
    VerilatedContext* contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    VSimTop* top = new VSimTop{contextp};                 // top is the name of Module
    //trace on
    Verilated::traceEverOn(true);                   // open trace, so that it can generate waveforms
    VerilatedVcdC* tfp = new VerilatedVcdC;         // it is used for generating waveforms
    top->trace(tfp, 99);                            // Trace 99 levels of hierarchy,1 level means only trace top level signals
    //get arg
    //char* tfp_file = argv[1];
    //char* img_file = argv[2];
    //set the path of vcd
    tfp->open(tfp_file);   // set the path of the vcd file, you need to mkdir before running it
    /****************************************************************************/

    uint64_t size = load_program(img_file);
    //init_difftest("/home/zgs/project/ysyx-workbench/nemu/build/riscv64-nemu-interpreter-so", size, DIFFTEST_PORT);
    init_difftest("/home/zgs/project/ysyx-workbench/nemu/tools/spike-diff/build/riscv64-spike-so", size, DIFFTEST_PORT);

    int sdb_state = SDB_RUNNING;
    int sim_time = 0;                             // sim time
    uint64_t pre_pc = 0;
    uint64_t pc = 0;
    while (sim_time < SIM_END_TIME) { 
        top->reset = sim_time < 2 ? 1 : 0;
        top->clock = sim_time % 2;

        top->eval();
        if(sim_time % 2 == 1) pre_pc = pc;
        pc = top->io_imem_addr;
        top->io_imem_data = read_memory(pc, 4);                                                              
        top->eval();                                
        tfp->dump(contextp->time());

        //rtl debug
        if(sim_time >= 2 && sim_time % 2 == 0){
            //halt
            if(cpu_halt[0]) {
                Log("Detected ebreak, sim quit");
                if(!cpu_gpr[10]) sdb_state = SDB_HIT_GOOD_TRAP;
                else sdb_state = SDB_HIT_BAD_TRAP;
                break;
            }
            //difftest
            if(sim_time >= 4 && sim_time % 2 == 0){
                isa_reg_update(pc, cpu_gpr);
                //isa_reg_display();
                if(!difftest_step(pre_pc)) {
                    sdb_state = SDB_DIFFTEST_WRONG;
                    break;
                }
            }
        }
        
        contextp->timeInc(1);
        sim_time++;
    }
    if(sim_time >= SIM_END_TIME) sdb_state = SDB_END_TIME;
    switch(sdb_state){
        case SDB_HIT_GOOD_TRAP:  Logc(ASNI_FG_GREEN,"halt good trap"); break;
        case SDB_HIT_BAD_TRAP:   Logc(ASNI_FG_RED,"halt bad trap"); break;
        case SDB_DIFFTEST_WRONG: Logc(ASNI_FG_RED, "difftest detect wrong, sim quit"); break;
        case SDB_END_TIME: Logc(ASNI_FG_RED, "out of sim time"); break;
    }
    int fail = 1;
    if(sdb_state == SDB_HIT_GOOD_TRAP) fail = 0;

    /***********************************************************************/
    tfp->close();
    delete top;
    delete contextp;
    return fail;
}

int main(int argc, char** argv, char** env) {
    int program_num = argc - 2;
    int program_fail[program_num];
    int fail_num = 0;
    char* tfp_file = argv[1];
    // sim
    for(int i = 0; i < program_num; i++){
        char* img_file = argv[i + 2];
        program_fail[i] = sim_main(argc, argv, tfp_file, img_file);
        fail_num += program_fail[i];
    }
    // printf result
    for(int i = 0; i < program_num; i++){
        printf("%s:", argv[i+2]);
        if(program_fail[i]) Logc(ASNI_FG_RED, "FAIL");
        else Logc(ASNI_FG_GREEN, "PASS");
    }
    printf("total program number:%d, fail:%d\n", program_num, fail_num);



}
