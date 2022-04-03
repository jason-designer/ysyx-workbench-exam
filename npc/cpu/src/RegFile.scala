import chisel3._
import chisel3.util._
import chisel3.experimental._

class RegFile extends BlackBox with HasBlackBoxInline{
    val io = IO(new Bundle{
        val clk      = Input(Clock())
        val reset    = Input(Reset())
        val rs1_en   = Input(Bool())
        val rs2_en   = Input(Bool())
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
           |            input  rs1_en,
           |            input  rs2_en,
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
           |  assign rs1_data = (!rs1_en || rs1_addr == 5'b0) ? 64'b0 : rf[rs1_addr];
           |  assign rs2_data = (!rs2_en || rs2_addr == 5'b0) ? 64'b0 : rf[rs2_addr];
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
