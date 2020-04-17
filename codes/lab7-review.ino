#define button_pin 4
#define bulb_pin 7

void setup()
{
  //SREG |= B10000000;
  cli(); //DISABLE GLOBAL INTERRUPTS
 
  Serial.begin(9600);
  //pinMode(bulb_pin,OUTPUT);
  //DDRD = (1<<PD7);
  DDRD =0b10000000; //BULB AS OUTPUT
  
  //pinMode(button_pin,INPUT);
  DDRD &= ~(1<<button_pin);  //BUTTON AS INPUT
  
  //attachInterrupt(0,someFunction,CHANGE);
  EICRA |= (1<<ISC00); //ANY CHANGE
  EIMSK |= (1<<INT0); //ENABLE INT0 
  
  ADCSRA |=(1<<ADEN); //ENABLE ADC DEVICE
  ADCSRA |=(1<<ADIE); //ENABLE ADC INTERRUPTS
  //ADMUX |= (1<<REFS0)|(1<<MUX1)|(1<<MUX0); 
  ADMUX = 0b01000011; //ENABLE "VCC" REF, CHOOSE "A3" PIN
  ADCSRA |=(1<<ADSC); //START CONVERSION
  
  TCCR1A = 0; //CLEAR REGISTERS
  TCCR1B = 0;
  TCCR1C = 0;
  TCNT1  = 0;
  
  OCR1A = 62499; //SysClk/(wantedHertz*PS)-1 (<65535)
                 //(16000000/(1*256))-1 (1024 PS also works)
  TCCR1B |= (1<<WGM12); //"CTC" MODE
  TCCR1B |= (1<<CS12); //256 PRESCALER
  TIMSK1 |= (1<<OCIE1A); //ENABLE "OCIE1A" INTERRUPTS

  //SREG &= B01111111;
  sei(); //ENABLE GLOBAL INTERRUPTS
  
}

int buttonState;
int bulbState;

void loop()
{
  //buttonState = digitalRead(button_pin);
  buttonState = (PIND&(1<<PD4))>>PD4;
               /* PIND =B10110101;
                       =B00010000;
                &_______________
                       =B00010000;>>PD4 => =B00000001; */
  if(buttonState){
     Serial.println("pressed"); 
     bulbState=!bulbState; //TOGGLE BULB VOLTAGE
     //digitalWrite(bulb_pin,bulbState);
     PORTD = (bulbState<<bulb_pin);
     delay(300);
  }  
}

ISR(INT0_vect){
  Serial.println("Switch flicked!");
}

ISR(ADC_vect){
 //Serial.println(ADCW); //you can uncomment this
 ADCSRA |= (1<<ADSC);
}

ISR(TIMER1_COMPA_vect){
 Serial.println("Timer ticked!");   
}