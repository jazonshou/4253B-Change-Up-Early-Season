#include "main.h"

//DRIVE MOTORS
Motor leftFront(9, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor rightFront(3, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);
Motor leftBack(8, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor rightBack(2, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

//CONTROLLER OP
Controller master(E_CONTROLLER_MASTER);

//MISCELLANEUOUS (MOTORS)
Motor intakeLeft(18, MOTOR_GEARSET_06, true, MOTOR_ENCODER_COUNTS);
Motor intakeRight(20, MOTOR_GEARSET_06, false, MOTOR_ENCODER_COUNTS);
Motor indexerBottom(17, MOTOR_GEARSET_06, false, MOTOR_ENCODER_COUNTS);
Motor indexerTop(19, MOTOR_GEARSET_06, false, MOTOR_ENCODER_COUNTS);

//DRIVE SENSORS
ADIEncoder encoderLeft('C', 'D', false);
//ADIEncoder encoderRight('G', 'H', false);
Imu inertialBoi(1);

//MISCELLANEUOUS (SENSORS)
ADILineSensor lineSensorBottom('F');
ADILineSensor lineSensorMiddle('B');
ADILineSensor lineSensorTop('G');
ADIButton topLimitSwitch('A');
ADIButton limitSwitch('E');
