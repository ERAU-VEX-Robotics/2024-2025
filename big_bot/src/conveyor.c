#include "conveyor.h"

#include "pros/misc.h"

#include "pros/motors.h"
#include "ringtail/motor_group.h"

/**
 * @file conveyor.c
 *
 * @brief Function implementations and local variables for controlling the
 * conveyor
 */

static rgt_motor_group conveyor_run = {-15};

void conveyor_init(void) {
	rgt_mg_set_gearing(conveyor_run, E_MOTOR_GEAR_GREEN);
	rgt_mg_set_encoder_units(conveyor_run, E_MOTOR_ENCODER_DEGREES);
	rgt_mg_set_brake_mode(conveyor_run, E_MOTOR_BRAKE_COAST);
}


void conveyor_up(void) { rgt_mg_move(conveyor_run, 127); }

void conveyor_down(void) { rgt_mg_move(conveyor_run, -127); }

void conveyor_stop(void) { rgt_mg_move(conveyor_run, 0); }

void conveyor_opcontrol(controller_digital_e_t up_button,
                        controller_digital_e_t down_button) {
	if (controller_get_digital(E_CONTROLLER_MASTER, up_button)) {
		conveyor_up();
	} else if (controller_get_digital(E_CONTROLLER_MASTER, down_button)) {
		conveyor_down();
	} else {
		// Turn off if no inputs
		rgt_mg_move(conveyor_run, 0);
	}
}


