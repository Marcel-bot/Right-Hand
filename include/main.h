#ifndef MAIN
#define MAIN

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>

#define BAUDRATE 115200

#define I2C_ADDRESS 0x08

#define INNER_SHOULDER_PIN 11
#define OUTER_SHOULDER_PIN 10
#define UNDER_SHOULDER_PIN 9
#define ELBOW_PIN 6
#define CLAW_JOINT_PIN 5
#define CLAW_PIN 3

#define HEAD_X A0
#define HEAD_Y A1

#define STEP_SIZE 3
#define SMOOTHING_DELAY 12

#define MOTION_METADATA 1
#define MOTION_DATA 2

#endif
