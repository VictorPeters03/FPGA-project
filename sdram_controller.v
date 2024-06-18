module sdram_controller (
    input wire          clk,
    input wire          reset_n,
    input wire  [24:0]  address,       // Full address for SDRAM (row, column, bank)
    input wire          read_enable,   // Signal to enable read operation
    output reg  [15:0]  data_out,      // Data read from SDRAM
    output reg          read_done,     // Signal to indicate read operation is done
    
    // SDRAM interface
    output reg [12:0]   sdram_addr,
    output reg [1:0]    sdram_ba,
    output reg          sdram_cas_n,
    output reg          sdram_cke,
    output reg          sdram_cs_n,
    inout wire [15:0]   sdram_dq,
    output reg [1:0]    sdram_dqm,
    output reg          sdram_ras_n,
    output reg          sdram_we_n,
    output wire         sdram_clk
);

// Internal state machine states
localparam IDLE        = 4'd0;
localparam ACTIVATE    = 4'd1;
localparam READ        = 4'd2;
localparam READ_WAIT   = 4'd3;
localparam PRECHARGE   = 4'd4;
localparam DONE        = 4'd5;

// SDRAM commands
localparam CMD_NOP         = 4'b0111;
localparam CMD_ACTIVE      = 4'b0011;
localparam CMD_READ        = 4'b0101;
localparam CMD_PRECHARGE   = 4'b0010;

// Internal signals
reg [3:0] state;
reg [3:0] next_state;
reg [7:0] wait_counter;  // Counter for timing delays

// Clock signal
assign sdram_clk = clk;

// State machine logic
always @(posedge clk or negedge reset_n) begin
    if (!reset_n) begin
        state <= IDLE;
    end else begin
        state <= next_state;
    end
end

// Next state logic
always @(*) begin
    case (state)
        IDLE: begin
            if (read_enable) begin
                next_state = ACTIVATE;
            end else begin
                next_state = IDLE;
            end
        end

        ACTIVATE: begin
            next_state = READ;
        end

        READ: begin
            next_state = READ_WAIT;
        end

        READ_WAIT: begin
            if (wait_counter == 8'd0) begin
                next_state = PRECHARGE;
            end else begin
                next_state = READ_WAIT;
            end
        end

        PRECHARGE: begin
            next_state = DONE;
        end

        DONE: begin
            next_state = IDLE;
        end

        default: begin
            next_state = IDLE;
        end
    endcase
end

// Output and control signals
always @(posedge clk or negedge reset_n) begin
    if (!reset_n) begin
        sdram_addr <= 13'd0;
        sdram_ba <= 2'd0;
        sdram_cas_n <= 1'b1;
        sdram_cke <= 1'b1;
        sdram_cs_n <= 1'b1;
        sdram_dqm <= 2'b11;
        sdram_ras_n <= 1'b1;
        sdram_we_n <= 1'b1;
        data_out <= 16'd0;
        read_done <= 1'b0;
        wait_counter <= 8'd0;
    end else begin
        case (state)
            IDLE: begin
                read_done <= 1'b0;
            end

            ACTIVATE: begin
                // Activate row command
                sdram_cs_n <= 1'b0;
                sdram_ras_n <= 1'b0;
                sdram_cas_n <= 1'b1;
                sdram_we_n <= 1'b1;
                sdram_addr <= address[24:13];  // Row address
                sdram_ba <= address[12:11];    // Bank address
            end

            READ: begin
                // Read command
                sdram_cs_n <= 1'b0;
                sdram_ras_n <= 1'b1;
                sdram_cas_n <= 1'b0;
                sdram_we_n <= 1'b1;
                sdram_addr <= {3'b000, address[10:0]}; // Column address
                sdram_dqm <= 2'b00;
                wait_counter <= 8'd2;  // Adjust wait time based on CAS latency
            end

            READ_WAIT: begin
                if (wait_counter > 8'd0) begin
                    wait_counter <= wait_counter - 1;
                end else begin
                    data_out <= sdram_dq;
                end
            end

            PRECHARGE: begin
                // Precharge command
                sdram_cs_n <= 1'b0;
                sdram_ras_n <= 1'b0;
                sdram_cas_n <= 1'b1;
                sdram_we_n <= 1'b0;
                sdram_addr[10] <= 1'b1;  // All banks precharge
                read_done <= 1'b1;
            end

            DONE: begin
                sdram_cs_n <= 1'b1;
                sdram_ras_n <= 1'b1;
                sdram_cas_n <= 1'b1;
                sdram_we_n <= 1'b1;
                sdram_dqm <= 2'b11;
            end
        endcase
    end
end

endmodule