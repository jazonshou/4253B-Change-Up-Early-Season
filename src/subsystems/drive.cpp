#include "main.h"

//HELPER FUNCTIONS
void setDrive(int left, int right) {
  leftFront = left;
  leftBack = left;
  rightFront = right;
  rightBack = right;
}

void resetEncoders() {
  encoderLeft.reset();
  encoderRight.reset();
}

double averageEncoderValue() {
  return (abs(encoderLeft.get_value()) +
          abs(encoderRight.get_value())) / 2;
}

//AUTON FUNCTIONS
void drivePIDD(int setPoint) {
  double kP = 0.23; //Proportional tuning
  double kI = 0.0;
  double kD = 0.2;

  int prevError = 0;

  int direction = abs(setPoint) / setPoint; //Forward = 1, backwards = -1
  resetEncoders(); //resets encoders

  while(1) { //while both encoders are less than setpoint...
    int driveError = setPoint - (direction * encoderRight.get_value());

    int integral = integral + driveError;
    if(abs(encoderRight.get_value()) > abs(setPoint)){
      integral = 0;
    }

    int derivative = driveError - prevError;
    prevError = driveError;

    double power = driveError * kP + integral * kI + derivative * kD;

    setDrive(power * direction, power * direction); //* direction
    delay(15);
  }
  setDrive(0, 0);
}

void turnPID(int degrees, int direction) { //might not be able to reset gyro cuz it takes up 2 seconds
  double turnkP = 0.01;
  double turnkD = 0.0;

  int prevTurnError = 0;

  double turnDifference = degrees - inertialBoi.get_heading();

  while(inertialBoi.get_heading() < degrees && direction == true) { //either get_rotation or get_heading
    int turnError = degrees - inertialBoi.get_heading(); //either get_rotation or get_heading

    int turnDerivative = turnError - prevTurnError;
    prevTurnError = turnError;

    double turnPower = turnError * turnkP + turnDerivative * turnkD;

    setDrive(turnPower * direction, -turnPower * direction);
    delay(15);
  }
  setDrive(0,0);
}

void simpleTurn(int degrees){
  while(inertialBoi.get_heading() < degrees){
    setDrive(-50, 50);
  }
}

/*void motionProfileDrive(int setPoint){ //Accelerate, constant, decelerate (PID)
  int startChunk = setPoint * (1/4); //Start; 1/4 of setPoint
  int middleChunk = setPoint * (1/2); //After startChunk; 1/4 of setPoint
  int endChunk = setPoint; //After middleChunk; 1/2 of setPoint

  int direction = abs(setPoint)/setPoint; //Finds direction
  resetEncoders();

  int prevError = 0; //For derivative

  double kP = 0.18; //Proportional tuning
  double kD = 0.7; //Derivative tuning
  double changeInSpeed = 5; //Acce/ faster || slower
  double accelVel; //Voltage after accel
  double power;

  while(abs(encoderRight.get_value()) < startChunk){ //While less than startChunk
    power += changeInSpeed; //maybe change to *= for faster acceleration
    power = accelVel; //new voltage after accel

    setDrive(power * direction, power * direction); //sets power and direction to drive
    delay(10);
  }
  while(abs(encoderRight.get_value()) > startChunk && abs(encoderRight.get_value()) < middleChunk){
    setDrive(accelVel * direction, accelVel * direction); //drive = new voltage after accel; max = 127, mostly likly less
    delay(10);
  }
  while(abs(encoderRight.get_value()) > middleChunk && abs(encoderRight.get_value()) < endChunk){ //PD loop; final 1 half; deceleration
    int driveError = abs(setPoint) - abs(encoderRight.get_value());

    int derivative = driveError - prevError;
    prevError = driveError;

    double power = driveError * kP + derivative * kD;

    setDrive(power * direction, power * direction); //* direction
    delay(10);
  }
  setDrive(0, 0);
}*/
