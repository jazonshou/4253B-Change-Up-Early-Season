#include "main.h"

//DRIVE MOTORS
Motor leftFront(3, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);
Motor rightFront(9, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor leftBack(2, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);
Motor rightBack(10, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);

//CONTROLLER OP
Controller master(E_CONTROLLER_MASTER);

//MISCELLANEUOUS (MOTORS)
Motor intakeLeft(18, MOTOR_GEARSET_06, false, MOTOR_ENCODER_COUNTS);
Motor intakeRight(20, MOTOR_GEARSET_06, true, MOTOR_ENCODER_COUNTS);
Motor indexerBottom(17, MOTOR_GEARSET_06, false, MOTOR_ENCODER_COUNTS);
Motor indexerTop(19, MOTOR_GEARSET_06, false, MOTOR_ENCODER_COUNTS);

//DRIVE SENSORS
ADIEncoder encoderLeft('C', 'D', true);
ADIEncoder encoderRight('G', 'H');
Imu inertialBoi(1);

//MISCELLANEUOUS (SENSORS)
ADILineSensor lineSensorBottom('C');
ADILineSensor lineSensorMiddle('D');
ADILineSensor lineSensorTop('G');
ADIButton limitSwitch('E');
