#include "drivetrain.h"

#include "pros/misc.h"
#include "pros/rtos.h"

#include "ringtail/controller.h"
#include "ringtail/motor_group.h"
#include "ringtail/reference_controllers.h"
#include <math.h>

/**
 * @file drivetrain.c
 *
 * @brief Function implementations and local variables for the drivetrain
 */

// Motor groups for each side of the drivetrain
static rgt_motor_group left_motors = {-11, -2, -1};
static rgt_motor_group right_motors = {8, 7, 6};

/**
 * Ringtail task variables and function prototypes for each side of the
 * drivetrain
 */
static mutex_t left_mutex;
static mutex_t right_mutex;

static task_t left_pid_task;
static task_t right_pid_task;

static Rgt_Controller_Info left_pid_info;
static Rgt_Controller_Info right_pid_info;

double left_mg_get_pos(void);
double right_mg_get_pos(void);

double left_mg_controller(double target, double current, bool reset);
double right_mg_controller(double target, double current, bool reset);

/**
 * Gear Ratio on the drivetrain -  defined as:
 * # of teeth on the gears attached to the wheels /
 * # of teeth on the gears attached to the sensor - in this case the motor
 */
static const double GEAR_RATIO = 36.0 / 60.0;

static const double WHEEL_DIAMETER = 3.25;
static const double BASE_WIDTH = 11.375;

/**
 * Motor encoder position threshold within which the drivetrain's PID
 * controllers begin accumulating error i.e. the I part of the PID becomes
 * relevant.
 */
static const double ERROR_ACCUMULATION_THRESH = 50;

void drivetrain_init(void) {
	left_mutex = mutex_create();
	right_mutex = mutex_create();

	left_pid_info = rgt_controller_info_init(
	    left_motors, left_mg_get_pos, left_mg_controller, left_mutex, 5.0, 20);
	right_pid_info =
	    rgt_controller_info_init(right_motors, right_mg_get_pos,
	                             right_mg_controller, right_mutex, 5.0, 20);

	left_pid_task = rgt_controller_create(&left_pid_info, TASK_PRIORITY_DEFAULT,
	                                      TASK_STACK_DEPTH_DEFAULT,
	                                      "Drive Left Controller");
	right_pid_task = rgt_controller_create(
	    &right_pid_info, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT,
	    "Drive Right Controller");
}

void drivetrain_opcontrol(controller_analog_e_t left,
                          controller_analog_e_t right) {
	rgt_mg_move(left_motors, controller_get_analog(E_CONTROLLER_MASTER, left));
	rgt_mg_move(right_motors,
	            controller_get_analog(E_CONTROLLER_MASTER, right));
}

void drivetrain_move_straight(double inches) {
	double target = inches * WHEEL_DIAMETER / 2 * 180 / M_PI;
	rgt_controller_set_target(&left_pid_info, target);
	rgt_controller_set_target(&right_pid_info, target);
}

void drivetrain_turn_angle(double angle) {
	double inches = angle * M_PI / 180 * BASE_WIDTH / 2;
	double target = inches * WHEEL_DIAMETER / 2 * 180 / M_PI;
	rgt_controller_set_target(&left_pid_info, target);
	rgt_controller_set_target(&right_pid_info, -target);
}

double left_mg_get_pos(void) {
	// Return average motor encoder position, accounting for 5:3 gear ratio from
	// motor to wheel
	return rgt_mg_get_average_position(left_motors) * GEAR_RATIO;
}
double right_mg_get_pos(void) {
	// Return average motor encoder position, accounting for 5:3 gear ratio from
	// motor to wheel
	return rgt_mg_get_average_position(right_motors) * GEAR_RATIO;
}

double left_mg_controller(double target, double current, bool reset) {
	static double integral, prev_error = 0;

	bool clear_integral = false;

	double error = target - current;

	if (error > ERROR_ACCUMULATION_THRESH)
		clear_integral = true;

	if (reset) {
		prev_error = 0;
		clear_integral = true;
	}

	double voltage =
	    pid(error, 20, 2, 5, &integral, prev_error, clear_integral);

	prev_error = error;

	return voltage;
}

double right_mg_controller(double target, double current, bool reset) {
	static double integral, prev_error = 0;

	bool clear_integral = false;

	double error = target - current;

	if (error > ERROR_ACCUMULATION_THRESH)
		clear_integral = true;

	if (reset) {
		prev_error = 0;
		clear_integral = true;
	}

	double voltage =
	    pid(error, 20, 2, 5, &integral, prev_error, clear_integral);

	prev_error = error;

	return voltage;
}