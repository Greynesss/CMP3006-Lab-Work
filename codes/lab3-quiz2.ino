void setup()
{
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(2,INPUT);
  attachInterrupt(0,shiftDirection,RISING);
}

bool forward = false;

void loop()
{
  
}

void shiftDirection(){
  
  if(forward){
 digitalWrite(10,HIGH);
 digitalWrite(11,LOW);
    forward=false;
  }
  else{
    digitalWrite(11,HIGH);
    digitalWrite(10,LOW);
    forward=true;
  }
  
}
