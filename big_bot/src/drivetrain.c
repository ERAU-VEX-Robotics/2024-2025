#include "drivetrain.h"

#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"

#include "ringtail/controller.h"
#include "ringtail/motor_group.h"
#include "ringtail/reference_controllers.h"
#include <math.h>
#include <stdio.h>

/**
 * @file drivetrain.c
 *
 * @brief Function implementations and local variables for the drivetrain
 */

// Motor groups for each side of the drivetrain
static rgt_motor_group right_motors = {18, 19, 20};
static rgt_motor_group left_motors = {-8, -9, -10};

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

static uint16_t kP = 20;
static uint16_t kI = 1;
static uint16_t kD = 15;

/**
 * Gear Ratio on the drivetrain -  defined as:
 * # of teeth on the gears attached to the wheels /
 * # of teeth on the gears attached to the sensor - in this case the motor
 */
static const double GEAR_RATIO = 36.0 / 60.0;

static const double WHEEL_DIAMETER = 3.25;
static const double BASE_WIDTH = 14.5;

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

	rgt_mg_set_gearing(left_motors, E_MOTOR_GEAR_GREEN);
	rgt_mg_set_gearing(right_motors, E_MOTOR_GEAR_GREEN);
	rgt_mg_set_encoder_units(left_motors, E_MOTOR_ENCODER_DEGREES);
	rgt_mg_set_encoder_units(right_motors, E_MOTOR_ENCODER_DEGREES);

	rgt_mg_set_brake_mode(left_motors, E_MOTOR_BRAKE_COAST);
	rgt_mg_set_brake_mode(right_motors, E_MOTOR_BRAKE_COAST);
}

void drivetrain_opcontrol(controller_analog_e_t left,
                          controller_analog_e_t right) {
	rgt_mg_move(left_motors, controller_get_analog(E_CONTROLLER_MASTER, left));
	rgt_mg_move(right_motors,
	            controller_get_analog(E_CONTROLLER_MASTER, right));
}

void drivetrain_move_straight(double inches) {
	kP = 290;
	kI = 1;
	kD = 25;

	double target = inches / (WHEEL_DIAMETER / 2) * 180 / M_PI;
	rgt_mg_reset_positions(left_motors);
	rgt_mg_reset_positions(right_motors);
	rgt_controller_reset(&left_pid_info);
	rgt_controller_reset(&right_pid_info);

	rgt_controller_set_target(&left_pid_info, target);
	rgt_controller_set_target(&right_pid_info, target);
}

void drivetrain_turn_angle(double angle) {
	kP = 290;
	kI = 3;
	kD = 25;

	double inches = angle * BASE_WIDTH / 2;
	double target = inches / (WHEEL_DIAMETER / 2) * 180 / M_PI;

	rgt_mg_reset_positions(left_motors);
	rgt_mg_reset_positions(right_motors);

	rgt_controller_reset(&left_pid_info);
	rgt_controller_reset(&right_pid_info);

	rgt_controller_set_target(&left_pid_info, target);
	rgt_controller_set_target(&right_pid_info, -target);
}

void drivetrain_wait_until_at_target(uint32_t timeout) {
	while ((!rgt_controller_at_target(&right_pid_info) ||
	        !rgt_controller_at_target(&left_pid_info)) &&
	       timeout > 0) {

		timeout -= 2;
		delay(2);
	}
}

double left_mg_get_pos(void) {
	// Return average motor encoder position, accounting for 5:3 gear ratio
	// from motor to wheel
	return rgt_mg_get_average_position(left_motors) * GEAR_RATIO;
}
double right_mg_get_pos(void) {
	// Return average motor encoder position, accounting for 5:3 gear ratio
	// from motor to wheel
	return rgt_mg_get_average_position(right_motors) * GEAR_RATIO;
}

double left_mg_controller(double target, double current, bool reset) {
	static double integral, prev_error = 0;

	bool clear_integral = false;

	double error = target - current;

	if (fabs(error) > ERROR_ACCUMULATION_THRESH)
		clear_integral = true;

	if (reset) {
		prev_error = 0;
		clear_integral = true;
	}

	double voltage =
	    pid(error, kP, kI, kD, &integral, prev_error, clear_integral);

	prev_error = error;

	return voltage;
}

double right_mg_controller(double target, double current, bool reset) {
	static double integral, prev_error = 0;

	bool clear_integral = false;

	double error = target - current;

	if (fabs(error) > ERROR_ACCUMULATION_THRESH)
		clear_integral = true;

	if (reset) {
		prev_error = 0;
		clear_integral = true;
	}

	double voltage =
	    pid(error, kP, kI, kD, &integral, prev_error, clear_integral);

	prev_error = error;

	return voltage;
}

// Suspend the drivetrain PID tasks
void drivetrain_suspend_pid_tasks(void) {
	task_suspend(left_pid_task);
	task_suspend(right_pid_task);
}

// Resume the drivetrain PID tasks
void drivetrain_resume_pid_tasks(void) {
	task_resume(left_pid_task);
	task_resume(right_pid_task);
}

// Delete the drivetrain PID tasks
void drivetrain_delete_pid_tasks(void) {
	task_delete(left_pid_task);
	task_delete(right_pid_task);
}
