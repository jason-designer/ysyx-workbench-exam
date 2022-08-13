import chisel3._
import chisel3.util.experimental._

class RegFile extends Module{
  val io = IO(new Bundle{
    val rs1_addr = Input(UInt(5.W))
    val rs2_addr = Input(UInt(5.W))
    val rs1_data = Output(UInt(64.W))
    val rs2_data = Output(UInt(64.W))
    val rd_en    = Input(Bool())
    val rd_addr  = Input(UInt(5.W))
    val rd_data  = Input(UInt(64.W))
  })
  val rf = Module(new RegFileBlackBox)
  rf.io.clock     := clock
  rf.io.reset     := reset
  rf.io.rs1_addr  := io.rs1_addr 
  rf.io.rs2_addr  := io.rs2_addr
  io.rs1_data     := rf.io.rs1_data
  io.rs2_data     := rf.io.rs2_data
  rf.io.rd_en     := io.rd_en  
  rf.io.rd_addr   := io.rd_addr
  io.rd_data      := rf.io.rd_data
}

class RegFileBlackBox extends BlackBox with HasBlackBoxInline{
    val io = IO(new Bundle{
        val clk      = Input(Clock())
        val reset    = Input(Reset())
        val rd_en    = Input(Bool())
        val rs1_addr = Input(UInt(5.W))
        val rs2_addr = Input(UInt(5.W))
        val rd_addr  = Input(UInt(5.W))
        val rs1_data = Output(UInt(64.W))
        val rs2_data = Output(UInt(64.W))
        val rd_data  = Input(UInt(64.W))
    })

    setInline("RegFile.v",
            """
           |import "DPI-C" function void set_gpr_ptr(input logic [63:0] a []);
           |
           |module RegFile(
           |            input  clk,
           |            input  reset,
           |            input  rd_en,
           |            input  [63:0] rs1_addr,
           |            input  [63:0] rs2_addr,
           |            input  [63:0] rd_addr,
           |            output [63:0] rs1_data,
           |            output [63:0] rs2_data,
           |            input  [63:0] rd_data
           |            );
           |
           |  reg [63:0] rf [0:31];
           |  initial set_gpr_ptr(rf);  // rf为通用寄存器的二维数组变量
           |
           |  assign rs1_data = rs1_addr == 5'b0 ? 64'b0 : rf[rs1_addr];
           |  assign rs2_data = rs2_addr == 5'b0 ? 64'b0 : rf[rs2_addr];
           |
           |  always @(posedge clk) begin
           |    if (reset) begin 
           |      integer i;
           |      for(i = 0; i < 32; i = i + 1) begin
           |        rf[i] <= 64'b0;
           |      end
           |    end else begin
           |      rf[rd_addr] <= rd_en ? (rd_addr == 5'b0 ? 64'b0 : rd_data) : rf[rd_addr]; 
           |    end
           |  end
           |endmodule
           |
            """.stripMargin)
}


// class RegFile extends Module {
//   val io = IO(new Bundle{
//     val rs1_addr = Input(UInt(5.W))
//     val rs2_addr = Input(UInt(5.W))
//     val rs1_data = Output(UInt(64.W))
//     val rs2_data = Output(UInt(64.W))
//     val rd_addr = Input(UInt(5.W))
//     val rd_data = Input(UInt(64.W))
//     val rd_en = Input(Bool())
//   })

//   val rf = RegInit(VecInit(Seq.fill(32)(0.U(64.W))))

//   when (io.rd_en && (io.rd_addr =/= 0.U)) {
//     rf(io.rd_addr) := io.rd_data;
//   }

//   io.rs1_data := Mux((io.rs1_addr =/= 0.U), rf(io.rs1_addr), 0.U)
//   io.rs2_data := Mux((io.rs2_addr =/= 0.U), rf(io.rs2_addr), 0.U)

//   /* ------------------------------------ use difftest ---------------------------------------- */
//   BoringUtils.addSource(rf(10), "rf_a0")
  
// }
