	system u0 (
		.audio_ADCDAT               (<connected-to-audio_ADCDAT>),               //                audio.ADCDAT
		.audio_ADCLRCK              (<connected-to-audio_ADCLRCK>),              //                     .ADCLRCK
		.audio_BCLK                 (<connected-to-audio_BCLK>),                 //                     .BCLK
		.audio_DACDAT               (<connected-to-audio_DACDAT>),               //                     .DACDAT
		.audio_DACLRCK              (<connected-to-audio_DACLRCK>),              //                     .DACLRCK
		.audio_pll_clk_clk          (<connected-to-audio_pll_clk_clk>),          //        audio_pll_clk.clk
		.audio_pll_ref_clk_clk      (<connected-to-audio_pll_ref_clk_clk>),      //    audio_pll_ref_clk.clk
		.audio_pll_ref_reset_reset  (<connected-to-audio_pll_ref_reset_reset>),  //  audio_pll_ref_reset.reset
		.av_config_SDAT             (<connected-to-av_config_SDAT>),             //            av_config.SDAT
		.av_config_SCLK             (<connected-to-av_config_SCLK>),             //                     .SCLK
		.hex7_hex4_export           (<connected-to-hex7_hex4_export>),           //            hex7_hex4.export
		.hex7_hex4_1_export         (<connected-to-hex7_hex4_1_export>),         //          hex7_hex4_1.export
		.pushbuttons_export         (<connected-to-pushbuttons_export>),         //          pushbuttons.export
		.sdram_ba                   (<connected-to-sdram_ba>),                   //                sdram.ba
		.sdram_addr                 (<connected-to-sdram_addr>),                 //                     .addr
		.sdram_cas_n                (<connected-to-sdram_cas_n>),                //                     .cas_n
		.sdram_cke                  (<connected-to-sdram_cke>),                  //                     .cke
		.sdram_cs_n                 (<connected-to-sdram_cs_n>),                 //                     .cs_n
		.sdram_dq                   (<connected-to-sdram_dq>),                   //                     .dq
		.sdram_dqm                  (<connected-to-sdram_dqm>),                  //                     .dqm
		.sdram_ras_n                (<connected-to-sdram_ras_n>),                //                     .ras_n
		.sdram_we_n                 (<connected-to-sdram_we_n>),                 //                     .we_n
		.sdram_clk_clk              (<connected-to-sdram_clk_clk>),              //            sdram_clk.clk
		.slider_switches_export     (<connected-to-slider_switches_export>),     //      slider_switches.export
		.sram_DQ                    (<connected-to-sram_DQ>),                    //                 sram.DQ
		.sram_ADDR                  (<connected-to-sram_ADDR>),                  //                     .ADDR
		.sram_LB_N                  (<connected-to-sram_LB_N>),                  //                     .LB_N
		.sram_UB_N                  (<connected-to-sram_UB_N>),                  //                     .UB_N
		.sram_CE_N                  (<connected-to-sram_CE_N>),                  //                     .CE_N
		.sram_OE_N                  (<connected-to-sram_OE_N>),                  //                     .OE_N
		.sram_WE_N                  (<connected-to-sram_WE_N>),                  //                     .WE_N
		.system_pll_ref_clk_clk     (<connected-to-system_pll_ref_clk_clk>),     //   system_pll_ref_clk.clk
		.system_pll_ref_reset_reset (<connected-to-system_pll_ref_reset_reset>)  // system_pll_ref_reset.reset
	);

