#define leg1 5
#define leg2 6
#define button 2


void setup()
{
 Serial.begin(9600);
  
 pinMode(leg1,OUTPUT);
 pinMode(leg2,OUTPUT);
  
}

void loop()
{
  
  if(digitalRead(button)){
  Serial.println("Started!");
  for(int i=0;i<255;i++){
   Serial.println("Speeding in + direction");
   analogWrite(leg1,i);
   digitalWrite(leg2,LOW);
   delay(10);
  }
  for(int i=255;i>0;i--){
    Serial.println("Slowing in + direction");
   analogWrite(leg1,i);
   digitalWrite(leg2,LOW);
   delay(10);
  }
  for(int i=0;i<255;i++){
    Serial.println("Speeding in - direction");
   analogWrite(leg2,i);
   digitalWrite(leg1,LOW);
   delay(10);
  }
  for(int i=255;i>0;i--){
    Serial.println("Slowing in - direction");
   analogWrite(leg2,i);
   digitalWrite(leg1,LOW);
   delay(10);
  }
    Serial.println("Finished!");
  }
}