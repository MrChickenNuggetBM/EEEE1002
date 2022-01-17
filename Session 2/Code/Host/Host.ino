//**********************************//
//* Hardware Serial (UART) Demo    *//
//*                                *//
//* UoN 2021                       *//
//*                                *//
//* Host Arduino                   *//
//**********************************//

#include <SoftwareSerial.h>
SoftwareSerial SoftSerial(11,12);

void setup() 
{
    SoftSerial.begin(9600); //initialise serial
}
  

void loop() 
{
  SoftSerial.print(1); // send signal to turn LED on
  delay(1000);
  SoftSerial.print(0); // send signal to turn LED off
  delay(1000);
}
