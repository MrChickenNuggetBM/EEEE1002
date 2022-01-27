// #include <MPU6050_tockn.h> //IMU
// #include <NewPing.h>       // HC-SR04
#include <Arduino.h>
#include <WirePacker.h> //to send data to ESP32
#include <Wire.h>

#define I2C_SLAVE_ADDR 0x04
#define OPTICAL_1 A0
#define OPTICAL_2 A1
#define OPTICAL_3 A2
#define OPTICAL_4 A3
#define OPTICAL_5 A6
#define OPTICAL_6 A7

int read_1, read_2, read_3, read_4, read_5, read_6;
float weighted_average;
int min_1 = 483;
int min_2 = 554;
int min_3 = 416;
int min_4 = 499;
int min_5 = 530;
int min_6 = 536;
int max_ = 1017;
int count = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(OPTICAL_1, INPUT);
  pinMode(OPTICAL_2, INPUT);
  pinMode(OPTICAL_3, INPUT);
  pinMode(OPTICAL_4, INPUT);
  pinMode(OPTICAL_5, INPUT);
  pinMode(OPTICAL_6, INPUT);
}

void loop()
{
  count++;
  Serial.println(count);
  slaveWrite(count, 0);
  delay(400);
}
/*---------------------------------------------------------------------------
   Inputs:
      int leftMotor, this is the ledcwrite signal send to the left motor
      int rightMotor, this is the ledcwrite signal send to the right motor

  sends signals to the ESP32 so that it can drive the motors
  -----------------------------------------------------------------------------*/
void slaveWrite(int leftMotor, int rightMotor)
{
  WirePacker packer;

  packer.write((byte)((leftMotor & 0x0000FF00) >> 8));
  packer.write((byte)(leftMotor & 0x000000FF));

  packer.write((byte)((rightMotor & 0x0000FF00) >> 8));
  packer.write((byte)(rightMotor & 0x000000FF));

  Serial.println((byte)(rightMotor & 0xFFFFFFFF));

  packer.end();

  Wire.beginTransmission(I2C_SLAVE_ADDR);
  while (packer.available())
  {
    Wire.write(packer.read());
  }
  Serial.print("Left Motor: ");
  Serial.print(leftMotor);
  Serial.print(" Right Motor: ");
  Serial.println(rightMotor);
  Wire.endTransmission();
}
