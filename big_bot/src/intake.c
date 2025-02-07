#include "intake.h"

#include "pros/misc.h"

#include "ringtail/motor_group.h"

/**
 * @file intake.c
 *
 * @brief Function implementations and local variables for controlling the
 * intake
 */

static rgt_motor_group intake_motors = {2, 4};

void intake_in() { rgt_mg_move(intake_motors, 127); }

void intake_out() { rgt_mg_move(intake_motors, -127); }

void intake_opcontrol(controller_digital_e_t in_button,
                      controller_digital_e_t out_button) {
	if (controller_get_digital(E_CONTROLLER_MASTER, in_button)) {
		intake_in();
	} else if (controller_get_digital(E_CONTROLLER_MASTER, out_button)) {
		intake_out();
	} else {
		// Turn off if no inputs
		rgt_mg_move(intake_motors, 0);
		// rgt_mg_move(intake_pivot, 0);
	}
}
