#include "main.h"

//HELPER FUNCTIONS
void setDrive (int left, int right);

void setLeft(int left);

void setRight(int right);

void resetEncoders();

double averageMotorVoltage();

int convertToTick(double inch);

//DRIVER CONTROL FUNCTIONS
void setDriveMotors();

//AUTON FUNCTIONS
void leftSlew(int leftTarget);

void rightSlew(int rightTarget);

void driveShort(double inch, bool autoIntake, int time);

void driveMedium(double inch, bool autoIntake, int time);

void turnPID(int degrees);
