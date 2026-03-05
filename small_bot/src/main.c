#include "main.h"
#include "conveyor.h"
#include "gui.h"
#include "intake.h"
#include "pros/misc.h"
#include "pros/rtos.h"
#include "spike.h"

#include "drivetrain.h"
#include <strings.h>

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	drivetrain_init(); // Initialize drive train
	spike_init();      // Initialize the spike
	gui_init();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() { drivetrain_suspend_pid_tasks(); }

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
	auton_id=SKILLS;
	switch (auton_id) {

	case MATCH:
		break;
	case SKILLS:
		/*
		drivetrain_move_straight(25);
		drivetrain_wait_until_at_target(600);

		intake_in();

		drivetrain_move_straight(-24);
		drivetrain_wait_until_at_target(300);
		delay(1500);

		drivetrain_move_straight(50);
		drivetrain_wait_until_at_target(2000);

		drivetrain_move_straight(-10);
		drivetrain_wait_until_at_target(1500);

		drivetrain_turn_angle(-90);
		drivetrain_wait_until_at_target(2000);

		drivetrain_move_straight(-14);
		drivetrain_wait_until_at_target(1500);

		drivetrain_move_straight(-8);
		drivetrain_wait_until_at_target(1500);


		spike_toggle();

		drivetrain_wait_until_at_target(500);

		drivetrain_move_straight(24);
		drivetrain_wait_until_at_target(1000);

		*/
		conveyor_up();
		delay(1500);
		/*
		
		drivetrain_turn_angle(-150);
		drivetrain_wait_until_at_target(2000);

		intake_in();

		drivetrain_move_straight(36);
		drivetrain_wait_until_at_target(2000);

		conveyor_up();

		drivetrain_turn_angle(-180);
		drivetrain_wait_until_at_target(2000);

		drivetrain_move_straight(-20);
		drivetrain_wait_until_at_target(2000);

		spike_toggle();
		conveyor_down();
		delay(500);
		conveyor_stop();

		drivetrain_move_straight(10);
		drivetrain_wait_until_at_target(1000);
		*/
		break;
	default:
		break;
	}
}

/**
 * Runs the operator control code. This function will be started in its own
 * task with the default priority and stack size whenever the robot is
 * enabled via the Field Management System or the VEX Competition Switch in
 * the operator control mode.
 *
 * If no competition control is connected, this function will run
 * immediately following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart
 * the task, not resume it from where it left off.
 */
void opcontrol() {
	drivetrain_suspend_pid_tasks();

	while (true) {
		intake_opcontrol(E_CONTROLLER_DIGITAL_L1, E_CONTROLLER_DIGITAL_L2,
		                 E_CONTROLLER_DIGITAL_R1, E_CONTROLLER_DIGITAL_R2);

		conveyor_opcontrol(E_CONTROLLER_DIGITAL_L1, E_CONTROLLER_DIGITAL_L2);
		spike_opcontrol(E_CONTROLLER_DIGITAL_A);

		drivetrain_opcontrol(ANALOG_LEFT_Y, ANALOG_RIGHT_Y);
		delay(20);
	}
}
