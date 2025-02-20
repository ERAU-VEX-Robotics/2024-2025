#include "main.h"
#include "arm.h"
#include "conveyor.h"
#include "drivetrain.h"
#include "intake.h"
#include "piston.h"
#include "pros/misc.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	drivetrain_init();
	intake_init();
	conveyor_init();
	piston_init();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	drivetrain_resume_pid_tasks();
	drivetrain_move_straight(24);
	conveyor_up();
	intake_in();
	delay(2000);
	intake_half();
	delay(2500);
	conveyor_stop();
	drivetrain_wait_until_at_target(500);
	//delay(18000);
	intake_stop();
	drivetrain_turn_angle(-45);
	drivetrain_wait_until_at_target(1500);
	intake_in();
	drivetrain_move_straight(20);
	delay(3000);
	intake_stop();
	drivetrain_wait_until_at_target(1500);
	drivetrain_turn_angle(45);
	drivetrain_wait_until_at_target(1500);
	drivetrain_move_straight(-3.8);
	drivetrain_wait_until_at_target(1000);
	piston_toggle();
	conveyor_up();
	intake_half();
	delay(4000);
	drivetrain_turn_angle(-180);
	drivetrain_wait_until_at_target(1500);
	drivetrain_turn_angle(45);
	drivetrain_wait_until_at_target(1500);	
	drivetrain_move_straight(20);
	drivetrain_wait_until_at_target(1000);
	/*intake_stop();
	drivetrain_move_straight(-1);
	drivetrain_wait_until_at_target(1000);
	drivetrain_turn_angle(90);
	drivetrain_wait_until_at_target(1500);
	drivetrain_turn_angle(-90)
	conveyer_stop();
	drivetrain_move_straight(-1);
	drivetrain_wait_until_at_target(1000);	
	piston_toggle();
	*/
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	drivetrain_suspend_pid_tasks();
	while (true) {
		intake_opcontrol(E_CONTROLLER_DIGITAL_R2, E_CONTROLLER_DIGITAL_R1);

		conveyor_opcontrol(E_CONTROLLER_DIGITAL_L2, E_CONTROLLER_DIGITAL_A);
		drivetrain_opcontrol(E_CONTROLLER_ANALOG_LEFT_Y,
		                     E_CONTROLLER_ANALOG_RIGHT_Y);
		// arm_opcontrol(E_CONTROLLER_DIGITAL_UP, E_CONTROLLER_DIGITAL_DOWN);
		piston_opcontrol(E_CONTROLLER_DIGITAL_L1);
		delay(20); // Run for 20 ms then update
	}
	drivetrain_delete_pid_tasks();
}
