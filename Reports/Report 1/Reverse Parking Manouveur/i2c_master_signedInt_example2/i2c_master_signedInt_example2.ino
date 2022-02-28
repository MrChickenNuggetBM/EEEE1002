//****************************************//
//* Example 2 Code for Sending           *//
//* Signed Integers over I2C             *//
//* Master to ESP32 (Slave)              *//
//*                                      *//
//* Master Code                          *//
//*                                      *//
//* UoN 2021 - ND                        *//
//****************************************//

// you can use either an ESP32 or an Arduino board as the master
// remember, if you use an Arduino and ESP32 for serial communication, you need a voltage logic level shifter on the data lines

// read through all of the code and the comments before asking for help
// research 'two's complement' if this is not familiar to you as it is used to represented signed (i.e. positive and negative) values

// the difference in this code from example 1 is that the WireSlave.h (ESP32 I2C Slave) library is used to setup the ESP32 as a slave device
// as this library has to be used on the slave device, for compatibility, it also has to be used on the master device even though it is an Arduino
// read through the library examples for further code examples under File --> Examples --> ESP32 I2C Slave

#include <Arduino.h>
#include <Wire.h>
#include <WirePacker.h>

#define I2C_SLAVE_ADDR 0x04 // 4 in hexadecimal

void setup()
{
  Serial.begin(115200);
  Wire.begin();   // join i2c bus (address optional for master)
}

// the minimum and maximum values here are determined by the amount of bits used by the chosen variable type
// for int, this is either 16-bits or 32-bits
// due to two's complement, the minimum value is -2^(N-1), and the maximum is (2^(N-1))-1; where N is the number of bits
int x = -255;
int y = 255;

void loop()
{
  Serial.println(x);
  WirePacker packer;
  /* depending on the mirocontroller, the int variable is stored as 32-bits or 16-bits
     if you want to increase the value range, first use a suitable variable type and then modify the code below
     for example; if the variable used to store x and y is 32-bits and you want to use signed values between -2^31 and (2^31)-1
     uncomment the four lines below relating to bits 32-25 and 24-17 for x and y
     for my microcontroller, int is 32-bits hence x and y are AND operated with a 32 bit hexadecimal number - change this if needed
  */
  //packer.write((byte)((x & 0xFF000000) >> 24)); // bits 32 to 25 of x
  //packer.write((byte)((x & 0x00FF0000) >> 16)); // bits 24 to 17 of x
  packer.write((byte)((x & 0x0000FF00) >> 8));    // first byte of x, containing bits 16 to 9
  packer.write((byte)(x & 0x000000FF));           // second byte of x, containing the 8 LSB - bits 8 to 1
  //packer.write((byte)((y & 0xFF000000) >> 24)); // bits 32 to 25 of y
  //packer.write((byte)((y & 0x00FF0000) >> 16)); // bits 24 to 17 of y
  packer.write((byte)((y & 0x0000FF00) >> 8));    // first byte of y, containing bits 16 to 9
  packer.write((byte)(y & 0x000000FF));           // second byte of y, containing the 8 LSB - bits 8 to 1
  packer.end();
  
  Wire.beginTransmission(I2C_SLAVE_ADDR); // transmit to device #4
  while (packer.available()) {            // write every packet byte
    Wire.write(packer.read());
  }
  Wire.endTransmission();                 // stop transmitting
  delay(100);
}
