#ifndef CONVEYOR_H_
#define CONVEYOR_H_
#include "pros/misc.h"

/**
 * @file conveyor.h
 *
 * @brief Function prototypes for controlling the conveyor
 *
 * @details This file contains declarations/prototypes for the functions used to
 * control the conveyor. These functions serve as an API for the conveyor,
 * abstracting away specific information.
 */

// Moves the conveyor up
void conveyor_up(void);

// Moves the conveyor down
void conveyor_down(void);

/**
 * @brief Conveyor operation controller
 *
 * @details Conveyor controller, polls what buttons are pressed
 *          and calls their respective conveyor functions
 *
 * @param up_button   Button to call conveyor_up to move conveyor up
 * @param down_button Button to call conveyor_down to move conveyor down
 */
void conveyor_opcontrol(controller_digital_e_t up_button,
                        controller_digital_e_t down_button);

#endif
