void setup()
{
  pinMode(11,OUTPUT);
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

int val;
void loop()
{
  val = analogRead(A0);
  Serial.println(val);
  //analogWrite(11,val/4); //Converted 0-1023 to 0-255
  analogWrite(11,map(val,0,1023,0,255));
  
}
