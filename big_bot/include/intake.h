#ifndef INTAKE_H_
#define INTAKE_H_
#include "pros/misc.h"

/**
 * @file intake.h
 *
 * @brief Function prototypes for controlling the intake
 *
 * @details This file contains declarations/prototypes for the functions used to
 * control the intake. These functions serve as an API for the intake,
 * abstracting away specific information.
 */

// Moves the intake up
void intake_up(void);

// Moves the intake down
void intake_down(void);

// Intake grabs ring
void intake_in(void);

// Intake releases ring
void intake_out(void);

/**
 * @brief Intake operation controller
 *
 * @details Intake controller, polls what buttons are pressed
 *          and calls their respective intake functions
 *
 * @param up_button   Button to call intake_up to move intake up
 * @param down_button Button to call intake_down to move intake down
 * @param in_button   Button to call intake_in to pull in ring
 * @param out_button  Button to call intake_out to release held ring
 */
void intake_opcontrol(controller_digital_e_t up_button,
                      controller_digital_e_t down_button,
                      controller_digital_e_t in_button,
                      controller_digital_e_t out_button);

#endif