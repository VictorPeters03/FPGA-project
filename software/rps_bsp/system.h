/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'Nios2' in SOPC Builder design 'Computer_System'
 * SOPC Builder design path: c:/school/Jaar-3/Periode-4/FPGA/FPGA-project/Computer_System.sopcinfo
 *
 * Generated: Wed May 22 20:12:26 CEST 2024
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * AV_Config configuration
 *
 */

#define ALT_MODULE_CLASS_AV_Config altera_up_avalon_audio_and_video_config
#define AV_CONFIG_BASE 0xff203000
#define AV_CONFIG_IRQ -1
#define AV_CONFIG_IRQ_INTERRUPT_CONTROLLER_ID -1
#define AV_CONFIG_NAME "/dev/AV_Config"
#define AV_CONFIG_SPAN 16
#define AV_CONFIG_TYPE "altera_up_avalon_audio_and_video_config"


/*
 * Audio_Subsystem_Audio configuration
 *
 */

#define ALT_MODULE_CLASS_Audio_Subsystem_Audio altera_up_avalon_audio
#define AUDIO_SUBSYSTEM_AUDIO_BASE 0xff203040
#define AUDIO_SUBSYSTEM_AUDIO_IRQ 6
#define AUDIO_SUBSYSTEM_AUDIO_IRQ_INTERRUPT_CONTROLLER_ID 0
#define AUDIO_SUBSYSTEM_AUDIO_NAME "/dev/Audio_Subsystem_Audio"
#define AUDIO_SUBSYSTEM_AUDIO_SPAN 16
#define AUDIO_SUBSYSTEM_AUDIO_TYPE "altera_up_avalon_audio"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x0a000020
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x20
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00000020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 1
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 1
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_DIVISION_ERROR_EXCEPTION
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INST_ADDR_WIDTH 0x1c
#define ALT_CPU_NAME "Nios2"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x0a000020
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x20
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00000020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 1
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 1
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_DIVISION_ERROR_EXCEPTION
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INST_ADDR_WIDTH 0x1c
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00000000


/*
 * Char_LCD_16x2 configuration
 *
 */

#define ALT_MODULE_CLASS_Char_LCD_16x2 altera_up_avalon_character_lcd
#define CHAR_LCD_16X2_BASE 0xff203050
#define CHAR_LCD_16X2_IRQ -1
#define CHAR_LCD_16X2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CHAR_LCD_16X2_NAME "/dev/Char_LCD_16x2"
#define CHAR_LCD_16X2_SPAN 2
#define CHAR_LCD_16X2_TYPE "altera_up_avalon_character_lcd"


/*
 * Custom instruction macros
 *
 */

#define ALT_CI_NIOS2_FLOATING_POINT(n,A,B) __builtin_custom_inii(ALT_CI_NIOS2_FLOATING_POINT_N+(n&ALT_CI_NIOS2_FLOATING_POINT_N_MASK),(A),(B))
#define ALT_CI_NIOS2_FLOATING_POINT_N 0xfc
#define ALT_CI_NIOS2_FLOATING_POINT_N_MASK ((1<<2)-1)


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2
#define __ALTERA_NIOS_CUSTOM_INSTR_FLOATING_POINT
#define __ALTERA_UP_AVALON_AUDIO
#define __ALTERA_UP_AVALON_AUDIO_AND_VIDEO_CONFIG
#define __ALTERA_UP_AVALON_CHARACTER_LCD
#define __ALTERA_UP_AVALON_RS232
#define __ALTERA_UP_AVALON_SRAM
#define __ALTERA_UP_FLASH_MEMORY_IP_CORE_AVALON_INTERFACE
#define __SDRAM_128MB


/*
 * Expansion_JP5 configuration
 *
 */

#define ALT_MODULE_CLASS_Expansion_JP5 altera_avalon_pio
#define EXPANSION_JP5_BASE 0xff200060
#define EXPANSION_JP5_BIT_CLEARING_EDGE_REGISTER 1
#define EXPANSION_JP5_BIT_MODIFYING_OUTPUT_REGISTER 0
#define EXPANSION_JP5_CAPTURE 1
#define EXPANSION_JP5_DATA_WIDTH 32
#define EXPANSION_JP5_DO_TEST_BENCH_WIRING 1
#define EXPANSION_JP5_DRIVEN_SIM_VALUE 0
#define EXPANSION_JP5_EDGE_TYPE "FALLING"
#define EXPANSION_JP5_FREQ 50000000
#define EXPANSION_JP5_HAS_IN 0
#define EXPANSION_JP5_HAS_OUT 0
#define EXPANSION_JP5_HAS_TRI 1
#define EXPANSION_JP5_IRQ 11
#define EXPANSION_JP5_IRQ_INTERRUPT_CONTROLLER_ID 0
#define EXPANSION_JP5_IRQ_TYPE "EDGE"
#define EXPANSION_JP5_NAME "/dev/Expansion_JP5"
#define EXPANSION_JP5_RESET_VALUE 0
#define EXPANSION_JP5_SPAN 16
#define EXPANSION_JP5_TYPE "altera_avalon_pio"


/*
 * Flash_flash_data configuration
 *
 */

#define ALT_MODULE_CLASS_Flash_flash_data Altera_UP_Flash_Memory_IP_Core_Avalon_Interface
#define FLASH_FLASH_DATA_BASE 0xc000000
#define FLASH_FLASH_DATA_IRQ -1
#define FLASH_FLASH_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FLASH_FLASH_DATA_NAME "/dev/Flash_flash_data"
#define FLASH_FLASH_DATA_SPAN 8388608
#define FLASH_FLASH_DATA_TYPE "Altera_UP_Flash_Memory_IP_Core_Avalon_Interface"


/*
 * Flash_flash_erase_control configuration
 *
 */

#define ALT_MODULE_CLASS_Flash_flash_erase_control Altera_UP_Flash_Memory_IP_Core_Avalon_Interface
#define FLASH_FLASH_ERASE_CONTROL_BASE 0xbff0000
#define FLASH_FLASH_ERASE_CONTROL_IRQ -1
#define FLASH_FLASH_ERASE_CONTROL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FLASH_FLASH_ERASE_CONTROL_NAME "/dev/Flash_flash_erase_control"
#define FLASH_FLASH_ERASE_CONTROL_SPAN 4
#define FLASH_FLASH_ERASE_CONTROL_TYPE "Altera_UP_Flash_Memory_IP_Core_Avalon_Interface"


/*
 * Green_LEDs configuration
 *
 */

#define ALT_MODULE_CLASS_Green_LEDs altera_avalon_pio
#define GREEN_LEDS_BASE 0xff200010
#define GREEN_LEDS_BIT_CLEARING_EDGE_REGISTER 0
#define GREEN_LEDS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define GREEN_LEDS_CAPTURE 0
#define GREEN_LEDS_DATA_WIDTH 9
#define GREEN_LEDS_DO_TEST_BENCH_WIRING 0
#define GREEN_LEDS_DRIVEN_SIM_VALUE 0
#define GREEN_LEDS_EDGE_TYPE "NONE"
#define GREEN_LEDS_FREQ 50000000
#define GREEN_LEDS_HAS_IN 0
#define GREEN_LEDS_HAS_OUT 1
#define GREEN_LEDS_HAS_TRI 0
#define GREEN_LEDS_IRQ -1
#define GREEN_LEDS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define GREEN_LEDS_IRQ_TYPE "NONE"
#define GREEN_LEDS_NAME "/dev/Green_LEDs"
#define GREEN_LEDS_RESET_VALUE 0
#define GREEN_LEDS_SPAN 16
#define GREEN_LEDS_TYPE "altera_avalon_pio"


/*
 * HEX3_HEX0 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX3_HEX0 altera_avalon_pio
#define HEX3_HEX0_BASE 0xff200020
#define HEX3_HEX0_BIT_CLEARING_EDGE_REGISTER 0
#define HEX3_HEX0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX3_HEX0_CAPTURE 0
#define HEX3_HEX0_DATA_WIDTH 32
#define HEX3_HEX0_DO_TEST_BENCH_WIRING 0
#define HEX3_HEX0_DRIVEN_SIM_VALUE 0
#define HEX3_HEX0_EDGE_TYPE "NONE"
#define HEX3_HEX0_FREQ 50000000
#define HEX3_HEX0_HAS_IN 0
#define HEX3_HEX0_HAS_OUT 1
#define HEX3_HEX0_HAS_TRI 0
#define HEX3_HEX0_IRQ -1
#define HEX3_HEX0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX3_HEX0_IRQ_TYPE "NONE"
#define HEX3_HEX0_NAME "/dev/HEX3_HEX0"
#define HEX3_HEX0_RESET_VALUE 0
#define HEX3_HEX0_SPAN 16
#define HEX3_HEX0_TYPE "altera_avalon_pio"


/*
 * HEX7_HEX4 configuration
 *
 */

#define ALT_MODULE_CLASS_HEX7_HEX4 altera_avalon_pio
#define HEX7_HEX4_BASE 0xff200030
#define HEX7_HEX4_BIT_CLEARING_EDGE_REGISTER 0
#define HEX7_HEX4_BIT_MODIFYING_OUTPUT_REGISTER 0
#define HEX7_HEX4_CAPTURE 0
#define HEX7_HEX4_DATA_WIDTH 32
#define HEX7_HEX4_DO_TEST_BENCH_WIRING 0
#define HEX7_HEX4_DRIVEN_SIM_VALUE 0
#define HEX7_HEX4_EDGE_TYPE "NONE"
#define HEX7_HEX4_FREQ 50000000
#define HEX7_HEX4_HAS_IN 0
#define HEX7_HEX4_HAS_OUT 1
#define HEX7_HEX4_HAS_TRI 0
#define HEX7_HEX4_IRQ -1
#define HEX7_HEX4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define HEX7_HEX4_IRQ_TYPE "NONE"
#define HEX7_HEX4_NAME "/dev/HEX7_HEX4"
#define HEX7_HEX4_RESET_VALUE 0
#define HEX7_HEX4_SPAN 16
#define HEX7_HEX4_TYPE "altera_avalon_pio"


/*
 * Interval_Timer configuration
 *
 */

#define ALT_MODULE_CLASS_Interval_Timer altera_avalon_timer
#define INTERVAL_TIMER_ALWAYS_RUN 0
#define INTERVAL_TIMER_BASE 0xff202000
#define INTERVAL_TIMER_COUNTER_SIZE 32
#define INTERVAL_TIMER_FIXED_PERIOD 0
#define INTERVAL_TIMER_FREQ 50000000
#define INTERVAL_TIMER_IRQ 0
#define INTERVAL_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define INTERVAL_TIMER_LOAD_VALUE 6249999
#define INTERVAL_TIMER_MULT 0.001
#define INTERVAL_TIMER_NAME "/dev/Interval_Timer"
#define INTERVAL_TIMER_PERIOD 125.0
#define INTERVAL_TIMER_PERIOD_UNITS "ms"
#define INTERVAL_TIMER_RESET_OUTPUT 0
#define INTERVAL_TIMER_SNAPSHOT 1
#define INTERVAL_TIMER_SPAN 32
#define INTERVAL_TIMER_TICKS_PER_SEC 8
#define INTERVAL_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define INTERVAL_TIMER_TYPE "altera_avalon_timer"


/*
 * Interval_Timer_2 configuration
 *
 */

#define ALT_MODULE_CLASS_Interval_Timer_2 altera_avalon_timer
#define INTERVAL_TIMER_2_ALWAYS_RUN 0
#define INTERVAL_TIMER_2_BASE 0xff202020
#define INTERVAL_TIMER_2_COUNTER_SIZE 32
#define INTERVAL_TIMER_2_FIXED_PERIOD 0
#define INTERVAL_TIMER_2_FREQ 50000000
#define INTERVAL_TIMER_2_IRQ 2
#define INTERVAL_TIMER_2_IRQ_INTERRUPT_CONTROLLER_ID 0
#define INTERVAL_TIMER_2_LOAD_VALUE 6249999
#define INTERVAL_TIMER_2_MULT 0.001
#define INTERVAL_TIMER_2_NAME "/dev/Interval_Timer_2"
#define INTERVAL_TIMER_2_PERIOD 125.0
#define INTERVAL_TIMER_2_PERIOD_UNITS "ms"
#define INTERVAL_TIMER_2_RESET_OUTPUT 0
#define INTERVAL_TIMER_2_SNAPSHOT 1
#define INTERVAL_TIMER_2_SPAN 32
#define INTERVAL_TIMER_2_TICKS_PER_SEC 8
#define INTERVAL_TIMER_2_TIMEOUT_PULSE_OUTPUT 0
#define INTERVAL_TIMER_2_TYPE "altera_avalon_timer"


/*
 * JTAG_UART configuration
 *
 */

#define ALT_MODULE_CLASS_JTAG_UART altera_avalon_jtag_uart
#define JTAG_UART_BASE 0xff201000
#define JTAG_UART_IRQ 8
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/JTAG_UART"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * Pushbuttons configuration
 *
 */

#define ALT_MODULE_CLASS_Pushbuttons altera_avalon_pio
#define PUSHBUTTONS_BASE 0xff200050
#define PUSHBUTTONS_BIT_CLEARING_EDGE_REGISTER 1
#define PUSHBUTTONS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PUSHBUTTONS_CAPTURE 1
#define PUSHBUTTONS_DATA_WIDTH 4
#define PUSHBUTTONS_DO_TEST_BENCH_WIRING 1
#define PUSHBUTTONS_DRIVEN_SIM_VALUE 0
#define PUSHBUTTONS_EDGE_TYPE "FALLING"
#define PUSHBUTTONS_FREQ 50000000
#define PUSHBUTTONS_HAS_IN 1
#define PUSHBUTTONS_HAS_OUT 0
#define PUSHBUTTONS_HAS_TRI 0
#define PUSHBUTTONS_IRQ 1
#define PUSHBUTTONS_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PUSHBUTTONS_IRQ_TYPE "EDGE"
#define PUSHBUTTONS_NAME "/dev/Pushbuttons"
#define PUSHBUTTONS_RESET_VALUE 0
#define PUSHBUTTONS_SPAN 16
#define PUSHBUTTONS_TYPE "altera_avalon_pio"


/*
 * Red_LEDs configuration
 *
 */

#define ALT_MODULE_CLASS_Red_LEDs altera_avalon_pio
#define RED_LEDS_BASE 0xff200000
#define RED_LEDS_BIT_CLEARING_EDGE_REGISTER 0
#define RED_LEDS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define RED_LEDS_CAPTURE 0
#define RED_LEDS_DATA_WIDTH 18
#define RED_LEDS_DO_TEST_BENCH_WIRING 0
#define RED_LEDS_DRIVEN_SIM_VALUE 0
#define RED_LEDS_EDGE_TYPE "NONE"
#define RED_LEDS_FREQ 50000000
#define RED_LEDS_HAS_IN 0
#define RED_LEDS_HAS_OUT 1
#define RED_LEDS_HAS_TRI 0
#define RED_LEDS_IRQ -1
#define RED_LEDS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RED_LEDS_IRQ_TYPE "NONE"
#define RED_LEDS_NAME "/dev/Red_LEDs"
#define RED_LEDS_RESET_VALUE 0
#define RED_LEDS_SPAN 16
#define RED_LEDS_TYPE "altera_avalon_pio"


/*
 * SDRAM configuration
 *
 */

#define ALT_MODULE_CLASS_SDRAM sdram_128mb
#define SDRAM_BASE 0x0
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_NAME "/dev/SDRAM"
#define SDRAM_SPAN 134217728
#define SDRAM_TYPE "sdram_128mb"


/*
 * SRAM configuration
 *
 */

#define ALT_MODULE_CLASS_SRAM altera_up_avalon_sram
#define SRAM_BASE 0x8000000
#define SRAM_IRQ -1
#define SRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SRAM_NAME "/dev/SRAM"
#define SRAM_SPAN 2097152
#define SRAM_TYPE "altera_up_avalon_sram"


/*
 * Serial_Port configuration
 *
 */

#define ALT_MODULE_CLASS_Serial_Port altera_up_avalon_rs232
#define SERIAL_PORT_BASE 0xff201010
#define SERIAL_PORT_IRQ 10
#define SERIAL_PORT_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SERIAL_PORT_NAME "/dev/Serial_Port"
#define SERIAL_PORT_SPAN 8
#define SERIAL_PORT_TYPE "altera_up_avalon_rs232"


/*
 * Slider_Switches configuration
 *
 */

#define ALT_MODULE_CLASS_Slider_Switches altera_avalon_pio
#define SLIDER_SWITCHES_BASE 0xff200040
#define SLIDER_SWITCHES_BIT_CLEARING_EDGE_REGISTER 0
#define SLIDER_SWITCHES_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SLIDER_SWITCHES_CAPTURE 0
#define SLIDER_SWITCHES_DATA_WIDTH 18
#define SLIDER_SWITCHES_DO_TEST_BENCH_WIRING 1
#define SLIDER_SWITCHES_DRIVEN_SIM_VALUE 0
#define SLIDER_SWITCHES_EDGE_TYPE "NONE"
#define SLIDER_SWITCHES_FREQ 50000000
#define SLIDER_SWITCHES_HAS_IN 1
#define SLIDER_SWITCHES_HAS_OUT 0
#define SLIDER_SWITCHES_HAS_TRI 0
#define SLIDER_SWITCHES_IRQ -1
#define SLIDER_SWITCHES_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SLIDER_SWITCHES_IRQ_TYPE "NONE"
#define SLIDER_SWITCHES_NAME "/dev/Slider_Switches"
#define SLIDER_SWITCHES_RESET_VALUE 0
#define SLIDER_SWITCHES_SPAN 16
#define SLIDER_SWITCHES_TYPE "altera_avalon_pio"


/*
 * SysID configuration
 *
 */

#define ALT_MODULE_CLASS_SysID altera_avalon_sysid_qsys
#define SYSID_BASE 0xff202040
#define SYSID_ID 0
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/SysID"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1716400871
#define SYSID_TYPE "altera_avalon_sysid_qsys"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_IRQ_BASE NULL
#define ALT_LEGACY_INTERRUPT_API_PRESENT
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/JTAG_UART"
#define ALT_STDERR_BASE 0xff201000
#define ALT_STDERR_DEV JTAG_UART
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/JTAG_UART"
#define ALT_STDIN_BASE 0xff201000
#define ALT_STDIN_DEV JTAG_UART
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/JTAG_UART"
#define ALT_STDOUT_BASE 0xff201000
#define ALT_STDOUT_DEV JTAG_UART
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "Computer_System"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK INTERVAL_TIMER
#define ALT_TIMESTAMP_CLK none

#endif /* __SYSTEM_H_ */
