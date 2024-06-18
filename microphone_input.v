module microphone_input (
    input wire clk,       // 50 MHz clock
    input wire [15:0] mic_in,  // Audio input data
    input wire key,           // Key0 for recording control
    output reg [17:0] ledr,    // Red LEDs for status indication
    output wire [15:0] audio_out // Audio output data
);

parameter SAMPLE_RATE = 48000; // Audio sampling rate
parameter RECORD_TIME = 2;     // Recording time in seconds
parameter TOTAL_SAMPLES = SAMPLE_RATE * RECORD_TIME;

reg [15:0] audio_buffer [0:TOTAL_SAMPLES-1];  // Buffer for storing audio samples
reg [16:0] sample_count = 0;  // Counter for the number of samples recorded

reg [31:0] clk_count = 0;     // Clock counter for sampling
wire sample_tick;             // Signal to indicate when to sample audio

reg recording = 0;            // Recording state
reg [3:0] state = 0;          // FSM state

// State machine states
localparam IDLE = 0, WAIT_FOR_KEY = 1, RECORDING = 2, DONE = 3;

// Generate sample tick
assign sample_tick = (clk_count == (50000000 / SAMPLE_RATE) - 1);

// Main FSM and recording logic
always @(posedge clk or posedge key) begin
    if (key) begin
        state <= WAIT_FOR_KEY;
    end else begin
        case (state)
            IDLE: begin
                ledr <= 18'b0; // Turn off all LEDs
                sample_count <= 0;
                clk_count <= 0;
                recording <= 0;
                state <= WAIT_FOR_KEY;
            end
            WAIT_FOR_KEY: begin
                if (key == 0) begin
                    recording <= 1;
                    state <= RECORDING;
                    ledr <= 18'b000000000000000001; // Indicate start
                end
            end
            RECORDING: begin
                if (sample_tick) begin
                    clk_count <= 0;
                    audio_buffer[sample_count] <= mic_in;
                    sample_count <= sample_count + 1;
                    ledr <= 18'b000000000000000011; // Increment LED status
                    if (sample_count == TOTAL_SAMPLES - 1) begin
                        recording <= 0;
                        state <= DONE;
                    end
                end else begin
                    clk_count <= clk_count + 1;
                end
            end
            DONE: begin
                ledr <= 18'b111111111111111111; // Indicate done
                state <= IDLE;
            end
        endcase
    end
end

assign audio_out = mic_in; // Pass-through for audio output for now

endmodule