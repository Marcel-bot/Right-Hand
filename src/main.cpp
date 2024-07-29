#include <main.h>

Servo inner_shoulder;
Servo outer_shoulder;
Servo under_shoulder;
Servo elbow;

void return_position() {
  smoothMove(inner_shoulder, inner_shoulder.read(), 10);
  smoothMove(outer_shoulder, outer_shoulder.read(), 20);
  smoothMove(under_shoulder, under_shoulder.read(), 90);
  smoothMove(elbow, elbow.read(), 80);
}

void smoothMove(Servo &servo, int startAngle, int endAngle) {
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

void hand_shake() {
  smoothMove(inner_shoulder, inner_shoulder.read(), 50);
  smoothMove(elbow, elbow.read(), 140);
  delay(3000);
  return_position();
}

void salute() {
  smoothMove(under_shoulder, under_shoulder.read(), 180);
  smoothMove(outer_shoulder, outer_shoulder.read(), 110);
  delay(50);
  for (int i = 0; i < 3 * 2; i++) {
    if (i % 2 == 0)
      smoothMove(elbow, elbow.read(), 0);
    else
      smoothMove(elbow, elbow.read(), 80);
    delay(300);
  }
  delay(300);
  return_position();
}

void hand_shake() {
  smoothMove(inner_shoulder, inner_shoulder.read(), 50);
  smoothMove(elbow, elbow.read(), 140);
  delay(3000);
  return_position();
}

void flex() {
  smoothMove(outer_shoulder, outer_shoulder.read(), 110);
  smoothMove(under_shoulder, under_shoulder.read(), 180);
  delay(50);
  smoothMove(elbow, elbow.read(), 110);
  delay(5000);
  return_position();
}

void onReceive(int size) {
  switch (Wire.read()) {
    case '1':
      hand_shake();
      break;

    case '2':
      salute();
      break;

    case '3':
      flex();
      break;

    case '4':
      return_position();
      break;
  }
}

void setup() {
  Serial.begin(BAUDRATE);
  Wire.begin(I2C_ADDRESS);

  inner_shoulder.attach(INNER_SHOULDER_PIN);
  outer_shoulder.attach(OUTER_SHOULDER_PIN);
  under_shoulder.attach(UNDER_SHOULDER_PIN);
  elbow.attach(ELBOW_PIN);

  inner_shoulder.write(10);
  outer_shoulder.write(20);
  under_shoulder.write(90);
  elbow.write(80);

  Wire.onReceive(onReceive);
}

void loop() {}