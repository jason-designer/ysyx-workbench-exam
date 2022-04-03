#include "VSimTop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "common.h"
#include "memory.h"
#include "halt.h"
#include "reg.h"
#include "difftest.h"


extern CPU_state cpu;

#define SIM_END_TIME 5000

int main(int argc, char** argv, char** env) {
    VerilatedContext* contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    VSimTop* top = new VSimTop{contextp};                 // top is the name of Module
    //trace on
    Verilated::traceEverOn(true);                   // open trace, so that it can generate waveforms
    VerilatedVcdC* tfp = new VerilatedVcdC;         // it is used for generating waveforms
    top->trace(tfp, 99);                            // Trace 99 levels of hierarchy,1 level means only trace top level signals
    //get arg
    char* tfp_file = argv[1];
    char* img_file = argv[2];
    //set the path of vcd
    tfp->open(tfp_file);   // set the path of the vcd file, you need to mkdir before running it
    /****************************************************************************/

    
    uint64_t size = load_program(img_file);
    init_difftest("/home/zgs/project/ysyx-workbench/nemu/build/riscv64-nemu-interpreter-so", size, DIFFTEST_PORT);
    //init_difftest("/home/zgs/project/ysyx-workbench/nemu/tools/spike-diff/build/riscv64-spike-so", size, DIFFTEST_PORT);

    int sim_time = 0;                             // sim time
    uint64_t pre_pc = 0;
    uint64_t pc = 0;
    while (contextp->time() < SIM_END_TIME && !contextp->gotFinish()) { 
        top->reset = sim_time < 2 ? 1 : 0;
        top->clock = sim_time % 2;

        top->eval();
        pre_pc = pc;
        pc = top->io_imem_addr;
        top->io_imem_data = read_memory(pc, 4);                                                              
        top->eval();                                
        tfp->dump(contextp->time());

        //rtl debug
        if(sim_time >= 2 && sim_time % 2 == 0){
            //halt
            if(cpu_halt[0]) {
                Log("Detected ebreak, sim quit");
                if(!cpu_gpr[10]) Logc(ASNI_FG_GREEN,"halt good trap");
                else Logc(ASNI_FG_RED,"halt bad trap");
                break;
            }
            //difftest
            if(sim_time >= 4 && sim_time % 2 == 0){
                isa_reg_update(pc, cpu_gpr);
                //isa_reg_display();
                if(!difftest_step(pre_pc)) {
                    Log("difftest detect wrong, sim quit");
                    break;
                }
            }
            
        }
        
        contextp->timeInc(1);
        sim_time++;
    }


    /***********************************************************************/
    tfp->close();
    delete top;
    delete contextp;
    return 0;
}
