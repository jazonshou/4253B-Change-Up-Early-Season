#include "main.h"

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

void blueHomeRow(){
  setIntakes(127, 127); delay(300); setIntakes(0, 0);
  driveShort(12, true, 10000);
  setIntakes(0, 0);
  setDrive(100, 20); delay(400); setDrive(0, 0);
  cycle();
  driveMedium(-36, false, 1750);
  turnPID(88);
  driveMedium(34, false, 2000);
  setIndexer(127, 127); delay(333); setIndexer(0, 0);
  driveMedium(-26, false, 1500);
  setIndexer(0, 0);
  turnPID(55);
  driveMedium(60, false, 100000);
  turnPID(-46);
  setDrive(80, 80); setIntakes(127, 127); delay(1500); setDrive(0, 0); setIndexer(127, 127); setIntakes(80, 80);
  delay(750); setIntakes(0, 0); setIndexer(0, 0);
  //setIndexer(127, 127); setIntakes(127, 127); delay(1000); setIndexer(0, 0); setIntakes(0, 0);
  //intakeOne();
}

void redHomeRow(){

}

void skills(){

}

void test(){
  turnPID(90);
  inertialBoi.reset();
  turnPID(-90);
}

void autonomous() {
  /*drivePID(850, true, 500);
	setIntakes(0, 0);
	turnPID(-30);
	drivePID(500, false, 200);
	setIntakes(0, 0); setIndexer(127, 127);
	delay(300);
	setIndexer(0, -80);
	delay(500);
	setIndexer(0, 0);
	drivePID(-1400, false, 600);
  turnPID(-70);*/
  //driveShort(12, false, 100000);
  //turnPID(90);
  //cycle();
  //turnPID(45);
  //lcd::print(1, "Rotation: %f", inertialBoi.get_rotation());
  //driveMedium(36, false, 19000);
  //turnPID(45
  //test();
  //blueHomeRow();
  setIntakes(127, 127); delay(300); setIntakes(0, 0);
  driveShort(12, true, 10000);
  setIntakes(0, 0);
  setDrive(100, 20); delay(400); setDrive(0, 0);
  cycle();
  driveMedium(-36, false, 1750);
  turnPID(88);
  driveMedium(34, false, 2000);
  setIndexer(127, 127); delay(333); setIndexer(0, 0);
  driveMedium(-26, false, 1500);
  setIndexer(0, 0);
  turnPID(55);
  driveMedium(60, false, 100000);
  turnPID(-46);
  setDrive(80, 80); setIntakes(127, 127); delay(1500); setDrive(0, 0); setIndexer(127, 127); setIntakes(80, 80);
  //setDrive(-80, -80); delay(200); setDrive(0, 0);
  delay(750); setIntakes(0, 0); setIndexer(0, 0);
}
