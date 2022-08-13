import chisel3._
import chisel3.util._
import Instructions._

object Decode_constant{
    val fu_code_length      = 7
    val alu_code_length     = 16
    val bu_code_length      = 8
    val lu_code_length      = 7
    val su_code_length      = 4
    val mu_code_length      = 2
    val du_code_length      = 8
    val csru_code_length    = 8
}
class DecodeInfo extends Bundle{
    val fu_code     = Output(UInt())
    val alu_code    = Output(UInt())
    val bu_code     = Output(UInt())
    val lu_code     = Output(UInt())
    val su_code     = Output(UInt())
    val mu_code     = Output(UInt())
    val du_code     = Output(UInt())
    val csru_code   = Output(UInt())
}
class Decode extends Module{
    val io = IO(new Bundle{
        val pc = Input(UInt(64.W))
        val inst = Input(UInt(32.W))
        
        val rs1_en   = Output(Bool())
        val rs2_en   = Output(Bool())
        val rs1_addr = Output(UInt(5.W))
        val rs2_addr = Output(UInt(5.W))
        val rs1_data = Input(UInt(64.W))
        val rs2_data = Input(UInt(64.W))

        val rd_en    = Output(Bool())
        val rd_addr  = Output(UInt(5.W))

        val decode_info = new DecodeInfo
        val jump_en = Output(Bool())
        val jump_pc = Output(UInt(64.W))

        val op1 = Output(UInt(64.W))
        val op2 = Output(UInt(64.W))
        val imm = Output(UInt(64.W))
        val putch = Output(Bool())

        val mtvec = Input(UInt(64.W))
        val mepc  = Input(UInt(64.W))

        val intr = Input(Bool())
    })
    val inst = io.inst

    //get inst
    //shifts
    val sll = inst === SLL
    val srl = inst === SRL
    val sra = inst === SRA
    val slli = inst === SLLI
    val srli = inst === SRLI
    val srai = inst === SRAI
    val sllw = inst === SLLW
    val srlw = inst === SRLW
    val sraw = inst === SRAW
    val slliw = inst === SLLIW
    val srliw = inst === SRLIW
    val sraiw = inst === SRAIW
    //arithmetic
    val add     = inst === ADD
    val addw    = inst === ADDW
    val addi    = inst === ADDI
    val addiw   = inst === ADDIW
    val sub     = inst === SUB
    val subw    = inst === SUBW
    val lui     = inst === LUI
    val auipc   = inst === AUIPC
    //logical
    val xor     = inst === XOR
    val or      = inst === OR
    val and     = inst === AND
    val xori    = inst === XORI
    val ori     = inst === ORI
    val andi    = inst === ANDI
    //compare
    val slt     = inst === SLT
    val sltu    = inst === SLTU
    val slti    = inst === SLTI
    val sltiu   = inst === SLTIU
    //branches
    val beq     = inst === BEQ
    val bne     = inst === BNE
    val blt     = inst === BLT
    val bge     = inst === BGE
    val bltu    = inst === BLTU
    val bgeu    = inst === BGEU
    //jump
    val jal     = inst === JAL
    val jalr    = inst === JALR
    //load
    val lb      = inst === LB
    val lh      = inst === LH
    val lw      = inst === LW
    val ld      = inst === LD
    val lbu     = inst === LBU
    val lhu     = inst === LHU
    val lwu     = inst === LWU
    //save
    val sb      = inst === SB
    val sh      = inst === SH
    val sw      = inst === SW
    val sd      = inst === SD
    //mul and div
    val mul     = inst === MUL
    val mulw    = inst === MULW
    val div     = inst === DIV
    val divw    = inst === DIVW
    val divu    = inst === DIVU
    val divuw   = inst === DIVUW
    val rem     = inst === REM
    val remw    = inst === REMW
    val remu    = inst === REMU
    val remuw   = inst === REMUW
    // csr
    val ecall   = inst === ECALL
    val mret    = inst === MRET
    val csrrs   = inst === CSRRS
    val csrrw   = inst === CSRRW
    val csrrc   = inst === CSRRC
    val csrrsi  = inst === CSRRSI
    val csrrwi  = inst === CSRRWI
    val csrrci  = inst === CSRRCI

    // printf
    val putch   = inst === PUTCH
    io.putch := putch

    //---------------------------------------get fu_code
    //alu
    val alu_add   = add || addi || lui
    val alu_addw  = addw || addiw
    val alu_sub   = sub
    val alu_subw  = subw
    val alu_auipc = auipc

    val alu_sll   = sll  || slli
    val alu_srl   = srl  || srli
    val alu_sra   = sra  || srai
    val alu_sllw  = sllw || slliw
    val alu_srlw  = srlw || srliw
    val alu_sraw  = sraw || sraiw

    val alu_xor   = xor  || xori
    val alu_or    = or   || ori
    val alu_and   = and  || andi

    val alu_slt   = slt  || slti
    val alu_sltu  = sltu || sltiu

    val alu_code = Cat(alu_sltu, alu_slt, alu_and, alu_or, alu_xor, alu_sraw, alu_srlw, alu_sllw, alu_sra, alu_srl, alu_sll, alu_auipc, alu_subw, alu_sub, alu_addw, alu_add)
    val alu_en   = alu_code =/= 0.U
    //bu
    val bu_code = Cat(jalr, jal, bgeu, bltu, bge, blt, bne, beq)
    val bu_en   = bu_code =/= 0.U
    //lu
    val lu_code = Cat(lwu, lhu, lbu, ld, lw, lh, lb)
    val lu_en   = lu_code =/= 0.U
    //su
    val su_code = Cat(sd, sw, sh, sb)
    val su_en   = su_code =/= 0.U
    //mu
    val mu_code = Cat(mulw, mul)
    val mu_en   = mu_code =/= 0.U
    //du
    val du_code = Cat(remuw, remu, remw, rem, divuw, divu, divw, div)
    val du_en   = du_code =/= 0.U
    //csrrs
    val csru_code = Cat(csrrci, csrrwi, csrrsi, csrrc, csrrw, csrrs, mret, ecall)
    val csr_en    = csru_code =/= 0.U
    //fu_code
    val fu_code = Cat(csr_en, du_en, mu_en, su_en, lu_en, bu_en, alu_en)
  
    //----------------------------------------get inst type
    val type_r =    sll   || srl   || sra   || sllw  || srlw   || sraw   ||
                    add   || addw  || sub   || subw  ||
                    xor   || or    || and   ||
                    slt   || sltu  ||
                    mul   || mulw  ||
                    div   || divw  || divu  || divuw ||
                    rem   || remw  || remu  || remuw ||
                    mret
    val type_i =    slli  || srli  || srai  || slliw || srliw  || sraiw  ||
                    addi  || addiw ||
                    xori  || ori   || andi  ||
                    slti  || sltiu ||
                    jalr  ||
                    lb    || lh    || lw    || ld    || lbu    || lhu    || lwu ||
                    ecall || csrrs || csrrw || csrrc || csrrwi || csrrci || csrrsi
    val type_s =    sb    || sh    || sw    || sd
    val type_b =    beq   || bne   || blt   || bge   || bltu   || bgeu
    val type_u =    lui   || auipc 
    val type_j =    jal
    val inst_type = Cat(type_r, type_i, type_s, type_b, type_u, type_j)

    //-------------------------------------------get imm
    val imm_r = 0.U
    val imm_i = Cat(Fill(52, inst(31)), inst(31, 20))
    val imm_s = Cat(Fill(52, inst(31)), inst(31, 25), inst(11, 7))
    val imm_b = Cat(Fill(51, inst(31)), inst(31), inst(7), inst(30, 25), inst(11, 8), 0.U)
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
    io.decode_info.fu_code   := fu_code
    io.decode_info.alu_code  := alu_code
    io.decode_info.bu_code   := bu_code
    io.decode_info.lu_code   := lu_code
    io.decode_info.su_code   := su_code
    io.decode_info.mu_code   := mu_code
    io.decode_info.du_code   := du_code
    io.decode_info.csru_code := csru_code

    io.rs1_addr := inst(19, 15)
    io.rs2_addr := inst(24, 20)
    io.rd_addr  := inst(11, 7)
    
    io.rs1_en := type_r || type_i || type_s || type_b 
    io.rs2_en := type_r || type_s || type_b 
    io.rd_en  := type_r || type_i || type_u || type_j

    io.op1 := Mux(io.rs1_en, io.rs1_data, 0.U)
    io.op2 := Mux(io.rs2_en, io.rs2_data, imm)
    io.imm := imm

    //jump
    val op1 = io.op1
    val op2 = io.op2
    val pc  = io.pc
    val bu_jump_pc = Mux(bu_code === "b10000000".U, ((op1 + op2) & "hfffffffffffffffe".U), pc + imm)
    val bu_jump_en = MuxLookup(bu_code, false.B, Array(
        "b00000001".U -> (op1 === op2),                     //beq
        "b00000010".U -> (op1 =/= op2),                     //bne
        "b00000100".U -> (op1.asSInt()  <  op2.asSInt()),   //blt
        "b00001000".U -> (op1.asSInt()  >= op2.asSInt()),   //bge
        "b00010000".U -> (op1  <  op2),                     //bltu
        "b00100000".U -> (op1  >= op2),                     //bgeu
        "b01000000".U -> true.B,                            //jal
        "b10000000".U -> true.B,                            //jalr
    ))

    val csru_jump_pc = MuxLookup(csru_code, 0.U, Array(
        "b0001".U -> io.mtvec,    //ecall
        "b0010".U -> io.mepc,     //mret
    ))
    val csru_jump_en = MuxLookup(csru_code, false.B, Array(
        "b0001".U -> true.B,   //ecall
        "b0010".U -> true.B,   //mret
    ))

    // io.jump_en := bu_jump_en || csru_jump_en                // 按理说不会两个都enable
    // io.jump_pc := Mux(bu_jump_en, bu_jump_pc, csru_jump_pc) // 按理说不会两个都enable
    when(io.intr){                  // intr有可能和bu或csru同时enable，所以intr要优先
        io.jump_en := true.B
        io.jump_pc := io.mtvec
    }
    .elsewhen(bu_jump_en){          // 按理bu和csru不会两个都enable,所以顺序无关
        io.jump_en := true.B
        io.jump_pc := bu_jump_pc
    }
    .elsewhen(csru_jump_en){
        io.jump_en := true.B
        io.jump_pc := csru_jump_pc
    }
    .otherwise{
        io.jump_en := false.B
        io.jump_pc := 0.U
    }
}


