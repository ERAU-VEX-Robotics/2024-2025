#ifndef PISTON_H_
#define PISTON_H_

#include "pros/misc.h"

/**
 * @file piston.h
 *
 * @brief Function prototypes for controlling big bot's piston
 *
 * @details Big bot's piston subsystem actuates a pneumatic piston to grab the
 * mobile goal. This file provides the user-facing API for controlling the
 * piston.
 */

// Initialize piston variables, ADI port
void piston_init(void);

// Toggle the piston to extend or retract fully
void piston_toggle(void);

/**
 * @brief Piston operation controller
 *
 * @details Piston controller, polls what button is pressed
 *          and calls the respective piston function
 *
 * @param toggle_button - Button to call piston_toggle to toggle the piston
 */
void piston_opcontrol(controller_digital_e_t toggle_button);

#endif /* PISTON_H_ */
