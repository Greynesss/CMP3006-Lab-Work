void setup()
{
 ADMUX = 1 << REFS0; // choose ref voltage (AVCC)
 ADCSRA = (1<<ADEN)|7; //Enable ADC, choose prescaler
 Serial.begin(9600);
}

int readAdc(char pin){
  
  ADMUX |= (pin & 0x0f); //select analog pin
  ADCSRA |= (1<<ADSC); //start conversion
  
  while(ADCSRA & (1<<ADSC)); //wait for conversion to finish
  
  return ADCW; //get resulting ADC value
  
}
int val;
void loop()
{
  //val = analogRead(A0); //default function
  val = readAdc(0); //our function
  analogWrite(11,val/4); //map from 0-1023 to 0-255
  Serial.println(val);
}
