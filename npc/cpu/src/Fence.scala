import chisel3._
import chisel3.util._
import Instructions._

class FenceIO extends Bundle{
    val req = Output(Bool())
    val done = Input(Bool())
}

class Fence extends Module{
    val io = IO(new Bundle{
        val go      = Input(Bool())
        val ok      = Output(Bool())
        val ifence  = new FenceIO
        val dfence  = new FenceIO
    })
    // state machine
    val idle :: run_fence :: dcache :: icache :: done :: Nil = Enum(5)
    val state = RegInit(idle)

    switch(state){
        is(idle){
            when(io.go){state := run_fence}
        }
        is(run_fence){          // 在这个状态会输出ok，让fence指令流掉。如果不留掉的话，icache的v被置为0，会导致重复取fence指令。
            state := dcache
        }
        is(dcache){
            when(io.dfence.done){state := icache}
        }
        is(icache){
            when(io.ifence.done){state := done}
        }
        is(done){
            state := idle
        }
    }
    // output
    io.ok := (state === idle && io.go === false.B) || state === done || state === run_fence
    io.dfence.req := state === dcache
    io.ifence.req := state === icache
}


