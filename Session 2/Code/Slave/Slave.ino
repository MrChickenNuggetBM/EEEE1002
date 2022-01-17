//**********************************//
//* SPI Demo – UoN 2021            *//
//* Slave Arduino                  *//
//**********************************//
#include <SPI.h>
char signal  = ' ';
byte LED = 2; // LED connected to digital pin
volatile boolean process;
 
void setup (void) {
   Serial.begin (115200);
   pinMode(MISO, OUTPUT); // have to send on master so it is set as an output
   pinMode(LED, OUTPUT);  // configure digital pin LED (2) as an output
   SPCR |= _BV(SPE);   // turn on SPI in slave mode
   process = false;
   SPI.attachInterrupt(); // turn on interrupt
}
 
ISR (SPI_STC_vect) // SPI interrupt routine 
{ 
   signal = SPDR; // read byte from SPI Data Register
   process = true;
}
 
void loop (void) {
   if (process) {
      process = false; // reset the process
      if (signal == '0') { digitalWrite(LED, LOW); }
      if (signal == '1') { digitalWrite(LED, HIGH); }
      Serial.print (signal); // print the array on serial monitor
  }
}
