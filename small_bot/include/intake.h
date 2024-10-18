#ifndef INTAKE_H_
#define INTAKE_H_

/**
 * @file intake.h
 *
 * @brief Function prototypes for controlling the intake
 *
 * @details This file contains declarations/prototypes for the functions used to
 * control the intake. These functions serve as an API for the intake,
 * abstracting away specific information.
 */

// Initializes internal intake variables
void intake_init(void);

// Moves the intake up
void intake_up(void);

// Moves the intake down
void intake_down(void);

// Intake grabs ring
void intake_in(void);

// Intake releases ring
void intake_out(void);



#endif
