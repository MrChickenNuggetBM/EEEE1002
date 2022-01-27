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

int stable_speed = 170;

float kp = 1, kd = 1, ki = 1;

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
  //reads the voltage level from the sensors
  read_1 = analogRead(OPTICAL_1);
  read_2 = analogRead(OPTICAL_2);
  read_3 = analogRead(OPTICAL_3);
  read_4 = analogRead(OPTICAL_4);
  read_5 = analogRead(OPTICAL_5);
  read_6 = analogRead(OPTICAL_6);

  //constrains the values to a specified range, to disallow extremes
  read_1 = constrain(read_1, min_1, max_);
  read_2 = constrain(read_2, min_2, max_);
  read_3 = constrain(read_3, min_3, max_);
  read_4 = constrain(read_4, min_4, max_);
  read_5 = constrain(read_5, min_5, max_);
  read_6 = constrain(read_6, min_6, max_);

  //maps the values into the 0 to 255 range
  read_1 = map(read_1, min_1, max_, 0, 255);
  read_2 = map(read_2, min_2, max_, 0, 255);
  read_3 = map(read_3, min_3, max_, 0, 255);
  read_4 = map(read_4, min_4, max_, 0, 255);
  read_5 = map(read_5, min_5, max_, 0, 255);
  read_6 = map(read_6, min_6, max_, 0, 255);

  //makes black a higher signal than white
  read_1 = 255 - read_1;
  read_2 = 255 - read_2;
  read_3 = 255 - read_3;
  read_4 = 255 - read_4;
  read_5 = 255 - read_5;
  read_6 = 255 - read_6;

  //calcuates the weighted average and determines the pid speed
  weighted_average = ((read_1 * 3.25) + (read_2 * 1.95) + (read_3 * 0.65) + (read_4 * -0.65) + (read_5 * -1.95) + (read_6 * -3.25)) / (read_1 + read_2 + read_3 + read_4 + read_5 + read_6);
  Serial.println(weighted_average);
  pid(weighted_average);
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
}
/*---------------------------------------------------------------------------
   Inputs:
      float weighted_average

  calculates the speed of the motors using the pid approach
  -----------------------------------------------------------------------------*/
void pid(float weighted_average)
{
  static float previous = 0;
  static float integral = 0;
  integral += weighted_average;

  float offset = kp*weighted_average + ki*integral + kd*(error - previous);
  
  previous = weighted_average;
  
  int leftSpeed = constrain(stable_speed - offset, -255, 255);
  int rightSpeed = constrain(stable_speed + offset, -255, 255);

  slaveWrite(leftSpeed,rightSpeed);
}
