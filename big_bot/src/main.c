#include "main.h"
#include "arm.h"
#include "conveyor.h"
#include "drivetrain.h"
#include "gui.h"
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
	piston_init();
	gui_init();
	drivetrain_init();
	intake_init();
	conveyor_init();
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
	auton_id = SKILLS;
	switch (auton_id) {
	case SKILLS:
		drivetrain_move_straight(30); // Move to ring 1
		delay(500);
		conveyor_up();
		intake_in(); // Intake ring 1
		drivetrain_wait_until_at_target(2000);
		drivetrain_turn_angle(-80); //290, turn to ring 2
		delay(1000);
		conveyor_stop();
		delay(1000);
		drivetrain_wait_until_at_target(500);
		delay(1000);
		intake_in(); // intake ring 2
		delay(1000);
		drivetrain_move_straight(36); // move to ring 2
		delay(500);
		drivetrain_wait_until_at_target(3000);
		//
		delay(500);
		drivetrain_turn_angle(100); //-315, -325, turn to goal
		intake_stop();
		drivetrain_wait_until_at_target(1500);
		drivetrain_move_straight(-30); //-24, move to goal
		drivetrain_wait_until_at_target(1500);
		piston_toggle(); // take goal
		drivetrain_move_straight(-30); // move to set up for goal placement
		drivetrain_wait_until_at_target(2500);	
		drivetrain_turn_angle(90); //-400 , turn to place goal
		drivetrain_wait_until_at_target(1500);	

		delay(500);
		drivetrain_move_straight(2);
		drivetrain_wait_until_at_target(1000);
		delay(500);
		conveyor_up(); //place rings on goal
		intake_half();
		delay(5000); // 4000	
		
		drivetrain_move_straight(-38); //-36 move to place goal
		drivetrain_wait_until_at_target(2500);
		intake_stop();
		conveyor_down();
		piston_toggle(); // release goal	
		drivetrain_move_straight(24); // back away 
		drivetrain_wait_until_at_target(2500);
		//
		conveyor_stop();
		drivetrain_move_straight(1); //Attempt to stop moving
		drivetrain_wait_until_at_target(1000); 
		break;
	case MATCH:
		break;
	case TEST:
		break;
	}
	drivetrain_suspend_pid_tasks();
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
