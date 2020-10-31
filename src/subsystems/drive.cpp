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
  //encoderRight.reset();
}

double averageMotorVoltage(){
  return abs((leftBack.get_voltage() + leftFront.get_voltage() + rightBack.get_voltage() + rightFront.get_voltage()) / 4);
}

int convertToTick(double inch){
  return (int)(inch / 8.6394 * 360);
}

static int prevRotation = 0;

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

void driveShort(double inch, bool autoIntake, int time){
  lcd::print(3, "I was in PID SHort");
  int setpoint = convertToTick(inch);
  double kP = 0.205, kI = 0.00038, kD = 0.58; //kI = 0.00027
  int error = 0, prevError = 0, derivative = 0, integral = 0;
  double initRotation = inertialBoi.get_rotation(), swerveVal = 0;
  int cnt = 0;
  int direction = fabs(inch)/inch;

  //pros::lcd::clear();
  resetEncoders();
  while(1){
    cnt += 15;
    swerveVal = (inertialBoi.get_rotation()*1) - initRotation;
    error = setpoint - encoderLeft.get_value();
    derivative = error - prevError;
    integral += error;
    prevError = error;

    if(cnt >= time || abs(error) <= 7){
      lcd::print(4, "broken");
      delay(800);
      break;
    }

    if((error ^ setpoint) < 0 || abs(integral) >= 85000){
      integral = 0;
    }

    double power = error * kP + integral * kI + derivative * kD;

    leftSlew(power - swerveVal); rightSlew(power + swerveVal);
    //setDrive(power , power );
    //std::cout << "Error: " << error << " Integral: " << integral << '\n';
    pros::lcd::print(1, "Error: %d", error);
    pros::lcd::print(2, "Integral: %d", integral);
    if(autoIntake){
      autoIndex();
    }
    delay(15);
  }
  prevRotation = inertialBoi.get_rotation();
  setDrive(0, 0);
}

void driveMedium(double inch, bool autoIntake, int time){
  int setpoint = convertToTick(inch);
  double kP = 0.16, kI = 0.00034, kD = 0.90;
  int error = 0, prevError = 0, derivative = 0, integral = 0;
  double initRotation = inertialBoi.get_rotation(), swerveVal = 0;
  int cnt = 0;
  int direction = fabs(inch)/inch;

  //pros::lcd::clear();
  resetEncoders();
  while(1){
    cnt += 15;
    swerveVal = (inertialBoi.get_rotation()*1) - initRotation;
    error = setpoint - encoderLeft.get_value();
    derivative = error - prevError;
    integral += error;
    prevError = error;

    if(cnt >= time || abs(error) <= 7){
      delay(800);
      break;
    }

    if((error ^ setpoint) < 0 || abs(integral) >= 85000){
      integral = 0;
    }

    double power = error * kP + integral * kI + derivative * kD;

    leftSlew(power - swerveVal); rightSlew(power + swerveVal);
    //setDrive(power - swerveVal, power + swerveVal);
    //std::cout << "Error: " << error << " Integral: " << integral << '\n';
    pros::lcd::print(1, "Error: %d", error);
    pros::lcd::print(2, "Integral: %d", integral);
    if(autoIntake){
      autoIndex();
    }
    delay(15);
  }
  prevRotation = inertialBoi.get_rotation();
  setDrive(0, 0);
}

void turnPID(int degrees) { //might not be able to reset gyro cuz it takes up 2 seconds
  double turnkP = 3.0;
  double turnkI = 0.0009;
  double turnkD = 16.5;

  int turnIntegral = 0;
  int prevTurnError = 0;
  int direction = abs(degrees)/degrees;
  int initRotation = inertialBoi.get_rotation();
  //pros::lcd::clear();
  //double turnDifference = degrees - inertialBoi.get_rotation();

  while(1) { //either get_rotation or get_heading
    int turnError = degrees - (inertialBoi.get_rotation() - initRotation); //either get_rotation or get_heading

    int turnDerivative = turnError - prevTurnError;
    prevTurnError = turnError;

    double turnPower = turnError * turnkP + turnIntegral * turnkI + turnDerivative * turnkD;

    if(abs(turnError) < 3){
      break;
    }
    setDrive(turnPower, -turnPower);
    pros::lcd::print(3, "Turn Error: %d", turnError);
    pros::lcd::print(4, "Turn Integral: %d", turnIntegral);
    pros::lcd::print(5, "Rotation: %f", inertialBoi.get_heading());
    delay(15);
  }

  setDrive(0,0);
}
