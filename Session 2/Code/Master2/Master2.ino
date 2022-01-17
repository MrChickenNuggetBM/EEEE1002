#include <Wire.h>

void setup()
{
  Wire.begin();
}

void loop()
{
  Wire.beginTransmission(0x08);
  Wire.write("hello")
  Wire.endTransmission();
}
