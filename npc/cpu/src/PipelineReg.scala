import chisel3._
import chisel3.util._

class PipelineRegIO extends Bundle{
    val valid_in = Input(Bool())
    val valid_out = Output(Bool())
    val en = Input(Bool())
}


class IFReg extends Module{
    val io = IO(new Bundle{
        val pr = new PipelineRegIO
        val next_pc_in = Input(UInt(64.W))
        val next_pc_out = Output(UInt(64.W))
    })
    val valid = RegEnable(io.pr.valid_in, false.B, io.pr.en)
    val next_pc = RegEnable(io.next_pc_in, 0.U, io.pr.en)

    io.pr.valid_out := valid
    io.next_pc_out := next_pc

}


class IDReg extends Module{
    val io = IO(new Bundle{
        val pr = new PipelineRegIO
        val pc_in = Input(UInt(64.W))
        val inst_in = Input(UInt(32.W))

        val pc_out = Output(UInt(64.W))
        val inst_out = Output(UInt(32.W))
    })
    val valid = RegEnable(io.pr.valid_in, false.B, io.pr.en)
    val pc = RegEnable(io.pc_in, 0.U(64.W), io.pr.en)
    val inst = RegEnable(io.inst_in, 0.U(32.W), io.pr.en)

    io.pr.valid_out := valid
    io.pc_out := pc
    io.inst_out := inst
}

class ExeReg extends Module{
    val io = IO(new Bundle{
        val pr = new PipelineRegIO
        val pc_in = Input(UInt(64.W))
        val inst_in = Input(UInt(32.W))
        val rd_en_in = Input(Bool())
        val rd_addr_in = Input(UInt(5.W))
        val imm_in = Input(UInt(64.W))
        val op1_in = Input(UInt(64.W))
        val op2_in = Input(UInt(64.W))
        val decode_info_in = Flipped(new DecodeInfo)
        
        //
        val pc_out = Output(UInt(64.W))
        val inst_out = Output(UInt(32.W))
        val rd_en_out = Output(Bool())
        val rd_addr_out = Output(UInt(5.W))
        val imm_out = Output(UInt(64.W))
        val op1_out = Output(UInt(64.W))
        val op2_out = Output(UInt(64.W))
        val decode_info_out = new DecodeInfo
    })
    val valid = RegEnable(io.pr.valid_in, false.B, io.pr.en)
    val pc = RegEnable(io.pc_in, 0.U(64.W), io.pr.en)
    val inst = RegEnable(io.inst_in, 0.U(32.W), io.pr.en)
    val rd_en = RegEnable(io.rd_en_in, false.B, io.pr.en)
    val rd_addr = RegEnable(io.rd_addr_in, 0.U(5.W), io.pr.en)
    val imm = RegEnable(io.imm_in, 0.U(64.W), io.pr.en)
    val op1 = RegEnable(io.op1_in, 0.U(64.W), io.pr.en)
    val op2 = RegEnable(io.op2_in, 0.U(64.W), io.pr.en)

    val fu_code  = RegEnable(io.decode_info_in.fu_code, 0.U, io.pr.en)
    val alu_code = RegEnable(io.decode_info_in.alu_code, 0.U, io.pr.en)
    val bu_code  = RegEnable(io.decode_info_in.bu_code, 0.U, io.pr.en)
    val lu_code  = RegEnable(io.decode_info_in.lu_code, 0.U, io.pr.en)
    val su_code  = RegEnable(io.decode_info_in.su_code, 0.U, io.pr.en)
    val mdu_code = RegEnable(io.decode_info_in.mdu_code, 0.U, io.pr.en)

    io.pr.valid_out := valid
    io.pc_out := pc
    io.inst_out := inst
    io.rd_en_out := rd_en
    io.rd_addr_out := rd_addr
    io.imm_out := imm
    io.op1_out := op1
    io.op2_out := op2
    io.decode_info_out.fu_code := fu_code
    io.decode_info_out.alu_code := alu_code
    io.decode_info_out.bu_code := bu_code
    io.decode_info_out.lu_code := lu_code
    io.decode_info_out.su_code := su_code
    io.decode_info_out.mdu_code := mdu_code
}

class MemReg extends Module{
    val io = IO(new Bundle{
        val pr = new PipelineRegIO
        val pc_in = Input(UInt(64.W))
        val inst_in = Input(UInt(32.W))
        val rd_en_in = Input(Bool())
        val rd_addr_in = Input(UInt(5.W))
        val alu_out_in = Input(UInt(64.W))
        val bu_out_in = Input(UInt(64.W))
        val mdu_out_in = Input(UInt(64.W))

        val imm_in = Input(UInt(64.W))
        val op1_in = Input(UInt(64.W))
        val op2_in = Input(UInt(64.W))
        val decode_info_in = Flipped(new DecodeInfo)

        //
        val pc_out = Output(UInt(64.W))
        val inst_out = Output(UInt(32.W))
        val rd_en_out = Output(Bool())
        val rd_addr_out = Output(UInt(5.W))
        val alu_out_out = Output(UInt(64.W))
        val bu_out_out = Output(UInt(64.W))
        val mdu_out_out = Output(UInt(64.W))

        val imm_out = Output(UInt(64.W))
        val op1_out = Output(UInt(64.W))
        val op2_out = Output(UInt(64.W))
        val decode_info_out = new DecodeInfo
    })
    val valid   = RegEnable(io.pr.valid_in, false.B, io.pr.en)
    val pc      = RegEnable(io.pc_in, 0.U(64.W), io.pr.en)
    val inst    = RegEnable(io.inst_in, 0.U(32.W), io.pr.en)
    val rd_en   = RegEnable(io.rd_en_in, false.B, io.pr.en)
    val rd_addr = RegEnable(io.rd_addr_in, 0.U(5.W), io.pr.en)
    val alu_out = RegEnable(io.alu_out_in, 0.U(64.W), io.pr.en)
    val bu_out  = RegEnable(io.bu_out_in, 0.U(64.W), io.pr.en)
    val mdu_out  = RegEnable(io.mdu_out_in, 0.U(64.W), io.pr.en)

    val imm = RegEnable(io.imm_in, 0.U(64.W), io.pr.en)
    val op1 = RegEnable(io.op1_in, 0.U(64.W), io.pr.en)
    val op2 = RegEnable(io.op2_in, 0.U(64.W), io.pr.en)

    val fu_code  = RegEnable(io.decode_info_in.fu_code, 0.U, io.pr.en)
    val alu_code = RegEnable(io.decode_info_in.alu_code, 0.U, io.pr.en)
    val bu_code  = RegEnable(io.decode_info_in.bu_code, 0.U, io.pr.en)
    val lu_code  = RegEnable(io.decode_info_in.lu_code, 0.U, io.pr.en)
    val su_code  = RegEnable(io.decode_info_in.su_code, 0.U, io.pr.en)
    val mdu_code = RegEnable(io.decode_info_in.mdu_code, 0.U, io.pr.en)

    io.pr.valid_out := valid
    io.pc_out := pc
    io.inst_out := inst
    io.rd_en_out := rd_en
    io.rd_addr_out := rd_addr
    io.alu_out_out := alu_out
    io.bu_out_out := bu_out
    io.mdu_out_out := mdu_out

    io.imm_out := imm
    io.op1_out := op1
    io.op2_out := op2
    io.decode_info_out.fu_code := fu_code
    io.decode_info_out.alu_code := alu_code
    io.decode_info_out.bu_code := bu_code
    io.decode_info_out.lu_code := lu_code
    io.decode_info_out.su_code := su_code
    io.decode_info_out.mdu_code := mdu_code
}

class WBReg extends Module{
    val io = IO(new Bundle{
        val pr = new PipelineRegIO
        val pc_in       = Input(UInt(64.W))
        val inst_in     = Input(UInt(32.W))
        val rd_en_in    = Input(Bool())
        val rd_addr_in  = Input(UInt(5.W))
        val alu_out_in = Input(UInt(64.W))
        val bu_out_in = Input(UInt(64.W))
        val mdu_out_in = Input(UInt(64.W))

        val fu_code_in  = Input(UInt())
        val lu_code_in  = Input(UInt())
        val lu_shift_in = Input(UInt(6.W))

        val pc_out      = Output(UInt(64.W))
        val inst_out    = Output(UInt(32.W))
        val rd_en_out   = Output(Bool())
        val rd_addr_out = Output(UInt(5.W))
        val alu_out_out = Output(UInt(64.W))
        val bu_out_out = Output(UInt(64.W))
        val mdu_out_out = Output(UInt(64.W))

        val fu_code_out = Output(UInt())
        val lu_code_out = Output(UInt())
        val lu_shift_out = Output(UInt(6.W))
    })

    val valid = RegEnable(io.pr.valid_in, false.B, io.pr.en)
    val pc = RegEnable(io.pc_in, 0.U(64.W), io.pr.en)
    val inst = RegEnable(io.inst_in, 0.U(32.W), io.pr.en)
    val rd_en = RegEnable(io.rd_en_in, false.B, io.pr.en)
    val rd_addr = RegEnable(io.rd_addr_in, 0.U(5.W), io.pr.en)
    val alu_out = RegEnable(io.alu_out_in, 0.U(64.W), io.pr.en)
    val bu_out  = RegEnable(io.bu_out_in, 0.U(64.W), io.pr.en)
    val mdu_out  = RegEnable(io.mdu_out_in, 0.U(64.W), io.pr.en)

    val fu_code  = RegEnable(io.fu_code_in, 0.U, io.pr.en)
    val lu_code  = RegEnable(io.lu_code_in, 0.U, io.pr.en)
    val lu_shift = RegEnable(io.lu_shift_in, 0.U, io.pr.en)

    io.pr.valid_out := valid
    io.pc_out := pc
    io.inst_out := inst
    io.rd_en_out := rd_en
    io.rd_addr_out := rd_addr
    io.alu_out_out := alu_out
    io.bu_out_out := bu_out
    io.mdu_out_out := mdu_out

    io.fu_code_out := fu_code
    io.lu_code_out := lu_code
    io.lu_shift_out := lu_shift

}


class JumpFlushDelay extends Module{
    val io = IO(new Bundle{
        val en              = Input(Bool())
        val in              = Input(Bool())
        val preifu_jump_en  = Output(Bool())
        val idreg_en        = Output(Bool())
        val exereg_valid    = Output(Bool())
    })
    val s0 :: s1 :: s2 :: Nil = Enum(3)
    val state = RegInit(s0)
    switch(state){
        is(s0){
            state := Mux(io.en && io.in, s1, s0)
        }
        is(s1){
            state := s2
        }
        is(s2){
            state := s0
        }
    }

    io.idreg_en := MuxLookup(state, false.B, Array(
        s0 -> !io.in,
        s1 -> false.B,
        s2 -> true.B
    ))

    io.preifu_jump_en := MuxLookup(state, false.B, Array(
        s0 -> io.in,
        s1 -> false.B,
        s2 -> false.B
    ))
    
    //1.当跳转冲刷完再给exereg赋值valid。
    //2.非跳转的时候exereg是一直都valid的。（不考虑stall）
    io.exereg_valid := (state === s0 && (!io.in)) || state === s2 
}


class ImemoryReadHold extends Module{
  val io = IO(new Bundle{
    val ren         = Input(Bool())
    val raddr       = Input(UInt(64.W))
    val imem_ren    = Output(Bool())
    val imem_raddr  = Output(UInt(64.W))
  })
  val raddr = RegEnable(io.raddr, 0.U, io.ren)
  io.imem_raddr := Mux(io.ren, io.raddr, raddr)
  io.imem_ren := true.B
}


class CorrelationConflict extends Module{
    val io = IO(new Bundle{
        val rs_valid    = Input(Bool())
        val rd_valid    = Input(Bool())
        val rs1_en      = Input(Bool())
        val rs2_en      = Input(Bool())
        val rs1_addr    = Input(UInt(5.W))
        val rs2_addr    = Input(UInt(5.W))
        val rd_en       = Input(Bool())
        val rd_addr     = Input(UInt(5.W))

        val conflict    = Output(Bool())
    })
    val inst_valid      = io.rs_valid && io.rd_valid
    val rs1_conflict    = io.rs1_en && (io.rs1_addr === io.rd_addr)
    val rs2_conflict    = io.rs2_en && (io.rs2_addr === io.rd_addr)
    val rd_valid        = (io.rd_addr =/= 0.U) && io.rd_en

    io.conflict := inst_valid && rd_valid && (rs1_conflict || rs2_conflict)
}
