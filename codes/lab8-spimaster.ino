//master's code 
#include <SPI.h>

void setup() {
  Serial.begin(115200);
  Serial.println("MASTER'S MONITOR");
  digitalWrite(SS,HIGH); //disable transmission by SS to high
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  SPI.begin(); //Initialize SPI bus by setting SCK, MOSI and SS to outputs (pinMode)
               //and pulling SCK and MOSI low, and SS high. (digitalWrite)
}

void loop() {
  //SPDR is 1 byte(8 bits), char is also 1 byte
  //we can send 1 char at a time at most
  char c;
  digitalWrite(SS,LOW); // enable transmission

  for(const char *i = "From master to slave, HELLO! \n"; c=*i; i++){
    SPI.transfer(c); //write to SPDR and send to slave device
  }
  digitalWrite(SS,HIGH); //disable transmission
  delay(300);
}