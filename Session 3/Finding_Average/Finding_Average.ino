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
long read_1_sum, read_2_sum, read_3_sum, read_4_sum, read_5_sum, read_6_sum;
long count;

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
  read_1 = analogRead(OPTICAL_1);
  read_2 = analogRead(OPTICAL_2);
  read_3 = analogRead(OPTICAL_3);
  read_4 = analogRead(OPTICAL_4);
  read_5 = analogRead(OPTICAL_5);
  read_6 = analogRead(OPTICAL_6);

  read_1_sum += read_1;
  read_2_sum += read_2;
  read_3_sum += read_3;
  read_4_sum += read_4;
  read_5_sum += read_5;
  read_6_sum += read_6;

  count++;

  if (count == 10000) {
    Serial.print("s1: ");
    Serial.println(read_1_sum/10000);
    Serial.print("s2: ");
    Serial.println(read_2_sum/10000);
    Serial.print("s3: ");
    Serial.println(read_3_sum/10000);
    Serial.print("s4: ");
    Serial.println(read_4_sum/10000);
    Serial.print("s5: ");
    Serial.println(read_5_sum/10000);
    Serial.print("s6: ");
    Serial.println(read_6_sum/10000);
    while (1);
  }
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
