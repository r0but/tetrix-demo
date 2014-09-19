// Copyright 2014 Josh Trahan. Licensed under the MIT License.
// For more information, visit github.com/r0but/tetrix-demo

/*
This is RobotC code. Despite the extension, trying to compile with a C 
compiler will give errors.

The main task is at the bottom. Most of the motor controlling stuff is
in functions. The main loop is in the function mainLoop().

I HAVEN'T TESTED THIS CODE YET. It's probably broken and will likely remain so 
until I get a chance to test it on a Tetrix bot and fix whatever errors pop up.

/****************************************************
*                                                   *
*    IMPORTANT: IN ROBOT CONFIG, NAME THE MOTORS    *
*       leftMotor AND rightMotor ACCORDINGLY        *
*                                                   *
****************************************************/

#include "JoystickDriver.h"

// Deadzones for the control sticks
const int lowDeadzone = -5;
const int highDeadzone = 5;

// Max speed that the motors can EVER spin for the duration of the program.
// The actual speed itself is NOT constant.
const int maxSpeed = 100;
const int maxReverseSpeed = -100;

// Current speed for the motors to spin (determined in the main loop)
int speed;

void initializeRobot(){
  // Motors are not reversed by default. If your motor(s) are running backwards, 
  // just change the corresponding motor to true OR tick "reversed" checkbox 
  // for it in motor and sensor setup.
  bMotorReflected[rightMotor] = false;
  bMotorReflected[leftMotor] = false;
}

void turnLeft(int magnitude){  
  // normalizes magnitude to a 1-100 value, then makes it so a higher value 
  // makes the motor run slower
  if (speed > 0){
    magnitude = maxSpeed - (magnitude * (speed / 128));
  }
  else{
    magnitude = maxReverseSpeed - (magnitude * (speed / 128));
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
  // Max negative value from the stick is -128, while max positive is 127.
  if (magnitude < 0){
    speed = magnitude * (maxSpeed / 128);
  }
  else{
    speed = magnitude * (maxSpeed / 127);
  }
}

void stopRobot(){
  motor[rightMotor] = 0;
  motor[leftMotor] = 0;
}

void mainLoop(){
  int leftStick = 0;
  int rightStick = 0;

  while(1){
    wait1Msec(20);
  	
    // Spins the robot in a circle (L2 spins counter-clockwise, R2 clockwise)
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

task main(){
  initializeRobot();
  waitForStart();
  mainLoop();
}
