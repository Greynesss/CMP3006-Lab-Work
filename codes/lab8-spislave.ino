//slave's code
#include <SPI.h>

char buf[100]; //string buffer to hold the characters in
volatile byte pos = 0; //iterator used while filling the buffer
volatile boolean readFlag = false; //indicates end of a sentence

void setup(){
 cli();

 Serial.begin(115200); 
 Serial.println("SLAVE'S MONITOR!");
 
 pinMode(MISO,OUTPUT); //enable MISO line
 SPCR |= (1<<SPIE)| (1<<SPE); //Enable interrupts and SPI
 SPCR &= ~(1<<MSTR); // Clearing for declaring "slave"

 sei();
}

void loop(){

  if(readFlag){  //write the sentence on serial monitor
    buf[pos]=0;
    Serial.println(buf);
    pos=0;
    readFlag=false;
    
  }
}

ISR(SPI_STC_vect){
 byte c = SPDR; //get char from SPDR
 
 if (pos < (sizeof(buf)-1)){
   buf[pos++] = c; //add characters to buffer
 }
 if( c == '\n') { //when newline, go to loop() to print
  readFlag =true;
 }
  
}