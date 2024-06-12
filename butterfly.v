module butterfly(
    input wire signed [15:0] xr,
    input wire signed [15:0] xi,
    input wire signed [15:0] yr,
    input wire signed [15:0] yi,
    input wire signed [15:0] wr,
    input wire signed [15:0] wi,
    output wire signed [15:0] out1r,
    output wire signed [15:0] out1i,
    output wire signed [15:0] out2r,
    output wire signed [15:0] out2i
);
    // Butterfly calculation
    wire signed [31:0] temp1r = xr + yr;
    wire signed [31:0] temp1i = xi + yi;
    wire signed [31:0] temp2r = xr - yr;
    wire signed [31:0] temp2i = xi - yi;
    wire signed [31:0] temp3r = (temp2r * wr - temp2i * wi) >>> 15;
    wire signed [31:0] temp3i = (temp2r * wi + temp2i * wr) >>> 15;

    assign out1r = temp1r[15:0];
    assign out1i = temp1i[15:0];
    assign out2r = temp3r[15:0];
    assign out2i = temp3i[15:0];
endmodule