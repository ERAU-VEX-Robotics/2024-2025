#ifndef DRIVETRAIN_H_
#define DRIVETRAIN_H_

#include <stdint.h>

#include "pros/misc.h"

/**
 * @file drivetrain.h
 *
 * @brief Function prototypes for controlling the drivetrain
 *
 * @details This file contains the function prototypes that make up the
 * interface for controlling the robot.
 */

/**
 * @brief Initializes the drivetrain variables
 *
 * @details This function performs the initialization of all the variables used
 * for the drivetrain. These variables are all local to the drivetrain.c file
 * (using the static keyword at file scope), so there is no way to interact with
 * them outside of drivetrain.c.
 */
void drivetrain_init(void);

/**
 * @brief The driver control function for the drivetrain
 *
 * @details This function uses PROS's C controller API to get joystick values,
 * and uses those values to determine how to power the motors of the drivetrain.
 *
 * @param left The analog input on the controller to use to move the left motors
 * on the drivetrain
 * @param right The analog input on the controller to use to move the right
 * motors on the drivetrain
 */
void drivetrain_opcontrol(controller_analog_e_t left,
                          controller_analog_e_t right);

/**
 * @brief Moves the drive forward by the given distance, in inches
 *
 * @details This function takes in a distance to travel forward, in inches.
 * Negative values indicate moving backwards. The function sets the targets for
 * the left and right motor group PID controllers, so the PID tasks must be
 * running for the function to do anything.
 *
 * @param inches the distance to travel forward, in inches
 */
void drivetrain_move_straight(double inches);

/**
 * @brief Turns the robot counterclockwise by a given angle in degrees
 *
 * @details This function takes in an angle, in degrees, to rotate
 * counterclockwise. Negative values indicate a clockwise rotation. The function
 * sets the targets for the left and right motor group PID controllers, so the
 * PID tasks must be running for the function to do anything.
 *
 * @param angle the angle for the drive to rotate counterclockwise, in degrees
 */
void drivetrain_turn_angle(double angle);

/**
 * @brief Delays until all drivetrain PID controllers have reached their targets
 *
 * @details This function continuously calls the PROS delay function while any
 * of the PID controllers for the drivetrain have yet to reach their target.
 */
void drivetrain_wait_until_at_target(uint32_t timeout);

// Suspend the drivetrain PID tasks
void drivetrain_suspend_pid_tasks(void);

// Resume the drivetrain PID tasks
void drivetrain_resume_pid_tasks(void);

// Delete the drivetrain PID tasks
void drivetrain_delete_pid_tasks(void);

#endif /* DRIVETRAIN_H_ */