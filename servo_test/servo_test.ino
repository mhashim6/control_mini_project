#include <Servo.h>

Servo servo;
void setup() {
  servo.attach(6);
  //  servo.write(180);
}

void loop() {
  for (int i = 90; i <= 180; i++) {
    servo.write(i);
    delay(10);
  }

  for (int i = 180; i >= 90; i--) {
    servo.write(i);
    delay(10);
  }
}
