object Config{
  val soc = true
}


object TopMain extends App {
  val arg = if(Config.soc){
    Seq(chisel3.stage.ChiselGeneratorAnnotation(() => new SimTopSoc()),
    firrtl.stage.RunFirrtlTransformAnnotation(new AddModulePrefix()),
    ModulePrefixAnnotation("ysyx_040596_"))
  }
  else{
    Seq(chisel3.stage.ChiselGeneratorAnnotation(() => new SimTop()))
  }

  (new chisel3.stage.ChiselStage).execute(args, arg)
}

