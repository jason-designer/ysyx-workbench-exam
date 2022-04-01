import chisel3._


class RegFile extends Module{
    val io = IO(Bundle{
        val rs1_addr = Input(UInt(5.W))
        val rs2_addr = Input(UInt(5.W))
        val rd_addr  = Input(UInt(5.W))
        val rs1_en = Input(Bool())
        val rs2_en = Input(Bool())
        val rd_en = Input(Bool())
        
    })


}
