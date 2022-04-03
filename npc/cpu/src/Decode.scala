import chisel3._
import chisel3.util._
import Instructions._

class DecodeInfo extends Bundle{
    val fu_code = Output(UInt())
    val alu_code = Output(UInt())
}
class Decode extends Module{
    val io = IO(new Bundle{
        val pc = Input(UInt(64.W))
        val inst = Input(UInt(32.W))
        
        val decode_info = new DecodeInfo

        val rs1_en   = Output(Bool())
        val rs2_en   = Output(Bool())
        val rd_en    = Output(Bool())
        val rs1_addr = Output(UInt(5.W))
        val rs2_addr = Output(UInt(5.W))
        val rd_addr  = Output(UInt(5.W))
        val rs1_data = Input(UInt(64.W))
        val rs2_data = Input(UInt(64.W))

        val op1 = Output(UInt(64.W))
        val op2 = Output(UInt(64.W))
        val op3 = Output(UInt(64.W))
    })
    val inst = io.inst

    //get inst
    val addi = inst === ADDI


    //get fu_code
    //alu
    val alu_add = addi
    val alu_code = addi
    val alu_en = alu_code =/= 0.U

    val fu_code = Cat(alu_en)


    //get inst type
    val type_r = false.B
    val type_i = addi
    val type_s = false.B
    val type_b = false.B
    val type_u = false.B
    val type_j = false.B
    val inst_type = Cat(type_r, type_i, type_s, type_b, type_u, type_j)

    //get imm
    val imm_r = 0.U
    val imm_i = Cat(Fill(52, inst(31)), inst(31, 20))
    val imm_s = Cat(Fill(52, inst(31)), inst(31, 25), inst(11, 7))
    val imm_b = Cat(Fill(43, inst(31)), inst(31), inst(7), inst(30, 25), inst(11, 8), 0.U)
    val imm_u = Cat(Fill(32, inst(31)), inst(31, 12), Fill(12, 0.U))
    val imm_j = Cat(Fill(43, inst(31)), inst(31), inst(19, 12), inst(20), inst(30, 21), 0.U)
    val imm = MuxLookup(inst_type, 0.U, Array(
        "b100000".U -> imm_r,
        "b010000".U -> imm_i,
        "b001000".U -> imm_s,
        "b000100".U -> imm_b,
        "b000010".U -> imm_u,
        "b000001".U -> imm_j,
    ))


    //
    io.decode_info.fu_code  := fu_code
    io.decode_info.alu_code := alu_code

    io.rs1_addr := inst(19, 15)
    io.rs2_addr := inst(24, 20)
    io.rd_addr  := inst(11, 7)
    
    io.rs1_en := type_r || type_i || type_s || type_b 
    io.rs2_en := type_r || type_s || type_b 
    io.rd_en  := type_r || type_i || type_u || type_j

    //
    io.op1 := Mux(io.rs1_en, io.rs1_data, 0.U)
    io.op2 := Mux(io.rs2_en, io.rs2_data, imm)
    io.op3 := 0.U
}


