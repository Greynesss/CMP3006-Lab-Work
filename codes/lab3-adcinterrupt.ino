void setup()
{
 DDRD = B11111111; //assigned LEDs as output

 ADCSRA |= (1<<ADEN); //enabled ADC
 ADCSRA |= (1<<ADIE); //enabled interrupts
 ADMUX = B01000011; //Chose voltage ref, and A3 as input
 ADCSRA |= (1<<ADSC); //started conversion
}

void loop()
{
}

ISR(ADC_vect){
  int index;
  index = ADCW/128; //indexed from 0-1023 to 0-7
  PORTD = (1<<index); //lighted up corresp. LED
  ADCSRA |= (1<<ADSC); //started back ADC   
}
