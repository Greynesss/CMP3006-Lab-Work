//LCD Clock Example using Timer1

#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

void setup()
{
  cli(); //global interrupts disabled
 
  TCNT1= 0; //clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  
  TCCR1B |= (1<<WGM12); //CTC mode
  TCCR1B |= (1<<CS12)|(1<<CS10); //prescaler 1024
  OCR1A = 15624; //(SysClock)/(requestedHertz*prescaler)-1
                 //(16*10^6)/(1*1024)-1
  //TIMSK1 |= (1<<TOIE1); //enable overflow interrupt(65535)
  TIMSK1 |= (1<<OCIE1A); //enable custom OCR1A interrupt
  
  lcd.begin(16,2);
  
  lcd.print("BAU CLOCK");
  lcd.setCursor(0,1); //the next print call will write to
  					  //cursor location
  lcd.print("Good morning!");
  delay(3000);
  lcd.clear();
  
  sei();
}

 int hour=0;
 int min=0;
 int sec=0;

void loop()
{
 lcd.setCursor(0,0);
 lcd.print("H:    M:    S:");
 
 lcd.setCursor(1,1);
 if(hour==0) lcd.print("  ");
 else lcd.print(hour);
  
 lcd.setCursor(7,1);
 if(min==0) lcd.print("  ");
 else lcd.print(min);
  
 lcd.setCursor(13,1);
 if(sec==0) lcd.print("  ");
 else lcd.print(sec);
}
//ISR(TIMER1_OVF_vect){ // for overflow ISR (65535)
 ISR(TIMER1_COMPA_vect){
  sec++;
  if(sec>=60){
   min++;
   sec=0;   
  }
  if(min>=60){
   hour++;
   min=0;
  }
  if(hour>=24){
   hour=0; 
  }
}
