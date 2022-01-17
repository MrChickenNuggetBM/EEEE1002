//**********************************//
//* SPI Demo – UoN 2021            *//
//* Master Arduino                 *//
//**********************************//
#include <SPI.h>
 
void setup (void) {
   Serial.begin(115200);   // set baud rate to 115200 for usart
   digitalWrite(SS, HIGH); // disable Slave Select
   SPI.begin ();
   SPI.setClockDivider(SPI_CLOCK_DIV8);  // divide the clock by 8
}
 
void loop (void) {
  digitalWrite(SS, LOW); // enable Slave Select
  SPI.transfer ('1');
  Serial.print('1');
  digitalWrite(SS, HIGH); // disable Slave Select
  
  delay(1000);

  digitalWrite(SS, LOW); // enable Slave Select
  SPI.transfer ('0');
  Serial.print('0');
  digitalWrite(SS, HIGH); // disable Slave Select
  
  delay(1000);
}
