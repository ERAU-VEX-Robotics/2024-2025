#include "drivetrain.h"

#include "pros/misc.h"
#include "ringtail/motor_group.h"

/**
 * @file drivetrain.c
 *
 * @brief Function implementations and local variables for the drivetrain
 */

static rgt_motor_group left_motors = {};
static rgt_motor_group right_motors = {};

void drivetrain_init(void) {}

void drivetrain_opcontrol(controller_analog_e_t left,
                          controller_analog_e_t right) {
	rgt_mg_move(left_motors, controller_get_analog(E_CONTROLLER_MASTER, left));
	rgt_mg_move(right_motors,
	            controller_get_analog(E_CONTROLLER_MASTER, right));
}