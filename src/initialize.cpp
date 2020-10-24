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

	intakeLeft.set_brake_mode(MOTOR_BRAKE_COAST);
	intakeRight.set_brake_mode(MOTOR_BRAKE_COAST);
	indexerBottom.set_brake_mode(MOTOR_BRAKE_HOLD);
	indexerTop.set_brake_mode(MOTOR_BRAKE_HOLD);

	inertialBoi.reset();
	delay(2000);

	//IMU Stuff
	/*int time = pros::millis();
  int iter = 0;
  while (inertialBoi.is_calibrating()) {
    lcd::print(0, "IMU calibrating... %d\n", iter);
    iter += 10;
    pros::delay(10);
  }
  // should print about 2000 ms
	lcd::clear_line(0);
  lcd::print(0, "IMU is done calibrating (took %d ms)\n", iter - time);

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
	}*/
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
