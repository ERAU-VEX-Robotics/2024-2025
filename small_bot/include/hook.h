#ifndef HOOK_H_
#define HOOK_H_
#include "pros/misc.h"

/**
 * @file hook.h
 *
 * @brief Function prototypes for controlling the hook
 *
 * @details This file contains declarations/prototypes for the functions used to
 * control the hook. These functions serve as an API for the hook,
 * abstracting away specific information.
 */

// Rotate the hook to suplex the ring into the goal
void hook_forwards(void);

// Rotate the hook in the reverse direction, opposite of scooping
void hook_reverse(void);

/**
 * @brief Hook operation controller
 *
 * @details Hook controller, polls what buttons are pressed
 *          and calls their respective hook functions
 * 
 * @param forwards_button  - Button to call hook_up to move hook up
 * @param reverse_button  - Button to call hook_down to move hook down
 */
void hook_opcontrol(controller_digital_e_t forwards_button,
                    controller_digital_e_t reverse_button);

#endif 