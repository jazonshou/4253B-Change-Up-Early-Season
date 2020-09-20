#include "main.h"

//DRIVE MOTORS
Motor leftFront(11, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);
Motor rightFront(12, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor leftBack(19, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);
Motor rightBack(20, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);

//CONTROLLER OP
Controller master(E_CONTROLLER_MASTER);

//MISCELLANEUOUS (MOTORS)
Motor intakeLeft(2, MOTOR_GEARSET_06, false, MOTOR_ENCODER_COUNTS);
Motor intakeRight(5, MOTOR_GEARSET_06, true, MOTOR_ENCODER_COUNTS);
Motor indexerBottom(14, MOTOR_GEARSET_06, false, MOTOR_ENCODER_COUNTS);
Motor indexerTop(15, MOTOR_GEARSET_06, false, MOTOR_ENCODER_COUNTS);

//DRIVE SENSORS
ADIEncoder encoderLeft('A', 'B', true);
ADIEncoder encoderRight('E', 'F');
Imu inertialBoi(9);

//MISCELLANEUOUS (SENSORS)
ADILineSensor lineSensorBottom('C');
ADILineSensor lineSensorMiddle('D');
ADILineSensor lineSensorTop('G');
ADIButton limitSwitch('H');
