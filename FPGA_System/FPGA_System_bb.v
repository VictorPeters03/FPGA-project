
module FPGA_System (
	audio_ADCDAT,
	audio_ADCLRCK,
	audio_BCLK,
	audio_DACDAT,
	audio_DACLRCK,
	audio_pll_clk_clk,
	audio_pll_ref_clk_clk,
	audio_pll_ref_reset_reset,
	av_config_SDAT,
	av_config_SCLK,
	char_lcd_DATA,
	char_lcd_ON,
	char_lcd_BLON,
	char_lcd_EN,
	char_lcd_RS,
	char_lcd_RW,
	green_leds_export,
	hex3_hex0_export,
	hex7_hex4_export,
	irda_TXD,
	irda_RXD,
	pushbuttons_export,
	red_leds_export,
	sdram_ba,
	sdram_addr,
	sdram_cas_n,
	sdram_cke,
	sdram_cs_n,
	sdram_dq,
	sdram_dqm,
	sdram_ras_n,
	sdram_we_n,
	sdram_clk_clk,
	serial_port_RXD,
	serial_port_TXD,
	slider_switches_export,
	sram_DQ,
	sram_ADDR,
	sram_LB_N,
	sram_UB_N,
	sram_CE_N,
	sram_OE_N,
	sram_WE_N,
	system_pll_ref_clk_clk,
	system_pll_ref_reset_reset);	

	input		audio_ADCDAT;
	input		audio_ADCLRCK;
	input		audio_BCLK;
	output		audio_DACDAT;
	input		audio_DACLRCK;
	output		audio_pll_clk_clk;
	input		audio_pll_ref_clk_clk;
	input		audio_pll_ref_reset_reset;
	inout		av_config_SDAT;
	output		av_config_SCLK;
	inout	[7:0]	char_lcd_DATA;
	output		char_lcd_ON;
	output		char_lcd_BLON;
	output		char_lcd_EN;
	output		char_lcd_RS;
	output		char_lcd_RW;
	output	[8:0]	green_leds_export;
	output	[31:0]	hex3_hex0_export;
	output	[31:0]	hex7_hex4_export;
	output		irda_TXD;
	input		irda_RXD;
	input	[3:0]	pushbuttons_export;
	output	[17:0]	red_leds_export;
	output	[1:0]	sdram_ba;
	output	[12:0]	sdram_addr;
	output		sdram_cas_n;
	output		sdram_cke;
	output		sdram_cs_n;
	inout	[31:0]	sdram_dq;
	output	[3:0]	sdram_dqm;
	output		sdram_ras_n;
	output		sdram_we_n;
	output		sdram_clk_clk;
	input		serial_port_RXD;
	output		serial_port_TXD;
	input	[17:0]	slider_switches_export;
	inout	[15:0]	sram_DQ;
	output	[19:0]	sram_ADDR;
	output		sram_LB_N;
	output		sram_UB_N;
	output		sram_CE_N;
	output		sram_OE_N;
	output		sram_WE_N;
	input		system_pll_ref_clk_clk;
	input		system_pll_ref_reset_reset;
endmodule
