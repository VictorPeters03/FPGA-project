module rockpaperscissors (
	// Clock pins
	CLOCK_50,
	CLOCK2_50,
	CLOCK3_50,

	// Audio
	AUD_ADCDAT,
	AUD_BCLK,
	AUD_ADCLRCK,
	AUD_DACLRCK,
	AUD_DACDAT,
	AUD_XCK,
	
	// SDRAM
	DRAM_ADDR,
	DRAM_BA,
	DRAM_CAS_N,
	DRAM_CLK,
	DRAM_CKE,
	DRAM_CS_N,
	DRAM_DQ,
	DRAM_DQM,
	DRAM_RAS_N,
	DRAM_WE_N,
	
	// Flash
	FL_ADDR,
   FL_CE_N,
	FL_DQ,
	FL_OE_N,
	FL_RESET_N,
	FL_WE_N,

	// Seven Segment Displays
	HEX0,
	HEX1,
	HEX2,
	HEX3,
	HEX4,
	HEX5,
	HEX6,
	HEX7,

	// AV Config
	I2C_SCLK,
	I2C_SDAT,

	// Pushbuttons
	KEY,

	// Char LCD 16x2
	LCD_BLON,
	LCD_DATA,
	LCD_EN,
	LCD_ON,
	LCD_RS,
	LCD_RW,
	
	// LEDs
	LEDG,
	LEDR,
	
	// SD Card
	SD_CLK,
	SD_CMD,
	SD_DAT,

	// SRAM
	SRAM_ADDR,
	SRAM_DQ,
	SRAM_CE_N,
	SRAM_WE_N,
	SRAM_OE_N,
	SRAM_UB_N,
	SRAM_LB_N,

	// Slider Switches
	SW,
	
	// RS232 UART
	UART_RXD,
	UART_TXD,
);

/*****************************************************************************
 *                           Parameter Declarations                          *
 *****************************************************************************/


/*****************************************************************************
 *                             Port Declarations                             *
 *****************************************************************************/
// Clock pins
input						CLOCK_50;
input						CLOCK2_50;
input						CLOCK3_50;

// Audio
input						AUD_ADCDAT;
inout						AUD_BCLK;
inout						AUD_ADCLRCK;
inout						AUD_DACLRCK;
output					AUD_DACDAT;
output					AUD_XCK;

// SDRAM
output		[12: 0]	DRAM_ADDR;
output		[ 1: 0]	DRAM_BA;
output					DRAM_CAS_N;
output					DRAM_CLK;
output					DRAM_CKE;
output					DRAM_CS_N;
inout			[31: 0]	DRAM_DQ;
output		[ 3: 0]	DRAM_DQM;
output					DRAM_RAS_N;
output					DRAM_WE_N; 

// Flash
output 		[22: 0]	FL_ADDR;
output					FL_CE_N;
inout			[ 7: 0]  FL_DQ; 
output					FL_OE_N;
output					FL_RESET_N;
output					FL_WE_N;

// Seven Segment Displays
output		[ 6: 0]	HEX0;
output		[ 6: 0]	HEX1;
output		[ 6: 0]	HEX2;
output		[ 6: 0]	HEX3;
output		[ 6: 0]	HEX4;
output		[ 6: 0]	HEX5;
output		[ 6: 0]	HEX6;
output		[ 6: 0]	HEX7;

// AV Config
output					I2C_SCLK;
inout						I2C_SDAT;

// Pushbuttons
input			[ 3: 0]	KEY;

// Char LCD 16x2
output					LCD_BLON;
inout			[ 7: 0]	LCD_DATA;
output					LCD_EN;
output					LCD_ON;
output					LCD_RS;
output					LCD_RW;

// LEDs
output		[ 8: 0]	LEDG;
output		[17: 0]	LEDR;

// SD Card
output					SD_CLK;
inout						SD_CMD;
inout			[ 3: 0]  SD_DAT;

// SRAM
output		[19: 0]	SRAM_ADDR;
inout			[15: 0]	SRAM_DQ;
output					SRAM_CE_N;
output					SRAM_WE_N;
output					SRAM_OE_N;
output					SRAM_UB_N;
output					SRAM_LB_N;

// Slider Switches
input			[17: 0]	SW;

// RS232 UART
input						UART_RXD;
output					UART_TXD;

/*****************************************************************************
 *                 Internal Wires and Registers Declarations                 *
 *****************************************************************************/
// Internal Wires
wire			[31: 0]	hex3_hex0;
wire			[31: 0]	hex7_hex4;

// Internal Registers

// State Machine Registers

/*****************************************************************************
 *                         Finite State Machine(s)                           *
 *****************************************************************************/


/*****************************************************************************
 *                             Sequential Logic                              *
 *****************************************************************************/


/*****************************************************************************
 *                            Combinational Logic                            *
 *****************************************************************************/

// Output Assignments
assign HEX0				= ~hex3_hex0[ 6: 0];
assign HEX1				= ~hex3_hex0[14: 8];
assign HEX2				= ~hex3_hex0[22:16];
assign HEX3				= ~hex3_hex0[30:24];
assign HEX4				= ~hex7_hex4[ 6: 0];
assign HEX5				= ~hex7_hex4[14: 8];
assign HEX6				= ~hex7_hex4[22:16];
assign HEX7				= ~hex7_hex4[30:24];


/*****************************************************************************
 *                              Internal Modules                             *
 *****************************************************************************/
Computer_System The_System (
	// Global signals
	.system_pll_ref_clk_clk					(CLOCK_50),
	.system_pll_ref_reset_reset			(1'b0),

	// Audio Subsystem
	.audio_pll_clk_clk							(AUD_XCK),
	.audio_ADCDAT								(AUD_ADCDAT),
	.audio_ADCLRCK								(AUD_ADCLRCK),
	.audio_BCLK									(AUD_BCLK),
	.audio_DACDAT								(AUD_DACDAT),
	.audio_DACLRCK								(AUD_DACLRCK),
	.audio_pll_ref_clk_clk					(CLOCK3_50),
	.audio_pll_ref_reset_reset				(1'b0),

	// AV Config
	.av_config_SDAT							(I2C_SDAT),
	.av_config_SCLK							(I2C_SCLK),

	// Character LCD 16x2
	.char_lcd_DATA								(LCD_DATA),
	.char_lcd_ON								(LCD_ON),
	.char_lcd_BLON								(LCD_BLON),
	.char_lcd_EN								(LCD_EN),
	.char_lcd_RS								(LCD_RS),
	.char_lcd_RW								(LCD_RW),

	// Flash
	.flash_ADDR									(FL_ADDR),
   .flash_CE_N									(FL_CE_N),
   .flash_OE_N									(FL_OE_N),
   .flash_WE_N									(FL_WE_N),
   .flash_RST_N								(FL_RESET_N),
   .flash_DQ									(FL_DQ),   

	// Green LEDs
	.green_leds_export						(LEDG),

	// Seven Segs
	.hex3_hex0_export							(hex3_hex0),
	.hex7_hex4_export							(hex7_hex4),

	// Pushbuttons
	.pushbuttons_export						(~KEY[3:0]),

	// Red LEDs
	.red_leds_export							(LEDR),
	
	// SD Card
	.sd_card_b_SD_cmd							(SD_CMD),
   .sd_card_b_SD_dat							(SD_DAT[0]),
   .sd_card_b_SD_dat3						(SD_DAT[3]),
   .sd_card_o_SD_clock						(SD_CLK),
	
	// SDRAM
	.sdram_clk_clk								(DRAM_CLK),
   .sdram_addr									(DRAM_ADDR),
	.sdram_ba									(DRAM_BA),
	.sdram_cas_n								(DRAM_CAS_N),
	.sdram_cke									(DRAM_CKE),
	.sdram_cs_n									(DRAM_CS_N),
	.sdram_dq									(DRAM_DQ),
	.sdram_dqm									(DRAM_DQM),
	.sdram_ras_n								(DRAM_RAS_N),
	.sdram_we_n									(DRAM_WE_N),

	// Serial port
	.serial_port_RXD							(UART_RXD),
	.serial_port_TXD							(UART_TXD),
	
	// Slider Switches
	.slider_switches_export					(SW),

	// SRAM
	.sram_DQ										(SRAM_DQ),
	.sram_ADDR									(SRAM_ADDR),
	.sram_LB_N									(SRAM_LB_N),
	.sram_UB_N									(SRAM_UB_N),
	.sram_CE_N									(SRAM_CE_N),
	.sram_OE_N									(SRAM_OE_N),
	.sram_WE_N									(SRAM_WE_N)
);

endmodule