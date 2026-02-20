#ifndef ARM_H_
#define ARM_H_
#include "pros/misc.h"

/**
 * @file arm.h
 *
 * @brief Function prototypes for controlling the arm
 *
 * @details This file contains declarations/prototypes for the functions used to
 * control the arm. These functions serve as an API for the arm,
 * abstracting away specific information.
 */


 void ejector_init(void);


void ejector_out(void);

void ejector_in(void);

void ejector_stop(void);

/**
 * @brief Arm operation controller
 *
 * @details Arm controller, polls what buttons are pressed
 *          and calls their respective intake functions
 * 
 * @param up_button   - Button to call arm_up to move arm up
 * @param down_button - Button to call arm_down to move arm down
 */
void ejector_opcontrol(controller_digital_e_t up_button,
                      controller_digital_e_t down_button);



#endif