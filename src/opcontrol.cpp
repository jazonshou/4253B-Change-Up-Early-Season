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
	leftFront.set_brake_mode(MOTOR_BRAKE_COAST);
	leftBack.set_brake_mode(MOTOR_BRAKE_COAST);
	rightFront.set_brake_mode(MOTOR_BRAKE_COAST);
	rightBack.set_brake_mode(MOTOR_BRAKE_COAST);
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

		if(value == 1 && preValue == 0) {
			cnt++;
		}
		preValue = value;

		if(cnt % 2 == 1){
			autoIndex();
		}
		else {
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
		delay(5);
  }
}
