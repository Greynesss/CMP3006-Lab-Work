const int ledR=7;
const int ledY=6;
const int ledG=5;
const int radar=2;

int flag=0;

void setup()
{
  DDRD &= ~(1<<radar);
  PORTD |= (1<<radar);
  DDRD |= (1<<ledR);
  DDRD |= (1<<ledY);
  DDRD |= (1<<ledG);
  
  attachInterrupt(0,function,CHANGE);
  //attachInterrupt(digitalPinToInterrupt(2),function,CHANGE);
}

void loop()
{
  if(flag){
   PORTD ^= (1<<ledR); 
   PORTD ^= (1<<ledY);
   PORTD ^= (1<<ledG);
   flag=false;
    
  }
}

void function(){
  flag= true;
  //flag = ~flag; 
  
}
