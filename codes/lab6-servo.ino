#include <Servo.h>

Servo servo1; 
Servo servo2;


int analogVal; // 0-1023 potentiometer value
int degreeVal; // 0-180 degree for servo

void setup()
{
 Serial.begin(9600);
  
 servo1.attach(9);
 servo2.attach(3);
  
}

void loop()
{
  analogVal = analogRead(0);
  degreeVal = map(analogVal, 0, 1023, 0, 180);
  
  servo1.write(degreeVal);
  servo2.write(180-degreeVal);
  
  Serial.println(servo1.read());
  
  delay(15);
  
}