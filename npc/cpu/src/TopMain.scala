object Config{
  var soc = false
}


object TopMain extends App {
  Config.soc = false

  val arg = Seq(chisel3.stage.ChiselGeneratorAnnotation(() => new SimTop()))
  (new chisel3.stage.ChiselStage).execute(args, arg)
}


object TopMainSoc extends App {
  Config.soc = true
  
  val arg = Seq(chisel3.stage.ChiselGeneratorAnnotation(() => new SimTopSoc()),
    firrtl.stage.RunFirrtlTransformAnnotation(new AddModulePrefix()),
    ModulePrefixAnnotation("ysyx_040596_"))
  (new chisel3.stage.ChiselStage).execute(args, arg)
}

