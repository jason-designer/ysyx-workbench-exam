import chisel3._
import chisel3.util._

class Execution extends Module{
    val io = IO(new Bundle{
        val decode_info = Flipped(new DecodeInfo)

        val op1 = Input(UInt(64.W))
        val op2 = Input(UInt(64.W))
        val pc  = Input(UInt(64.W))
        val imm = Input(UInt(64.W))

        val alu_out = Output(UInt(64.W))
        val bu_out  = Output(UInt(64.W))
        val mdu_out = Output(UInt(64.W))
        
    })
    val op1 = io.op1
    val op2 = io.op2
    val pc  = io.pc
    val imm = io.imm
    val fu_code  = io.decode_info.fu_code
    val alu_code = io.decode_info.alu_code
    val bu_code  = io.decode_info.bu_code
    val lu_code  = io.decode_info.lu_code
    val su_code  = io.decode_info.su_code
    val mdu_code = io.decode_info.mdu_code

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

    //mdu
    val mdu_out = MuxLookup(mdu_code, 0.U, Array(
        "b0000000001".U -> (op1 * op2),                                             //mul
        "b0000000010".U -> sext((op1 * op2), 4),                                    //mulw
        "b0000000100".U -> (op1.asSInt() / op2.asSInt()).asUInt(),                  //div
        "b0000001000".U -> (op1(31, 0).asSInt() / op2(31, 0).asSInt()).asUInt(),    //divw
        "b0000010000".U -> (op1 / op2),                 //divu
        "b0000100000".U -> (op1(31, 0) / op2(31, 0)),   //divuw
        "b0001000000".U -> (op1.asSInt() % op2.asSInt()).asUInt(),  //rem
        "b0010000000".U -> (op1(31, 0).asSInt() % op2(31, 0).asSInt()).asUInt(),  //remw
        "b0100000000".U -> (op1 % op2),  //remu
        "b1000000000".U -> (op1(31, 0) % op2(31, 0)),  //remuw
    ))


    //
    io.alu_out := alu_out
    io.bu_out  := bu_out
    io.mdu_out := mdu_out

}








