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
        val rd_addr_in = Input(UInt(64.W))
        val imm_in = Input(UInt(64.W))
        val op1_in = Input(UInt(64.W))
        val op2_in = Input(UInt(64.W))
        val decode_info_in = Flipped(new DecodeInfo)
        
        //
        val pc_out = Output(UInt(64.W))
        val inst_out = Output(UInt(32.W))
        val rd_en_out = Output(Bool())
        val rd_addr_out = Output(UInt(64.W))
        val imm_out = Output(UInt(64.W))
        val op1_out = Output(UInt(64.W))
        val op2_out = Output(UInt(64.W))
        val decode_info_out = new DecodeInfo
    })
    val valid = RegEnable(io.pr.valid_in, false.B, io.pr.en)
    val pc = RegEnable(io.pc_in, 0.U(64.W), io.pr.en)
    val inst = RegEnable(io.inst_in, 0.U(32.W), io.pr.en)
    val rd_en = RegEnable(io.rd_en_in, false.B)
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
        val rd_addr_in = Input(UInt(64.W))
        val out_in = Input(UInt(64.W))

        val ren_in   = Output(Bool())
        val raddr_in = Output(UInt(64.W))
        val wen_in   = Output(Bool())
        val waddr_in = Output(UInt(64.W))
        val wdata_in = Output(UInt(64.W))
        val wmask_in = Output(UInt(8.W))
        //
        val pc_out = Output(UInt(64.W))
        val inst_out = Output(UInt(32.W))

        val rd_en_out = Output(Bool())
        val rd_addr_out = Output(UInt(64.W))
        val out_out = Output(UInt(64.W))

        val ren_out   = Output(Bool())
        val raddr_out = Output(UInt(64.W))
        val wen_out   = Output(Bool())
        val waddr_out = Output(UInt(64.W))
        val wdata_out = Output(UInt(64.W))
        val wmask_out = Output(UInt(8.W))
    })
    val valid = RegEnable(io.pr.valid_in, false.B, io.pr.en)
    val pc = RegEnable(io.pc_in, 0.U(64.W), io.pr.en)
    val inst = RegEnable(io.inst_in, 0.U(32.W), io.pr.en)
    val rd_en = RegEnable(io.rd_en_in, false.B, io.pr.en)
    val rd_addr = RegEnable(io.rd_addr_in, 0.U(5.W), io.pr.en)
    val out = RegEnable(io.out_in, 0.U(64.W), io.pr.en)

    val ren = RegEnable(io.ren_in, false.B, io.pr.en)
    val raddr = RegEnable(io.raddr_in, 0.U(64.W), io.pr.en)
    val wen = RegEnable(io.wen_in, false.B, io.pr.en)
    val waddr = RegEnable(io.waddr_in, 0.U(64.W), io.pr.en)
    val wdata = RegEnable(io.wdata_in, 0.U(64.W), io.pr.en)
    val wmask = RegEnable(io.wmask_in, 0.U(8.W), io.pr.en)

    io.pr.valid_out := valid
    io.pc_out := pc
    io.inst_out := inst
    io.rd_en_out := rd_en
    io.rd_addr_out := rd_addr
    io.out_out := out
    io.ren_out := ren
    io.raddr_out := raddr
    io.wen_out := wen
    io.waddr_out := waddr
    io.wdata_out := wdata
    io.wmask_out := wmask
}

class WBReg extends Module{
    val io = IO(new Bundle{
        val pr = new PipelineRegIO
        val pc_in = Input(UInt(64.W))
        val inst_in = Input(UInt(32.W))
        val rd_en_in = Input(Bool())
        val rd_addr_in = Input(UInt(64.W))
        val ren_in = Input(Bool())

        val pc_out = Output(UInt(64.W))
        val inst_out = Output(UInt(32.W))
        val rd_en_out = Output(Bool())
        val rd_addr_out = Output(UInt(64.W))
        val ren_out = Output(Bool())
    })

    val valid = RegEnable(io.pr.valid_in, false.B, io.pr.en)
    val pc = RegEnable(io.pc_in, 0.U(64.W), io.pr.en)
    val inst = RegEnable(io.inst_in, 0.U(32.W), io.pr.en)
    val rd_en = RegEnable(io.rd_en_in, false.B, io.pr.en)
    val rd_addr = RegEnable(io.rd_addr_in, 0.U(5.W), io.pr.en)
    val ren = RegEnable(io.ren_in, false.B, io.pr.en)

    io.pr.valid_out := valid
    io.pc_out := pc
    io.inst_out := inst
    io.rd_en_out := rd_en
    io.rd_addr_out := rd_addr
    io.ren_out := ren
}


class JumpFlushDelay extends Module{
    val io = IO(new Bundle{
        val in  = Input(Bool())
        val out = Output(Bool())
    })
    val s0 :: s1 :: Nil = Enum(2)
    val state = RegInit(s0)
    switch(state){
        is(s0){
            state := Mux(io.in, s1, s0)
        }
        is(s1){
            state := s0
        }
    }
    io.out := state
}

