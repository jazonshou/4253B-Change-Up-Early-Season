#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	//Sets break types on all motors
	leftFront.set_brake_mode(MOTOR_BRAKE_COAST);
	leftBack.set_brake_mode(MOTOR_BRAKE_COAST);
	rightFront.set_brake_mode(MOTOR_BRAKE_COAST);
	rightBack.set_brake_mode(MOTOR_BRAKE_COAST);

	intakeLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);
	intakeRight.set_brake_mode(MOTOR_BRAKE_BRAKE);
	indexerBottom.set_brake_mode(MOTOR_BRAKE_HOLD);
	indexerTop.set_brake_mode(MOTOR_BRAKE_HOLD);

	//IMU Stuff
	/*inertialBoi.reset();
	while(inertialBoi.is_calibrating()){
		master.rumble(". - -");
		delay(10);
	}
	delay(2000);*/

	//SCREEN
	int number = 0;

	if(limitSwitch.get_value()) {
		number ++;
		number %= 4;
	}

	switch(number) {
		case 0:
		lcd::clear();
		lcd::print(1, "Auton 1");
		break;

		case 1:
		lcd::clear();
		lcd::print(1, "Auton 2");
		break;

		case 2:
		lcd::clear();
		lcd::print(1, "Auton 3");
		break;

		case 3:
		lcd::clear();
		lcd::print(1, "Auton 4");
		break;
	}
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
	//For PID tuning purposes
	drivePIDD(2000);
	drivePIDD(1000);
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
	//Auto intake stuff
	int preValue = 0;
	int cnt = 0;

	while(1) {
		//DRIVE CONTROL
		leftFront = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		leftBack = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		rightFront = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
	  rightBack = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);

		//AUTO INTAKE
		int value = master.get_digital(E_CONTROLLER_DIGITAL_A);

		if(value == 1 && preValue == 0) {
			cnt++;
		}
		preValue = value;

		if(cnt % 2 == 1){
			autoIndex();
		}
		else{
			setIntakes(0, 0);
			setIndexer(0, 0);
		}

		//MANUAL INDEXER & INTAKE CONTROL
		if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
			setIntakes(127, 127);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
			setIntakes(-127, -127);
		}

		if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
			setIndexer(127, 127);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){
			setIndexer(-127, -127);
		}
		delay(15);
	}

	//SCREEN testing
	  int number = 0;
		if(limitSwitch.get_value()) {
			number ++;
			number %= 4;
		}

		switch(number) {
			case 0:
			lcd::clear();
			lcd::print(1, "Auton 1");
			break;

			case 1:
			lcd::clear();
			lcd::print(1, "Auton 2");
			break;

			case 2:
			lcd::clear();
			lcd::print(1, "Auton 3");
			break;

			case 3:
			lcd::clear();
			lcd::print(1, "Auton 4");
			break;
		}
}
