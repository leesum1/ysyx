#include <nvboard.h>
#include "Vlab04ecode83.h"

void nvboard_bind_all_pins(Vlab04ecode83* top) {
	nvboard_bind_pin( &top->in, BIND_RATE_SCR, BIND_DIR_IN , 8, SW7, SW6, SW5, SW4, SW3, SW2, SW1, SW0);
	nvboard_bind_pin( &top->out, BIND_RATE_SCR, BIND_DIR_OUT, 3, LD2, LD1, LD0);
	nvboard_bind_pin( &top->inflag, BIND_RATE_SCR, BIND_DIR_OUT, 1, LD8);
	nvboard_bind_pin( &top->seg, BIND_RATE_SCR, BIND_DIR_OUT, 8, DEC0P, SEG0G, SEG0F, SEG0E, SEG0D, SEG0C, SEG0B, SEG0A);
}
