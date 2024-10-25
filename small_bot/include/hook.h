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

 // Moves the hook up
void hook_up(void);

// Moves the hook down
void hook_down(void);

/**
 * @brief Hook operation controller
 *
 * @details Hook controller, polls what buttons are pressed
 *          and calls their respective hook functions
 * 
 * @param up_button   - Button to call hook_up to move hook up
 * @param down_button - Button to call hook_down to move hook down
 * @param in_button   - Button to call hook_in to grab ring
 * @param out_button  - Button to call hook_out to release held ring
 */

void hook_opcontrol(controller_digital_e_t up_button,
                    controller_digital_e_t down_button,
                    controller_digital_e_t in_button,
                    controller_digital_e_t out_button);

#endif 