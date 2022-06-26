#include <nvboard.h>
#include "Vlab07rand8.h"

void nvboard_bind_all_pins(Vlab07rand8* top) {
	nvboard_bind_pin( &top->seg1, BIND_RATE_SCR, BIND_DIR_OUT, 8, DEC0P, SEG0G, SEG0F, SEG0E, SEG0D, SEG0C, SEG0B, SEG0A);
	nvboard_bind_pin( &top->seg2, BIND_RATE_SCR, BIND_DIR_OUT, 8, DEC1P, SEG1G, SEG1F, SEG1E, SEG1D, SEG1C, SEG1B, SEG1A);
	nvboard_bind_pin( &top->out, BIND_RATE_SCR, BIND_DIR_OUT, 8, LD7, LD6, LD5, LD4, LD3, LD2, LD1, LD0);
	nvboard_bind_pin( &top->clk, BIND_RATE_SCR, BIND_DIR_IN , 1, BTNU);
}
