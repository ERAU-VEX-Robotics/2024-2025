/**
 * @file controller.h
 *
 * @brief Functions and structures used to build arbitrary async controllers
 *
 * @details Ringtail provides a generic way to create your own asynchronous
 * motion controllers. It requires you to write the actual controller function,
 * as well as functions to get the sensor data to compare with the target value.
 * This file contains the type and function definitions for the controller
 * system.
 */

#include "ringtail/motor_group.h"

#include "pros/rtos.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	int8_t *mg; // Ringtail Motor Group to control
	// Function to get sensor data used as the controller input
	double (*get_sensor_data)(void);
	// Function to determine the voltage to send to the motor group - the
	// "controller". Must take the target value, current value, and a boolean
	// for indicating a reset
	double (*calculate_voltage)(double, double, bool);
	// The target value for the controller - can be initialized to 0
	double target;
	// Whether the state of the controller should be reset. This exists mainly
	// as a flag to be used for calculate_voltage
	bool reset;
	// Indicates whether the controller has reached the target value
	bool at_target;
	// The maximum value of error at which the controller considers itself to be
	// at the target value
	double error_settle_threshold;
	// The number of iterations that the controller is within
	// error_settle_threshold before the controller sets at_target to true
	uint32_t error_below_thresh_max_cnt;
	// Mutex to prevent race conditions
	mutex_t mutex;
} Rgt_Controller_Info;

/**
 * @brief Creates a Rgt_Controller_Info struct, initalizing some values with
 * sane defaults
 *
 * @details This function simplifies the creation of a Rgt_Controller_Info
 * struct by removing the need to initialize some variables, namely: target,
 * reset, and at_target.
 *
 * @param mg The Ringtail Motor Group to control
 * @param get_sensor_data A function pointer that returns the sensor data to be
 * used as input to the controller.
 * @param calculate_voltage A function pointer to a function that determines the
 * voltage to supply to the controller based on the target value and current
 * value - also includes a flag to allow for resetting the state of the
 * controller.
 * @param mutex A mutex lock - used to prevent race conditions
 * @param error_settle_threshold The maximum value of error at which the
 * controller considers itself to be at the target value
 * @param error_below_thresh_max_cnt The number of iterations that the
 * controller is within error_settle_threshold before the controller sets
 * at_target to true
 */
Rgt_Controller_Info
rgt_controller_info_init(rgt_motor_group mg, double (*get_sensor_data)(void),
                         double (*calculate_voltage)(double, double, bool),
                         mutex_t mutex, double error_settle_threshold,
                         uint32_t error_below_thresh_max_cnt);

/**
 * @brief Creates a Ringtail Controller as a PROS task
 *
 * @details This function handles the creation of a Ringtail controller as a
 * PROS task. It creates a task whose function is Ringtail's controller
 * function. This function runs forever (with a 10ms delay between cycles). This
 * function handles the actual control of the motor - getting the current sensor
 * data, determining the error and if the controller has reached its target,
 * determining the output voltage, and moving the motor group.
 *
 * @param Rgt_Controller_Info The Controller info to use for the controller
 * The other parameters are directly passed to PROS's task_create function, see
 * the PROS docs on that function, found here:
 * https://pros.cs.purdue.edu/v5/api/c/rtos.html#task-create
 */
task_t rgt_controller_create(Rgt_Controller_Info *i, uint8_t priority,
                             uint16_t stack_depth, const char *name);

/**
 * @brief Gets the at_target value from a Rgt_Controller_Info
 *
 * @details To ensure that the at_target value is accurate, one must take the
 * mutex in the Rgt_Controller_Info struct. This function wraps that process,
 * allowing programmers to ignore the specifics of multithreading.
 */
bool rgt_controller_at_target(Rgt_Controller_Info *i);

/**
 * @brief Sets the reset flag for the controller
 *
 * @details Sets the reset flag for the controller, including taking and giving
 * the mutex - allowing programmers to ignore the specifics of multithreading.
 */
void rgt_controller_reset(Rgt_Controller_Info *i);

/**
 * @brief Sets the target for the controller
 *
 * @details Sets the target for the controller, including taking and giving
 * the mutex - allowing programmers to ignore the specifics of multithreading.
 */
void rgt_controller_set_target(Rgt_Controller_Info *i, double target);
