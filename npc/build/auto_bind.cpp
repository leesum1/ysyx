#include <nvboard.h>
#include "Vlab08keyboard.h"

void nvboard_bind_all_pins(Vlab08keyboard* top) {
	nvboard_bind_pin( &top->seg1, BIND_RATE_SCR, BIND_DIR_OUT, 8, DEC0P, SEG0G, SEG0F, SEG0E, SEG0D, SEG0C, SEG0B, SEG0A);
	nvboard_bind_pin( &top->seg2, BIND_RATE_SCR, BIND_DIR_OUT, 8, DEC1P, SEG1G, SEG1F, SEG1E, SEG1D, SEG1C, SEG1B, SEG1A);
	nvboard_bind_pin( &top->seg3, BIND_RATE_SCR, BIND_DIR_OUT, 8, DEC2P, SEG2G, SEG2F, SEG2E, SEG2D, SEG2C, SEG2B, SEG2A);
	nvboard_bind_pin( &top->seg4, BIND_RATE_SCR, BIND_DIR_OUT, 8, DEC3P, SEG3G, SEG3F, SEG3E, SEG3D, SEG3C, SEG3B, SEG3A);
	nvboard_bind_pin( &top->seg5, BIND_RATE_SCR, BIND_DIR_OUT, 8, DEC4P, SEG4G, SEG4F, SEG4E, SEG4D, SEG4C, SEG4B, SEG4A);
	nvboard_bind_pin( &top->seg6, BIND_RATE_SCR, BIND_DIR_OUT, 8, DEC5P, SEG5G, SEG5F, SEG5E, SEG5D, SEG5C, SEG5B, SEG5A);
	nvboard_bind_pin( &top->seg7, BIND_RATE_SCR, BIND_DIR_OUT, 8, DEC6P, SEG6G, SEG6F, SEG6E, SEG6D, SEG6C, SEG6B, SEG6A);
	nvboard_bind_pin( &top->seg8, BIND_RATE_SCR, BIND_DIR_OUT, 8, DEC7P, SEG7G, SEG7F, SEG7E, SEG7D, SEG7C, SEG7B, SEG7A);
	nvboard_bind_pin( &top->rst, BIND_RATE_SCR, BIND_DIR_IN , 1, BTNU);
	nvboard_bind_pin( &top->ps2_clk, BIND_RATE_RT , BIND_DIR_IN , 1, PS2_CLK);
	nvboard_bind_pin( &top->ps2_data, BIND_RATE_RT , BIND_DIR_IN , 1, PS2_DAT);
}
