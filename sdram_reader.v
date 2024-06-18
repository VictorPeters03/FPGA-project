module sdram_reader (
    input wire          clk,
    input wire          reset_n,
    input wire  [12:0]  address,       // Address to read from
    input wire          read_enable,   // Signal to enable read operation
    output reg  [31:0]  data_out,      // Data read from SDRAM
    output reg          read_done,     // Signal to indicate read operation is done
    
    // SDRAM interface
    output wire [12:0]  sdram_addr,
    output wire [1:0]   sdram_ba,
    output wire         sdram_cas_n,
    output wire         sdram_cke,
    output wire         sdram_cs_n,
    inout wire  [31:0]  sdram_dq,
    output wire [3:0]   sdram_dqm,
    output wire         sdram_ras_n,
    output wire         sdram_we_n,
    output wire         sdram_clk
);

// Internal signals
reg [3:0] state;
reg [31:0] sdram_data_reg;
reg sdram_read_enable;

// SDRAM Controller instance (assuming you have one)
sdram_controller u_sdram_controller (
    .clk(clk),
    .reset_n(reset_n),
    .address(address),
    .read_enable(sdram_read_enable),
    .data_out(sdram_dq),
    .read_done(read_done),
    .sdram_addr(sdram_addr),
    .sdram_ba(sdram_ba),
    .sdram_cas_n(sdram_cas_n),
    .sdram_cke(sdram_cke),
    .sdram_cs_n(sdram_cs_n),
    .sdram_dq(sdram_dq),
    .sdram_dqm(sdram_dqm),
    .sdram_ras_n(sdram_ras_n),
    .sdram_we_n(sdram_we_n),
    .sdram_clk(sdram_clk)
);

// State Machine for SDRAM Read
localparam IDLE        = 4'd0;
localparam READ_START  = 4'd1;
localparam READ_WAIT   = 4'd2;
localparam READ_DONE   = 4'd3;

always @(posedge clk or negedge reset_n) begin
    if (!reset_n) begin
        state <= IDLE;
        data_out <= 32'd0;
        read_done <= 1'b0;
        sdram_read_enable <= 1'b0;
    end else begin
        case (state)
            IDLE: begin
                if (read_enable) begin
                    state <= READ_START;
                end
                read_done <= 1'b0;
            end
            
            READ_START: begin
                sdram_read_enable <= 1'b1;
                state <= READ_WAIT;
            end
            
            READ_WAIT: begin
                sdram_read_enable <= 1'b0;
                if (read_done) begin
                    sdram_data_reg <= sdram_dq;
                    state <= READ_DONE;
                end
            end
            
            READ_DONE: begin
                data_out <= sdram_data_reg;
                read_done <= 1'b1;
                state <= IDLE;
            end
        endcase
    end
end

endmodule