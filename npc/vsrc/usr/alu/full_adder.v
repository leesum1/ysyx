module full_adder (
    input  wire a,
    input  wire b,
    input  wire ci,
    output wire s,
    output wire co
);

  assign s  = a ^ b ^ ci;
  assign co = (a & b) | (a & ci) | (b & ci);
endmodule
