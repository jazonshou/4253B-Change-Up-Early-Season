#include "main.h"

//HELPER FUNCTIONS
void setDrive (int left, int right);

void resetEncoders();

double averageEncoderValue();

//DRIVER CONTROL FUNCTIONS
void setDriveMotors();

//AUTON FUNCTIONS
void drivePID(int setPoint);

void turnPID(int degrees, int direction);

void simpleTurn(int degrees);

void drivePIDD(int setPoint);

void motionProfileDrive(int setPoint);

void odom_print();
