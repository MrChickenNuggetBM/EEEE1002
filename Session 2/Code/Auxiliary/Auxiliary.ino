//**********************************//
//* Hardware Serial (UART) Demo    *//
//*                                *//
//* UoN 2021                       *//
//*                                *//
//* Auxiliary Arduino              *//
//**********************************//

#include <SoftwareSerial.h>

SoftwareSerial SoftSerial(11,12);

char signal  = ' ';
byte LED = 2; // LED connected to digital pin 

 
void setup() 
{
   pinMode(LED, OUTPUT);
   SoftSerial.begin(9600);     // initialise serial
   SoftSerial.println("START");  // write START to serial monitor of the auxiliary
}
 
 
void loop()
{
   if(SoftSerial.available())
   {
      char signal = SoftSerial.read();
      if (signal == '0') { 
  digitalWrite(LED, LOW); 
      }
      if (signal == '1') { 
  digitalWrite(LED, HIGH); 
      }
      SoftSerial.println(signal);
   }
 
}
