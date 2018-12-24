void setup() {
  Serial.begin(1200);
}

void loop() {
  Serial.println(analogRead(A5) * 0.09765625);
  Serial.print(" ");
}
