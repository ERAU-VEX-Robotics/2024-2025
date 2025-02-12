#include "piston.h"

#include "pros/adi.h"
#include "pros/misc.h"

#include <stdbool.h>

/**
 * @file piston.c
 *
 * @brief Function implementations for big bot's piston
 */

static const uint8_t piston_port = 'b';
static bool piston_extended = false;

void piston_init(void) { adi_port_set_config(piston_port, E_ADI_DIGITAL_OUT); }

void piston_update_state(void) {
	adi_port_set_value(piston_port, piston_extended);
}

void piston_toggle(void) {
	piston_extended = !piston_extended;
	piston_update_state();
}

void piston_opcontrol(controller_digital_e_t toggle_button) {
	if (controller_get_digital_new_press(E_CONTROLLER_MASTER, toggle_button))
		piston_toggle();
}
