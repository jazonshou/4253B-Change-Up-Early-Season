#include "main.h"

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
		leftFront = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		leftBack = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		rightFront = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
	  rightBack = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

		//AUTO INTAKE
		int value = master.get_digital(E_CONTROLLER_DIGITAL_A);

		//if the button A is pressed
		//start the autoIndex
		//but if the button A is pressed again
		//stop the autoIndex
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

	//SCREEN TESTING
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

		//ODOM TESTING
		//odom_print();
		/*lcd::print(0, "Left encoder value: %d", encoderLeft.get_value());
		lcd::print(1, "Right encoder value: %d", encoderRight.get_value());
		lcd::print(2, "Back encoder value: %d", encoderBack.get_value());
		lcd::print(3, "Rotation: %d", inertialBoi.get_rotation());*/
}
