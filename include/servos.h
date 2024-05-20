#include "Servo.h"

#ifndef PINS

#define PINS

#define INNER_SHOULDER_PIN 11
#define OUTER_SHOULDER_PIN 10
#define UNDER_SHOULDER_PIN 9
#define ELBOW_PIN 6

#define INNER_SHOULDER_DEFAULT 0
#define OUTER_SHOULDER_DEFAULT 20
#define UNDER_SHOULDER_DEFAULT 90
#define ELBOW_DEFAULT 0

#endif

Servo inner_shoulder;
Servo outer_shoulder;
Servo under_shoulder;
Servo elbow;

void init_servos();