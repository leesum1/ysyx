#include <nvboard.h>
#include "Vlab05alu4.h"

void nvboard_bind_all_pins(Vlab05alu4* top) {
	nvboard_bind_pin( &top->segout, BIND_RATE_SCR, BIND_DIR_OUT, 8, DEC0P, SEG0G, SEG0F, SEG0E, SEG0D, SEG0C, SEG0B, SEG0A);
	nvboard_bind_pin( &top->a, BIND_RATE_SCR, BIND_DIR_IN , 4, SW3, SW2, SW1, SW0);
	nvboard_bind_pin( &top->b, BIND_RATE_SCR, BIND_DIR_IN , 4, SW7, SW6, SW5, SW4);
	nvboard_bind_pin( &top->out, BIND_RATE_SCR, BIND_DIR_OUT, 4, LD3, LD2, LD1, LD0);
	nvboard_bind_pin( &top->sel, BIND_RATE_SCR, BIND_DIR_IN , 3, SW15, SW14, SW13);
	nvboard_bind_pin( &top->CF, BIND_RATE_SCR, BIND_DIR_OUT, 1, LD15);
	nvboard_bind_pin( &top->PF, BIND_RATE_SCR, BIND_DIR_OUT, 1, LD14);
	nvboard_bind_pin( &top->AF, BIND_RATE_SCR, BIND_DIR_OUT, 1, LD13);
	nvboard_bind_pin( &top->SF, BIND_RATE_SCR, BIND_DIR_OUT, 1, LD12);
	nvboard_bind_pin( &top->OF, BIND_RATE_SCR, BIND_DIR_OUT, 1, LD11);
	nvboard_bind_pin( &top->ZF, BIND_RATE_SCR, BIND_DIR_OUT, 1, LD10);
}
