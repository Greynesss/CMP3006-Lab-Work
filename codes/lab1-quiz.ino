void setup()
{
  DDRD=B11110000;
}

void loop()
{
  PORTD=B10000000;
  delay(500);
  PORTD=B11000000;
  delay(500);
  PORTD=B11100000;
  delay(500);
  PORTD=B11110000; 
  delay(500);
  PORTD=B11100000;
  delay(500);
  PORTD=B11000000;
  delay(500);
  PORTD=B10000000;
  delay(500);
  PORTD=B00000000;
  delay(500);
}
