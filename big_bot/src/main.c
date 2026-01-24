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
	auton_id=SKILLS;
	switch (auton_id) {
	case SKILLS:
		int AmountOfDelay = 3000;
		int AmountOfTurnDelay = 2000;
		//first ring
		drivetrain_move_straight(24.5); // Move to ring 1
		intake_in(); // Intake ring 1
		drivetrain_wait_until_at_target(AmountOfDelay);
		intake_half();// make sure intake dosent get fuckey

		//1st mobile goal
		drivetrain_turn_angle(90); // 290, turn to mobile goal
		drivetrain_wait_until_at_target(AmountOfDelay);
		drivetrain_move_straight(-24);	//mode to mobile goal	
		drivetrain_wait_until_at_target(2000);
		piston_toggle();//take mobile goal
		delay(500);

		//2nd ring
		drivetrain_turn_angle(90);//turn to ring 2
		drivetrain_wait_until_at_target(AmountOfTurnDelay);
		conveyor_up();//place ring on mobile goal
		intake_in();
		drivetrain_move_straight(24);//move to ring 2
		drivetrain_wait_until_at_target(AmountOfDelay);
		
		//3rd ring
		drivetrain_turn_angle(45);//turn to corner
		drivetrain_wait_until_at_target(AmountOfDelay);
		drivetrain_move_straight(40);//move to ring 3
		drivetrain_wait_until_at_target(AmountOfDelay);
		delay(1000);

		//place 1st mobile goal
		drivetrain_move_straight(-20);//move away from corner
		drivetrain_wait_until_at_target(AmountOfDelay);	
		delay(1000);
		drivetrain_turn_angle(180);//turn around
		drivetrain_wait_until_at_target(AmountOfDelay);
		drivetrain_move_straight(-40);//move twords corner
		drivetrain_wait_until_at_target(AmountOfDelay);
		piston_toggle();//place piston in corner
		conveyor_down();
		delay(500);
		conveyor_stop();
		intake_in();

		//4th ring
		drivetrain_move_straight(16);//move away from corner
		drivetrain_wait_until_at_target(2000);
		drivetrain_turn_angle(305); //turn twords ring 4
		drivetrain_wait_until_at_target(AmountOfDelay);
		drivetrain_move_straight(-24);//move twords ring 4
		drivetrain_wait_until_at_target(AmountOfDelay);
		drivetrain_move_straight(57);//move twords ring 4
		drivetrain_wait_until_at_target(AmountOfDelay);	

		//2nd mobile goal
		drivetrain_turn_angle(230);//turn twords mobile goal 2
		drivetrain_wait_until_at_target(AmountOfDelay);	
		intake_half();
		drivetrain_move_straight(-28);//move twords mobile goal 2
		drivetrain_wait_until_at_target(AmountOfDelay);
		piston_toggle();//pick up mobile goal 2

		//5th ring
		conveyor_up();	
		drivetrain_turn_angle(90);//turn twords rings 5
		drivetrain_wait_until_at_target(AmountOfDelay);	
		drivetrain_move_straight(24);//go twords ring 5
		intake_in();
		drivetrain_wait_until_at_target(1500);
		drivetrain_move_straight(18);//go twords corner
		drivetrain_wait_until_at_target(1500);
		delay(500);

		//place 2nd mobile goal
		drivetrain_turn_angle(180);//turn around
		drivetrain_wait_until_at_target(AmountOfDelay);
		conveyor_stop();//stop convayer to make sure we dont place the blue ring
		drivetrain_move_straight(-26);//go twords corncer
		drivetrain_wait_until_at_target(AmountOfDelay);
		piston_toggle();//release mobile goal
		drivetrain_move_straight(24);//move away from corner
		drivetrain_wait_until_at_target(AmountOfDelay);
		break;
	case MATCH:
		drivetrain_move_straight(-24); // Move to ring 1
		drivetrain_wait_until_at_target(2500);
		piston_toggle();
		drivetrain_move_straight(24); //-400 , turn to place goal
		drivetrain_wait_until_at_target(1500);
		conveyor_up();
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

		conveyor_opcontrol(E_CONTROLLER_DIGITAL_L1, E_CONTROLLER_DIGITAL_L2);
		drivetrain_opcontrol(E_CONTROLLER_ANALOG_LEFT_X, E_CONTROLLER_ANALOG_RIGHT_X, E_CONTROLLER_ANALOG_LEFT_Y, E_CONTROLLER_ANALOG_RIGHT_Y);
		// arm_opcontrol(E_CONTROLLER_DIGITAL_UP, E_CONTROLLER_DIGITAL_DOWN);
		piston_opcontrol(E_CONTROLLER_DIGITAL_A);
		delay(20); // Run for 20 ms then update

		//printf("Port 6: %d\n", motor_get_voltage(6));
		//printf("Port 7: %d\n", motor_get_voltage(7));
		
		//delay(2);
	}
	drivetrain_delete_pid_tasks();
}
