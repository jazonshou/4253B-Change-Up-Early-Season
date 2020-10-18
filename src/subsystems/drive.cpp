#include "main.h"

//HELPER FUNCTIONS
void setDrive(int left, int right) { //Function: sets voltage value to left and right side
  leftFront = left;
  leftBack = left;
  rightFront = right;
  rightBack = right;
}

void resetEncoders() { //resets both tracking wheels
  encoderLeft.reset();
  encoderRight.reset();
}

double averageEncoderValue() { //gets both tracking wheel values and returns the average
  return (abs(encoderLeft.get_value()) +
          abs(encoderRight.get_value())) / 2;
}

//AUTON FUNCTIONS
int slewControl(int requestedSpeed){
  int currentSpeed = 0;
  int rate = 10; //acceleration rate
  if(abs(currentSpeed) < abs(requestedSpeed)){ //if it's accelerating, then...
    if(requestedSpeed > currentSpeed){ //if it's going forward... increased voltage
      currentSpeed += rate;
    }
    if(requestedSpeed < currentSpeed){ //if it's going backwards... decrease volatge
      currentSpeed -= rate;
    }
    return currentSpeed;
  }
  return requestedSpeed; //if it's not accelerating,
                         //then return original speed (because PID for deceleration)
}

void drivePIDD(int setPoint) {
  double kP = 0.23, kI = 0.0, kD = 0.2; //constants (for tuning)

  int prevError = 0; //for derivative

  int direction = abs(setPoint) / setPoint; //Forward = 1, backwards = -1
  resetEncoders(); //resets encoders

  while(1) {
    //P: error = how far we need to go (setpoint) - the actual encoder value
    //this is the core of the PID controller
    //as the chassis gets closer, the error becomes smaller making the chassis speed slower
    int driveError = setPoint - (direction * encoderRight.get_value());

    //Integral is used to prevent stedy state error (SSE)
    //SSE is when the P & D decelerate the chassis so much, it doesn't actually reach the target
    //Inegral finds if the chassis is decelerating too much and increases the voltage...
    //Allowing the chassis to be able to reach the setPoint
    int integral = integral + driveError;

    //Once the encoder value is over the desired value, this sets the integral to 0
    //which prevents oscillations
    if(abs(encoderRight.get_value()) > abs(setPoint)){
      integral = 0;
    }

    //TBH idk about derivate - basically just makes the deceleration smoother
    int derivative = driveError - prevError;
    prevError = driveError;

    //this puts everything together into one variable which then sets the voltage of the chassis
    double power = driveError * kP + integral * kI + derivative * kD;

    setDrive(power * direction, power * direction); //* direction
    delay(15);
  }
  setDrive(0, 0); //idk if we need tbh
}

void turnPID(int degrees, int direction) { //same thing as above... except turning
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
