#include <Wire.h>

String message;

void setup()
{
  Wire.begin(0x08);
  Wire.onReceive(received);
  Serial.begin(9600);
}

void loop()
{
  
}

void received()
{
  message = "";
  while(Wire.available())
  {
    char c = Wire.read();
    message += c;
  }
  Serial.println(message);
}
