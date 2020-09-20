#include "main.h"

//DRIVE MOTORS
extern Motor leftFront;
extern Motor rightFront;
extern Motor leftBack;
extern Motor rightBack;

//CONTROLLER OP
extern Controller master;

//MISCELLANEUOUS (MOTORS)
extern Motor intakeLeft;
extern Motor intakeRight;
extern Motor indexerBottom;
extern Motor indexerTop;

//DRIVE SENSORS
extern ADIEncoder encoderLeft;
extern ADIEncoder encoderRight;
extern Imu inertialBoi;

//MISCELLANEUOUS (SENSORS)
extern ADILineSensor lineSensorBottom;
extern ADILineSensor lineSensorMiddle;
extern ADILineSensor lineSensorTop;
extern ADIButton limitSwitch;
