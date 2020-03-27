//This code uses all 3 timers to 3 blink LEDs
//At first,
//timer0 will interrupt at 2kHz
//timer1 will interrupt at 1Hz
//timer2 will interrupt at 8kHz
//Then,
//they will all align at 1 Hz

//LED toggles
boolean toggle0 = 1;
boolean toggle1 = 1;
boolean toggle2 = 1;

//hertz counters for T0 and T2
int counter0=0;
int counter2=0;

void setup(){
  
  //set pins as outputs
  DDRB=0b00100011;
  /* REMINDER! alternatives are:
  
  DDRB=(1<<PB0)|(1<<PB1)|(1<<PB5);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT); */

  cli();//disable global interrupts

  //T0
  TCCR0A = 0; // clear registers and timer value
  TCCR0B = 0;
  TCNT0  = 0;
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256) 
  TCCR0A |= (1 << WGM01); //CTC
  TCCR0B |= (1 << CS01) | (1 << CS00); //prescaler 64
  TIMSK0 |= (1 << OCIE0A); //enable interrupt

  //T2
  TCCR2A = 0;  // clear registers and timer value
  TCCR2B = 0;
  TCNT2  = 0;
  OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  TCCR2A |= (1 << WGM21);  //CTC mode
  TCCR2B |= (1 << CS21);   //prescaler 8
  TIMSK2 |= (1 << OCIE2A); //enable interrupt

  //T1
  TCCR1A = 0; // clear registers and timer value
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  TCCR1B |= (1 << WGM12); //CTC
  TCCR1B |= (1 << CS12) | (1 << CS10);  //prescaler 1024
  TIMSK1 |= (1 << OCIE1A); //enable

  sei();//allow global interrupts

}

ISR(TIMER0_COMPA_vect){
  counter0++; //incremented each entrance
  if(counter0>2000){ //to scale 2000 entries to 1
  if (toggle0){
    digitalWrite(8,HIGH); //toggle LED
    toggle0 = 0;
  }
  else{
    digitalWrite(8,LOW);
    toggle0 = 1;
  }
    counter0=0; //counter cleared after each toggle
  }
}

ISR(TIMER1_COMPA_vect){
  if (toggle1){ 
    digitalWrite(13,HIGH); //toggle LED
    toggle1 = 0;
  }
  else{
    digitalWrite(13,LOW);
    toggle1 = 1;
  }
}
  
ISR(TIMER2_COMPA_vect){
  counter2++; //incremented each entrance
  if(counter2>8000){ //to scale 8000 entries to 1
    if (toggle2){
    digitalWrite(9,HIGH); //toggle LED
    toggle2 = 0;
  }
  else{
    digitalWrite(9,LOW);
    toggle2 = 1;
  }
    counter2=0; //counter cleared after each toggle
  }
}
void loop(){}