#include <Arduino.h>
#include <WirePacker.h> //to send data to ESP32
#include <Wire.h>
#include <WireSlaveRequest.h>

#define I2C_SLAVE_ADDR 0x04
#define MAX_RESPONSE_LENGTH 32
#define OPTICAL_1 A0
#define OPTICAL_2 A1
#define OPTICAL_3 A2
#define OPTICAL_4 A3
#define OPTICAL_5 A6
#define OPTICAL_6 A7

int read_1, read_2, read_3, read_4, read_5, read_6 = 0;
float weighted_average = 0;
int min_1 = 483;
int min_2 = 554;
int min_3 = 416;
int min_4 = 499;
int min_5 = 530;
int min_6 = 536;
int max_ = 1017;
float error = 0.05;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
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

  read_1 = constrain(read_1, min_1, max_);
  read_2 = constrain(read_2, min_2, max_);
  read_3 = constrain(read_3, min_3, max_);
  read_4 = constrain(read_4, min_4, max_);
  read_5 = constrain(read_5, min_5, max_);
  read_6 = constrain(read_6, min_6, max_);

  read_1 = map(read_1, min_1, max_, 1, 255);
  read_2 = map(read_2, min_2, max_, 1, 255);
  read_3 = map(read_3, min_3, max_, 1, 255);
  read_4 = map(read_4, min_4, max_, 1, 255);
  read_5 = map(read_5, min_5, max_, 1, 255);
  read_6 = map(read_6, min_6, max_, 1, 255);

  read_1 = 255 - read_1;
  read_2 = 255 - read_2;
  read_3 = 255 - read_3;
  read_4 = 255 - read_4;
  read_5 = 255 - read_5;
  read_6 = 255 - read_6;

  Serial.print("sensor 1: ");
  Serial.print(read_1);
  Serial.print(", sensor 2: ");
  Serial.print(read_2);
  Serial.print(", sensor 3: ");
  Serial.print(read_3);
  Serial.print(", sensor 4: ");
  Serial.print(read_4);
  Serial.print(", sensor 5: ");
  Serial.print(read_5);
  Serial.print(", sensor 6: ");
  Serial.println(read_6);

  weighted_average = ((read_1 * 3.25) + (read_2 * 1.95) + (read_3 * 0.65) + (read_4 * -0.65) + (read_5 * -1.95) + (read_6 * -3.25)) / (read_1 + read_2 + read_3 + read_4 + read_5 + read_6);

  Serial.println(weighted_average);

  if (weighted_average > error)
  {
    Serial.println("Left");
    slaveWrite(165, 185);
  }
  else if (weighted_average < -error)
  {
    Serial.println("Right");
    slaveWrite(185, 165);
  }
  else
  {
    Serial.println("Forward");
    slaveWrite(170, 170);
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
  delay(100);
}