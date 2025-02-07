#include "conveyor.h"

#include "pros/misc.h"

#include "ringtail/motor_group.h"

/**
 * @file conveyor.c
 *
 * @brief Function implementations and local variables for controlling the conveyor
 */ 

static rgt_motor_group conveyor_run  = {1};  

void conveyor_up(void) {
    rgt_mg_move(conveyor_run, 127);
}

void conveyor_down(void) {
    rgt_mg_move(conveyor_run, -127);
}

void conveyor_opcontrol(controller_digital_e_t up_button) {
	if (controller_get_digital(E_CONTROLLER_MASTER, up_button)) {
        conveyor_up();
    } else {  
        // Turn off if no inputs
        rgt_mg_move(conveyor_run, 0);
    }
}