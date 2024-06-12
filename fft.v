module fft(
    input wire clk,
    input wire rst,
    input wire start,
    input wire [127:0] xr,  // Flattened array: 8 * 16 bits
    input wire [127:0] xi,  // Flattened array: 8 * 16 bits
    output reg [127:0] out_r,  // Flattened array: 8 * 16 bits
    output reg [127:0] out_i,  // Flattened array: 8 * 16 bits
    output reg done
);
    reg [2:0] stage;
    reg [2:0] counter;
    reg signed [15:0] data_r [0:7];
    reg signed [15:0] data_i [0:7];
    wire signed [15:0] br [0:3];
    wire signed [15:0] bi [0:3];
    wire signed [15:0] wr [0:3];
    wire signed [15:0] wi [0:3];
    wire signed [15:0] out1r [0:3];
    wire signed [15:0] out1i [0:3];
    wire signed [15:0] out2r [0:3];
    wire signed [15:0] out2i [0:3];

    integer j; // Integer declaration

    // Twiddle factors (for 8-point FFT)
    assign wr[0] = 16'h7FFF; assign wi[0] = 16'h0000; // W0
    assign wr[1] = 16'h5A82; assign wi[1] = 16'hA57E; // W1
    assign wr[2] = 16'h0000; assign wi[2] = 16'h8000; // W2
    assign wr[3] = 16'hA57E; assign wi[3] = 16'hA57E; // W3

    // Instantiate butterfly modules
    generate
        genvar i;
        for (i = 0; i < 4; i = i + 1) begin : butterfly_block
            butterfly bf (
                .xr(data_r[i]),
                .xi(data_i[i]),
                .yr(data_r[i+4]),
                .yi(data_i[i+4]),
                .wr(wr[i]),
                .wi(wi[i]),
                .out1r(out1r[i]),
                .out1i(out1i[i]),
                .out2r(out2r[i]),
                .out2i(out2i[i])
            );
        end
    endgenerate

    // Control logic
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            stage <= 0;
            counter <= 0;
            done <= 0;
            // Initialize data arrays
            for (j = 0; j < 8; j = j + 1) begin
                data_r[j] <= 0;
                data_i[j] <= 0;
            end
        end else if (start) begin
            case (stage)
                3'b000: begin
                    // Load input data
                    for (j = 0; j < 8; j = j + 1) begin
                        data_r[j] <= xr[16*j +: 16];
                        data_i[j] <= xi[16*j +: 16];
                    end
                    stage <= 3'b001;
                end
                3'b001: begin
                    // First stage of FFT
                    data_r[0] <= out1r[0]; data_i[0] <= out1i[0];
                    data_r[1] <= out1r[1]; data_i[1] <= out1i[1];
                    data_r[2] <= out1r[2]; data_i[2] <= out1i[2];
                    data_r[3] <= out1r[3]; data_i[3] <= out1i[3];
                    data_r[4] <= out2r[0]; data_i[4] <= out2i[0];
                    data_r[5] <= out2r[1]; data_i[5] <= out2i[1];
                    data_r[6] <= out2r[2]; data_i[6] <= out2i[2];
                    data_r[7] <= out2r[3]; data_i[7] <= out2i[3];
                    stage <= 3'b010;
                end
                3'b010: begin
                    // Second stage of FFT
                    data_r[0] <= out1r[0]; data_i[0] <= out1i[0];
                    data_r[1] <= out1r[1]; data_i[1] <= out1i[1];
                    data_r[2] <= out2r[0]; data_i[2] <= out2i[0];
                    data_r[3] <= out2r[1]; data_i[3] <= out2i[1];
                    data_r[4] <= out1r[2]; data_i[4] <= out1i[2];
                    data_r[5] <= out1r[3]; data_i[5] <= out1i[3];
                    data_r[6] <= out2r[2]; data_i[6] <= out2i[2];
                    data_r[7] <= out2r[3]; data_i[7] <= out2i[3];
                    stage <= 3'b011;
                end
                3'b011: begin
                    // Third stage of FFT
                    for (j = 0; j < 8; j = j + 1) begin
                        out_r[16*j +: 16] <= (j < 4) ? out1r[j] : out2r[j-4];
                        out_i[16*j +: 16] <= (j < 4) ? out1i[j] : out2i[j-4];
                    end
                    done <= 1;
                    stage <= 3'b000;
                end
            endcase
        end
    end
endmodule