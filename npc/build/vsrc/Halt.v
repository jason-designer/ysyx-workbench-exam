
import "DPI-C" function void set_halt_ptr(input logic a []);

module Halt(input clk,
            input reset,
            input halt);

  reg halt_reg [0:0];
  initial set_halt_ptr(halt_reg);

  always @(posedge clk) begin
    if (reset) begin 
      halt_reg[0] <= 1'b0;
    end else begin
      halt_reg[0] <= halt; // 
    end
  end
endmodule


            