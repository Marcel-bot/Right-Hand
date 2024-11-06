#include <main.h>

Servo inner_shoulder;
Servo outer_shoulder;
Servo under_shoulder;
Servo elbow;

void smoothMove(Servo &servo, const int startAngle, const int endAngle) {
  if (startAngle < endAngle) {
    for (int pos = startAngle; pos <= endAngle; pos += STEP_SIZE) {
      servo.write(pos);
      delay(SMOOTHING_DELAY);
    }
  } else {
    for (int pos = startAngle; pos >= endAngle; pos -= STEP_SIZE) {
      servo.write(pos);
      delay(SMOOTHING_DELAY);
    }
  }
}

void setup() {
  Serial.begin(BAUDRATE);

  inner_shoulder.attach(INNER_SHOULDER_PIN);
  outer_shoulder.attach(OUTER_SHOULDER_PIN);
  under_shoulder.attach(UNDER_SHOULDER_PIN);
  elbow.attach(ELBOW_PIN);

  inner_shoulder.write(10);
  outer_shoulder.write(20);
  under_shoulder.write(90);
  elbow.write(80);
}

void loop() {
  under_shoulder.write(10);
  delay(2000);
  under_shoulder.write(90);
  delay(2000);
}