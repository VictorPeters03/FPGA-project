module fft_avalon (
    input wire clk,
    input wire reset_n,
    input wire [31:0] address,
    input wire write,
    input wire read,
    input wire [31:0] writedata,
    output wire [31:0] readdata,
    output wire waitrequest
);

    reg [31:0] data_reg;
    reg fft_start;
    wire fft_done;
    wire [127:0] fft_out_r, fft_out_i;

    // FFT module instance
    fft fft_inst (
        .clk(clk),
        .rst(!reset_n),
        .start(fft_start),
        .xr(data_reg), // assuming 32-bit chunks for simplicity
        .xi(128'b0), // imaginary part set to zero
        .out_r(fft_out_r),
        .out_i(fft_out_i),
        .done(fft_done)
    );

    // Avalon-MM interface logic
    assign readdata = (address == 0) ? {31'b0, fft_done} : // FFT done flag
                      (address == 1) ? fft_out_r[31:0] :
                      (address == 2) ? fft_out_r[63:32] :
                      (address == 3) ? fft_out_r[95:64] :
                      (address == 4) ? fft_out_r[127:96] : 32'b0;
    assign waitrequest = 0;

    always @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            data_reg <= 32'b0;
            fft_start <= 1'b0;
        end else if (write) begin
            if (address == 0) begin
                fft_start <= 1'b1; // trigger FFT start
            end else begin
                data_reg <= writedata;
            end
        end else if (fft_done) begin
            fft_start <= 1'b0; // reset start after done
        end
    end

endmodule