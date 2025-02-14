#include "piston.h"

#include "pros/misc.h"
#include "ringtail/pneumatics.h"

#include <stdbool.h>

/**
 * @file piston.c
 *
 * @brief Function implementations for big bot's piston
 */

static Rgt_Pneumatic_Piston p;

void piston_init(void) { p = rgt_pneumatic_init('b'); }

void piston_update_state(void) { rgt_pneumatic_toggle(&p); }

void piston_opcontrol(controller_digital_e_t toggle_button) {
	if (controller_get_digital_new_press(E_CONTROLLER_MASTER, toggle_button))
		piston_toggle();
}
