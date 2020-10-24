#include "main.h"

//HELPER FUNCTIONS
void setDrive(int left, int right) {
  leftFront = left;
  leftBack = left;
  rightFront = right;
  rightBack = right;
}

void setLeft(int left){
  leftFront = left;
  leftBack = left;
}

void setRight(int right){
  rightFront = right;
  rightBack = right;
}

void resetEncoders() {
  encoderLeft.reset();
  encoderRight.reset();
}

double averageMotorVoltage(){
  return abs((leftBack.get_voltage() + leftFront.get_voltage() + rightBack.get_voltage() + rightFront.get_voltage()) / 4);
}

double averageEncoderValue() {
  return (abs(encoderLeft.get_value()) +
          abs(encoderRight.get_value())) / 2;
}

//AUTON FUNCTIONS
const int accel_step = 9;
const int deccel_step = 256; // no decel slew
static int leftSpeed = 0;
static int rightSpeed = 0;

void leftSlew(int leftTarget){
  int step;

  if(abs(leftSpeed) < abs(leftTarget))
    step = accel_step;
  else
    step = deccel_step;

  if(leftTarget > leftSpeed + step)
    leftSpeed += step;
  else if(leftTarget < leftSpeed - step)
    leftSpeed -= step;
  else
    leftSpeed = leftTarget;

  setLeft(leftSpeed);
}

void rightSlew(int rightTarget){
  int step;

  if(abs(rightSpeed) < abs(rightTarget))
    step = accel_step;
  else
    step = deccel_step;

  if(rightTarget > rightSpeed + step)
    rightSpeed += step;
  else if(rightTarget < rightSpeed - step)
    rightSpeed -= step;
  else
    rightSpeed = rightTarget;

  setRight(rightSpeed);
}
/**************************************************/

void drivePID(int setPoint, bool autoIntake, int time) {
  double kP = 0.1275, kD = 0.35; //constants (for tuning)
  int error = 0, prevError = 0;
  int derivative = 0;
  double initialRotation = inertialBoi.get_rotation();
  double swerveVal = 0;
  int cnt = 0;
  pros::lcd::clear();


  resetEncoders(); //resets encoders

  while(1) {
    cnt += 15;
    if( cnt >= time){
      break;
    }
    swerveVal = MAX(inertialBoi.get_rotation() - initialRotation, 0);
    error = setPoint - encoderLeft.get_value();

    derivative = error - prevError;
    prevError = error;

    double power = error * kP + derivative * kD;
    if(abs(power) <= 127){
      leftSlew(power - swerveVal); rightSlew(power + swerveVal);
    }
    else{
      leftSlew(127); rightSlew(127);
    }


    pros::lcd::print(1, "Error: %d", error);
    pros::lcd::print(2, "Rotation: %d", inertialBoi.get_rotation());
    pros::lcd::print(3, "Swerve Value: %d", swerveVal);
    if(autoIntake == true){
      autoIndex();
    }
    delay(15);
  }
  setDrive(0, 0);
}

void turnPID(int degrees) { //might not be able to reset gyro cuz it takes up 2 seconds
  double turnkP = 3.25;
  double turnkD = 8.00;

  int prevTurnError = 0;
  int direction = abs(degrees)/degrees;
  int cnt = 0;

  pros::lcd::clear();
  //double turnDifference = degrees - inertialBoi.get_rotation();

  while(1) { //either get_rotation or get_heading
    cnt++;
    int turnError = abs(degrees) - abs(inertialBoi.get_rotation()); //either get_rotation or get_heading

    int turnDerivative = turnError - prevTurnError;
    prevTurnError = turnError;

    double turnPower = turnError * turnkP + turnDerivative * turnkD;

    if(turnError <= 5 && cnt >= 20){
      break;
    }
    setDrive(turnPower * direction, -turnPower * direction);
    pros::lcd::print(5, "Turn Error: %d", turnError);
    delay(15);
  }
  setDrive(0,0);
}

void simpleTurn(int degrees){
  inertialBoi.reset();
  while(inertialBoi.get_heading() < degrees){
    setDrive(50, -50);
  }
  setDrive(0, 0);
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
