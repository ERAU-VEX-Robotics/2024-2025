#include "arm.h"

#include "pros/misc.h"

#include "ringtail/motor_group.h"

/**
 * @file arm.c
 *
 * @brief Function implementations and local variables for controlling the intake
 */ 
 
static rgt_motor_group arm_motors = {-1, 2};

 void arm_up(){
    rgt_mg_move(arm_motors, 127);
 }

 void arm_down(){
    rgt_mg_move(arm_motors, -127);
 }

 void arm_opcontrol(controller_digital_e_t up_button,
                      controller_digital_e_t down_button){
    if (controller_get_digital(E_CONTROLLER_MASTER, up_button)) {
        arm_up();
    } else if (controller_get_digital(E_CONTROLLER_MASTER, down_button)) {
        arm_down();
     } else {  
        // Turn off if no inputs
        rgt_mg_move(arm_motors, 0);
    }

}