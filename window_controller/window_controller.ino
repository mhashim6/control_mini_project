#include <Servo.h>

#define KP 1.75

Servo servo;
void setup() {
  Serial.begin(1200);
  servo.attach(6);
}

float error ;
float angle;
void loop() {
  error = analogRead(A0);
  angle = error * KP + 90;
  Serial.print("LM35: ");
  Serial.println(analogRead(A5) * 0.48828125);
  Serial.print("error: ");
  Serial.println(error);
  Serial.print("angle: ");
  Serial.println(angle);
  if (angle > 180)
    servo.write(180);
  else
    servo.write(angle);
}
