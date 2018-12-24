
float analogSignal;

#define SET_POINT 65

#define kp 40.0
#define ki 0.0

#define kd 1.0

unsigned long lastTime;
double feedback, c_out;
double errSum, lastErr, errorCounter;

#define READINGS  30

float readings[READINGS];      // the readings from the analog input
int  readIndex = 0;              // the index of the current reading
float  total = 0;                  // the running total
float  average = 0;                // the average

void setup() {
  Serial.begin(1200);
  pinMode(6, OUTPUT);
  for (int thisReading = 0; thisReading < READINGS; thisReading++) {
    readings[thisReading] = 0;

  }
  //  consumeNoise();
}

void loop() {
  //  fan();
  //  pid();
  //  delay(1000);
  oscilliscope();
  //  analogWrite(A0, 0);
  //  analogSignal = (analogRead(A5)/1024.0f) * 12.0f ;
}

void pid()
{
  feedback = filter(analogRead(A5));
  Serial.println(feedback * 0.48828125);
  //  Serial.print(" ");
  /*How long since we last calculated*/
  unsigned long now = millis();
  double timeChange = (double)(now - lastTime);

  /*pid all the working error variables*/
  double error = SET_POINT - feedback;

  /*if (errorCounter > 500.0) {
    errSum = 0;
    errorCounter = 0;
    } else errorCounter++;
  */
  errSum += (error * timeChange);
  double dErr = (error - lastErr) / timeChange;
  /*pid PID c_out*/
  double rawOutput  = (kp * error + ki * errSum + kd * dErr) ;
  if (rawOutput < 0)
    c_out = 0;
  else if (rawOutput > 255)
    c_out = 255;
  else c_out = rawOutput;
  Serial.print("feedback ");
  Serial.println(feedback);
  Serial.print("err ");
  Serial.println(error);
  Serial.print("c_out ");
  Serial.println(c_out);
  Serial.println("------------");
  /*Remember some variables for next time*/
  lastErr = error;
  lastTime = now;
}

void fan() {
  analogWrite(9, c_out);
}

void oscilliscope() {
  //  analogSignal = filter((analogRead(A5) * 0.48828125)) ;
  analogSignal = analogRead(A5) * 0.48828125;
  Serial.println(analogSignal);
  Serial.print(" ");
}

// filter goes here:

void consumeNoise() {
  for (int i = 0; i < 20000; i++)
    filter((analogRead(A5) * 0.48828125));
}

float filter(float analog) {
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analog;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= READINGS) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / READINGS;
  delay(1);        // delay in between reads for stability
  return average;
}
