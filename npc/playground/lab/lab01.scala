package lab.lab01

import chisel3._
import chisel3.util._

class Mux21 extends Module {
  val io = IO(new Bundle {
    val in1 = Input(Uint(1.W))
  })
}
