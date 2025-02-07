#ifndef SPIKE_H_
#define SPIKE_H_
#include "pros/misc.h"

/**
 * @file spike.h
 *
 * @brief Function prototypes for controlling the spike
 *
 * @details This file contains declarations/prototypes for the
 * functions used to control the spike. These functions serve
 * as an API for the spike, abstracting away specific information.
 */

// Initialize spike
void spike_init(void);

// Toggle the spike to extend or retract fully
void spike_toggle(void);

/**
 * @brief Spike operation controller
 *
 * @details Spike controller, polls what button is pressed
 *          and calls the respective spike function
 *
 * @param toggle_button   - Button to call spike_toggle to toggle the spike
 */
void spike_opcontrol(controller_digital_e_t toggle_button);

#endif /* SPIKE_H_ */
