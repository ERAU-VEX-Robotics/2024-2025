#include "arm.h"

#include "pros/misc.h"

#include "ringtail/motor_group.h"

/**
 * @file arm.c
 *
 * @brief Function implementations and local variables for controlling the intake
 */ 
static rgt_motor_group ejector = {13};
void ejector_init(void) {
	rgt_mg_set_gearing(ejector, E_MOTOR_GEAR_GREEN);
	rgt_mg_set_encoder_units(ejector, E_MOTOR_ENCODER_DEGREES);
	rgt_mg_set_brake_mode(ejector, E_MOTOR_BRAKE_COAST);
}

void ejector_out(void) { rgt_mg_move(ejector, 127); }

void ejector_in(void) { rgt_mg_move(ejector, -127); }

void ejector_stop(void) { rgt_mg_move(ejector, 0); }

void ejector_opcontrol(controller_digital_e_t up_button,
                        controller_digital_e_t down_button) {
	if (controller_get_digital(E_CONTROLLER_MASTER, up_button)) {
		ejector_out();
	} else if (controller_get_digital(E_CONTROLLER_MASTER, down_button)) {
		ejector_in();
	} else {
		// Turn off if no inputs
		rgt_mg_move(ejector, 0);
	}
}