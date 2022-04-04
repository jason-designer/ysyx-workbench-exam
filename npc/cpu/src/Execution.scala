import chisel3._
import chisel3.util._

class Execution extends Module{
    val io = IO(new Bundle{
        val decode_info = Flipped(new DecodeInfo)

        val op1 = Input(UInt(64.W))
        val op2 = Input(UInt(64.W))
        val pc  = Input(UInt(64.W))
        val imm = Input(UInt(64.W))

        val out = Output(UInt(64.W))
        val jump_en = Output(Bool())
        val jump_pc = Output(UInt(64.W))

        val dmem = new DmemIO
    })
    val op1 = io.op1
    val op2 = io.op2
    val pc  = io.pc
    val imm = io.imm
    val fu_code = io.decode_info.fu_code
    val alu_code = io.decode_info.alu_code
    val bu_code = io.decode_info.bu_code
    val lu_code = io.decode_info.lu_code
    val su_code = io.decode_info.su_code
    val dmem = io.dmem
    //
    def sext(v:UInt, len:Int):UInt = len match{
        case 1 => Cat(Fill(56, v(7)), v(7, 0))
        case 2 => Cat(Fill(48, v(15)), v(15, 0))
        case 4 => Cat(Fill(32, v(31)), v(31, 0))
    }
    def zext(v:UInt, len:Int):UInt = len match{
        case 1 => Cat(Fill(56, 0.U), v(7, 0))
        case 2 => Cat(Fill(48, 0.U), v(15, 0))
        case 4 => Cat(Fill(32, 0.U), v(31, 0))
    }

    //alu
    val alu_out = MuxLookup(alu_code, 0.U, Array(
        "b0000000000000001".U -> (op1 + op2),                   //add
        "b0000000000000010".U -> sext((op1 + op2), 4),            //addw
        "b0000000000000100".U -> (op1 - op2),                   //sub
        "b0000000000001000".U -> sext((op1 - op2), 4),            //subw
        "b0000000000010000".U -> (op2 + pc),                    //imm,pc
        "b0000000000100000".U -> (op1 << op2(5, 0))(63, 0),     //sll
        "b0000000001000000".U -> (op1 >> op2(5, 0)),            //srl
        "b0000000010000000".U -> (op1.asSInt() >> op2(5, 0)).asUInt(),   //sra        
        "b0000000100000000".U -> sext((op1(31, 0) << op2(4, 0)), 4),    //sllw
        "b0000001000000000".U -> sext((op1(31, 0) >> op2(4, 0)), 4),    //srlw
        "b0000010000000000".U -> sext((op1(31, 0).asSInt() >> op2(4, 0)).asUInt(), 4),   //sraw        
        "b0000100000000000".U -> (op1 ^ op2),           //xor
        "b0001000000000000".U -> (op1 | op2),           //or
        "b0010000000000000".U -> (op1 & op2),           //and
        "b0100000000000000".U -> (op1.asSInt() < op2.asSInt()),  //slt
        "b1000000000000000".U -> (op1 < op2),           //sltu
    ))

    //bu
    val bu_out = Mux(bu_code === "b10000000".U || bu_code === "b01000000".U, pc + 4.U, 0.U)
    val bu_jump_pc = Mux(bu_code === "b10000000".U, ((op1 + op2) & "hfffffffffffffffe".U), pc + imm)
    val bu_jump_en = MuxLookup(bu_code, 0.U, Array(
        "b00000001".U -> (op1 === op2),                     //beq
        "b00000010".U -> (op1 =/= op2),                     //bne
        "b00000100".U -> (op1.asSInt()  <  op2.asSInt()),   //blt
        "b00001000".U -> (op1.asSInt()  >= op2.asSInt()),   //bge
        "b00010000".U -> (op1  <  op2),                     //bltu
        "b00100000".U -> (op1  >= op2),                     //bgeu
        "b01000000".U -> true.B,                            //jal
        "b10000000".U -> true.B,                            //jalr
    ))
    
    //lu
    val lu_offset = op1 + op2
    val lu_shift = lu_offset(2, 0) << 3
    val lu_ren = lu_code =/= 0.U
    val lu_raddr = lu_offset & "hfffffffffffffff8".U
    val lu_out = MuxLookup(lu_code, 0.U, Array(
        "b0000001".U -> sext((dmem.rdata) >> lu_shift, 1),  //lb
        "b0000010".U -> sext((dmem.rdata) >> lu_shift, 2),  //lh
        "b0000100".U -> sext((dmem.rdata) >> lu_shift, 4),  //lw
        "b0001000".U -> ((dmem.rdata) >> lu_shift),         //ld
        "b0010000".U -> zext((dmem.rdata) >> lu_shift, 1),  //lbu
        "b0100000".U -> zext((dmem.rdata) >> lu_shift, 2),  //lhu
        "b1000000".U -> zext((dmem.rdata) >> lu_shift, 4),  //lwu
    ))
    
    //su
    val su_offset = op1 + imm
    val su_shift  = su_offset(2, 0) << 3
    val su_wen    = su_code =/= 0.U
    val su_waddr  = su_offset & "hfffffffffffffff8".U
    val su_wdata  = op2 << su_shift
    val su_wmask  = MuxLookup(su_code, 0.U, Array(
        "b0001".U -> ("b00000001".U << su_offset(2, 0)),   //sb
        "b0010".U -> ("b00000011".U << su_offset(2, 0)),   //sh
        "b0100".U -> ("b00001111".U << su_offset(2, 0)),   //sw
        "b1000".U -> "b11111111".U ,                //sd
    ))
    val su_out = 0.U


    //
    io.out := MuxLookup(fu_code, 0.U, Array(
        "b000001".U -> alu_out,
        "b000010".U -> bu_out,
        "b000100".U -> lu_out,
        "b001000".U -> su_out,
    ))
    io.jump_en := bu_jump_en
    io.jump_pc := bu_jump_pc
    dmem.ren := lu_ren
    dmem.raddr := lu_raddr
    dmem.wen := su_wen
    dmem.waddr := su_waddr
    dmem.wdata := su_wdata
    dmem.wmask := su_wmask
    

}








