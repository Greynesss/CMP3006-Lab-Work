//1: output , 0: input
//Digital pin 12 = PB4
//Digital pin 13 = PB5

void setup()
{
 //pinMode(13,OUTPUT); //1: output , 0: input
  DDRB = B00100000;
  Serial.begin(9600);
}
void digitalToggle (byte pin) {
 digitalWrite(pin,!digitalRead(pin)); 
}

int buttonState = LOW;
void loop()
{
  //buttonState = digitalRead(12);
  buttonState = (PINB & (1<<PB4))>>PB4;
  Serial.println(buttonState);
  if(buttonState==HIGH){
   digitalToggle(13); 
    delay(500);
  }
}
