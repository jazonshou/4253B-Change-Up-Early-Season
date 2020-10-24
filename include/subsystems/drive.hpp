#include "main.h"

//HELPER FUNCTIONS
void setDrive (int left, int right);

void resetEncoders();

double averageEncoderValue();

double averageMotorVoltage();

//DRIVER CONTROL FUNCTIONS
void setDriveMotors();

//AUTON FUNCTIONS
void drivePID(int setPoint, bool autoIntake, int time);

void turnPID(int degrees);

void simpleTurn(int degrees);

void drivePID(int setPoint);

void motionProfileDrive(int setPoint);

void odom_print();
