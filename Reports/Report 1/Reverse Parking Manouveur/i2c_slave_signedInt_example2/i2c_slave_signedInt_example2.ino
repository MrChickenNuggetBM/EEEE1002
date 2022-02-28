//****************************************//
//* Example 2 Code for Sending           *//
//* Signed Integers over I2C             *//
//* Arduino (Master) to ESP32 (Slave)    *//
//*                                      *//
//* Slave Code                           *//
//*                                      *//
//* UoN 2021 - ND                        *//
//****************************************//

// read through all of the code and the comments before asking for help
// research 'two's compliment' if this is not familiar to you as it is used to represented signed (i.e. positive and negative) values

// the difference in this code from example 1 is that the WireSlave.h (ESP32 I2C Slave) library is used to setup the ESP32 as a slave device
// read through the library examples for further code examples under File --> Examples --> ESP32 I2C Slave

#include <Arduino.h>
#include <Wire.h>
#include <WireSlave.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define I2C_SLAVE_ADDR 0x04

void receiveEvent(int howMany);

void setup()
{
    Serial.begin(115200);

    bool success = WireSlave.begin(SDA_PIN, SCL_PIN, I2C_SLAVE_ADDR);
    if (!success) {
        Serial.println("I2C slave init failed");
        while(1) delay(100);
    }

    WireSlave.onReceive(receiveEvent);
}

void loop()
{
  WireSlave.update();
  delay(1);
}

// this function executes whenever data is received from master device
void receiveEvent(int howMany)
{
  if(howMany != 4)  // for 2 16-bit numbers, the data will be 4 bytes long - anything else is an error
  {
    emptyBuffer();
    return;
  }
  
  int16_t x = 0;
  int16_t y = 0;
  
  uint8_t x16_9 = WireSlave.read();  // receive bits 16 to 9 of x (one byte)
  uint8_t x8_1 = WireSlave.read();   // receive bits 8 to 1 of x (one byte)
  uint8_t y16_9 = WireSlave.read();   // receive bits 16 to 9 of y (one byte)
  uint8_t y8_1 = WireSlave.read();   // receive bits 8 to 1 of y (one byte)

  x = (x16_9 << 8) | x8_1; // combine the two bytes into a 16 bit number
  y = (y16_9 << 8) | y8_1; // combine the two bytes into a 16 bit number

  Serial.print("x: ");
  Serial.print(x);
  Serial.print("\t");
  Serial.print("y: ");
  Serial.println(y);
}

// function to clear the I2C buffer
void emptyBuffer(void)
{
  Serial.println("Error: I2C Byte Size Mismatch");
  while(WireSlave.available())
  {
    WireSlave.read();
  }
}
