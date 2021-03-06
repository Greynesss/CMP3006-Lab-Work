const int button_pin = 2;
const int led_pin = 5;

//volatile int flag = 0;

void setup()
{
  DDRD &= ~(1<<button_pin);  //assigned button as INPUT
  PORTD |= (1<<button_pin); //assigned button as PULLUP  
  DDRD |= (1<<led_pin); //assigned LED as OUTPUT
  
  EICRA |= (1<<ISC01); //enabled falling edge
  EICRA &= ~(1<<ISC00);
  
  EIMSK |= (1<<INT0); //enabled INT0 
  
  SREG |= 0b10000000; //sei();
  
}

void loop()
{
  //if(flag){
  
   //flag = 0;
  //}
}

ISR(INT0_vect){
 PORTD ^= (1<<led_pin); //toggle LED voltage
 //flag=1;
  
}
