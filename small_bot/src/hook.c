#include "hook.h"

#include "pros/misc.h"

#include "ringtail/motor_group.h"

/**
 * @file hook.c
 *
 * @brief Function implementations and local variables for controlling the hook
 */

 // TODO: Correct these motor ports
 // Initialize motor group object for the rotating the hook
static rgt_motor_group hook_motor = {18};  

// Hook function implementations
void hook_forwards(void) {
    rgt_mg_move(hook_motor, -127);  // Rotate hook to "suplex" the ring onto the goal
}

void hook_reverse(void) {
    rgt_mg_move(hook_motor, 127);  // Reverse hook rotation, pushing
}

// Hook opcontrol implementation
void hook_opcontrol(controller_digital_e_t forwards_button,
                    controller_digital_e_t reverse_button) {
    if (controller_get_digital(E_CONTROLLER_MASTER, forwards_button)) {
        hook_forwards();
    } else if (controller_get_digital(E_CONTROLLER_MASTER, reverse_button)) {
        hook_reverse();
    } else {
        // Turn off if no inputs
        rgt_mg_move(hook_motor, 0);
    }
} 