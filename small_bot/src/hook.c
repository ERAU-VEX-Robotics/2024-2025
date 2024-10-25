#include "hook.h"

#include "pros/misc.h"

#include "ringtail/motor_group.h"

/**
 * @file hook.c
 *
 * @brief Function implementations and local variables for controlling the hook
 */

 // TODO: Correct these motor ports
static rgt_motor_group hook_motors = {10};

void hook_up(void) {
    rgt_mg_move(hook_motors, 127);  // Move hook up
}

void hook_down(void) {
    rgt_mg_move(hook_motors, -127);  // Move hook down
}

void hook_opcontrol(controller_digital_e_t up_button,
                    controller_digital_e_t down_button) {
    if (controller_get_digital(E_CONTROLLER_MASTER, up_button)) {
        hook_up();
    } else if (controller_get_digital(E_CONTROLLER_MASTER, down_button)) {
        hook_down();
    } else {
        // Turn off if no inputs
        rgt_mg_move(hook_motors, 0);
    }
} 