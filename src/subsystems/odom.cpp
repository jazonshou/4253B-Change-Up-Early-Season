#include "main.h"
//SETTINGS
//This is something you should utilize to convert the horizontal encoder distance to match the vertical encoder distance
//Grab a ruler, and push the robot 20 inches straight forward, then record the average vertical value (Example: 51269)
//Reset, Grab a ruler, and push the robot 20 inches to the right, then record the horizontal encoder value (Example: 10532)
//You will need to convert it such that the horizontal matches for the same distance, so the multiplier will be horizontal(10532)/vertical(51269)
//And that number will be the ratio (10532/51269 = 0.2054262809885116)
double verticalToHorizontalRatio = 1.0000000;

//Because we can average the vertical encoders while turning, it will not show a change
//But for the horizontal encoders, it will assume the robot is laterally strafing, which is not correct
//We fix this by applying a multiplier compensation such that we will negate it using the inertial sensor
//Reset your robot, make sure everything is calibrated
//Rotate your robot such that the inertial sensor reads 3600 degrees (i.e. rotate the robot 10 times for the sake of accuracy)
//Your horizontal encoder should have a value (Example: 231809)
//Divide that result by 3600 (231809/3600 = 64.3913888), and that number will be the value used
double rotateNegateHorizontalRatio = 50.000000;

//This is utilized to convert the ticks moved to actual inches
//Push the robot 20 inches forward (without turning it or pushing it strafe-wise)
//Get the average reading of the vertical encoders (Example: 253053)
//Divide the reading by 20 (253053/20 = 12,652.65), and put the multipler in this area
//This will convert it to inches
double posTranslationMultiplier = 1;

//FUNCTIONS
// This converts degrees to radians
double getRadians(int degrees){
  return ( degrees * M_PI ) / 180 ;
}

//VARIABLES
// Include additional mathematical operations
double lastVerticalPosLocal = 0.0;
double lastHorizontalPosLocal = 0.0;
double XPos = 0.0;
double YPos = 0.0;

void odom_print(){
  //GETS VALUE OF SENSORS
  //Gets position of sensors (local position)
  int leftVal = encoderLeft.get_value();
  int rightVal = encoderRight.get_value();
  int backVal = encoderBack.get_value();
  //Gets rotation of inertial
  double rotation = inertialBoi.get_rotation();

  //LOCAL POSITION
  double VerticalPosLocal = (leftVal + rightVal) / 2.0;
  double HorizontalPosLocal = backVal + (rotation * rotateNegateHorizontalRatio);
  //Horizontal & veritcal ratio
  HorizontalPosLocal *= verticalToHorizontalRatio;
  //Calculate velocity/change in position per 20ms
  double YV = VerticalPosLocal - lastVerticalPosLocal;
  double XV = HorizontalPosLocal - lastHorizontalPosLocal;

  //WORLD-SPACE (whatever) position
  //Do some relatively-complex maths that converts local velocity to world-space velocity. The (m/milisecondStepTime) at the end is a multiplier
  //that would scale velocity more appropriately due to computer yields (Line 131 explains) If computer is told to wait 2 second and waits 0.75 instead,
  //the multiplier would then scale the velocity to be 0.375 its value (0.75/2 = 0.375)
  double XVelocityWorldSpace = (XV * std::cos(getRadians(-rotation)) - YV * std::sin(getRadians(-rotation)));
	double YVelocityWorldSpace = (XV * std::sin(getRadians(rotation)) - YV * std::cos(getRadians(rotation)));
  //This would give us the X and Y position in world space
  XPos += XVelocityWorldSpace * posTranslationMultiplier;
  YPos += YVelocityWorldSpace * posTranslationMultiplier;
  //This is applied to be utilized 20 miliseconds after
  lastVerticalPosLocal = VerticalPosLocal;
  lastHorizontalPosLocal = HorizontalPosLocal;

  //Print XPos & YPos on brain screen
  lcd::print(0, "X Position: %d", XPos);
  lcd::print(1, "Y Position: %d", YPos);
  lcd::print(2, "Rotation: %d", rotation);
}
