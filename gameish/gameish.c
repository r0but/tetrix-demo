// This is RobotC code. Despite the extension, trying to compile with a C compiler
// will throw errors.

// The main task is at the bottom. Most of the motor controlling stuff is in functions.

// I HAVEN'T TESTED THIS CODE YET. It's probably broken and will remain so until I
// get a chance to test it on a Tetrix bot and fix whatever errors pop up.

/****************************************************
*                                                   *
*    IMPORTANT: IN ROBOT CONFIG, NAME THE MOTORS    *
*       leftMotor AND rightMotor ACCORDINGLY        *
*                                                   *
****************************************************/

#include "JoystickDriver.h"

const int lowDeadzone = -5;
const int highDeadzone = 5;
const int maxSpeed = 100;
const int maxReverseSpeed = -100;
int speed;

void initializeRobot(){
  // Motors are not reversed. If your motors are running backwards, just flip
  // the corresponding motor to true.
  bMotorReflected[rightMotor] = false;
  bMotorReflected[leftMotor] = false;
}

void turnLeft(int magnitude){
  // To satisfy my OCD and make things even.
  // Maximum value that the stick returns is 127 while min is -128
  if (magnitude == -128) { magnitude = -127 ; }
  
  // normalizes magnitude to a 1-100 value, then makes it so a higher value 
  // makes the motor run slower
  if (speed > 0){
    magnitude = maxSpeed - (magnitude * (speed / 127));
  }
  else{
    magnitude = maxReverseSpeed - (magnitude * (speed / 127));
  }
  
  motor[rightMotor] = speed;
  motor[leftMotor] = magnitude;
}

void turnRight(int magnitude){
  // does the same thing as the similar statement in turnLeft
  if (speed > 0){
    magnitude = maxSpeed - (magnitude * (speed / 127));
  }
  else{
    magnitude = maxReverseSpeed - (magnitude * (speed / 127));
  }
  
  motor[rightMotor] = magnitude;
  motor[leftMotor] = speed;
}

void goStraight(){
  motor[rightMotor] = speed;
  motor[leftMotor] = speed;
}

void spinLeft(){
  motor[rightMotor] = maxSpeed;
  motor[leftMotor] = maxReverseSpeed;
}

void spinRight(){
  motor[rightMotor] = maxReverseSpeed;
  motor[leftMotor] = maxSpeed;
}

void setSpeedFromJoystick(int magnitude){
  if (magnitude == -128) { magnitude = 127; }
  
  speed = magnitude * (maxSpeed / 127);
}

void stopRobot(){
  motor[rightMotor] = 0;
  motor[leftMotor] = 0;
}

task main(){
  initializeRobot();
  waitForStart();

  int leftStick = 0;
  int rightStick = 0;
  
  while(1){
    wait1Msec(20);
  	
    // Spins the robot in a circle (L2 spins counter-clockwise, R2 spins clockwise)
    if (joy1Btn(7)){
      spinLeft();
      continue;
    }
    else if (joy1Btn(8)){
      spinRight();
      continue;
    }
  	
    // left stick left/right, right stick up/down
    leftStick = joystick.joy1_x1;
    rightStick = joystick.joy1_y2;	
  
    // This group of if statements sets the speed
    if (rightStick < lowDeadzone && rightStick > highDeadzone){
      setSpeedFromJoystick(rightStick);
    }
    else if (joy1Btn(6)){
      speed = maxSpeed;
    }
    else if (joy1Btn(5){
      speed = maxReverseSpeed;
    }
    else{
      stopRobot;
      continue;
    }
  	
    // This group determines turning
    if (leftStick < lowDeadzone){
      turnLeft(leftStick);
    }
    else if (leftStick > highDeadzone){
      turnRight(leftStick);
    }
    else{
	  goStraight();
    }
  }
}
