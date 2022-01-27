#include <MPU6050_tockn.h> //IMU
#include <NewPing.h>       // HC-SR04
#include <Arduino.h>
#include <WirePacker.h> //to send data to ESP32
#include <Wire.h>

// defines for the HC-SR04
#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define MAX_DISTANCE 100

#define I2C_SLAVE_ADDR 0x04 // ESP32 Address

MPU6050 imu(Wire);                                  // IMU connected to the I2C Wire
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // HC-SR04 established connection

// determines the delay, until the the car starts moving forward for the manouveur
unsigned int startForwardMotion = 10 * 1000;
unsigned int endForwardMotion = startForwardMotion + 1000;

// variables used for conditional statements later on, to advance to the next parts of the manouveur
unsigned int doRotate_1 = 1;
unsigned int doReverse_1 = 1;
unsigned int doRotate_2 = 1;
unsigned int doReverse_2 = 1;
//---------------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  Wire.begin();
  imu.begin();
  imu.calcGyroOffsets(true); // calibrates the gyroscope on the IMU
}

int startAngle = (int)imu.getAngleZ(); // finds the angle, which the car is initially in
//---------------------------------------------------------------------------
void loop()
{
  int _time = (int)millis(); // finds the time since the start

  if (_time <= startForwardMotion)
  {
    slaveWrite(0, 0); // no motion until the end of the delay
  }
  else if (_time > startForwardMotion && _time < endForwardMotion)
  {
    Serial.println("start");
    slaveWrite(255, 255); // makes the car go forward, for 1 second.
  }
  // goes through all of these if statements.
  // when the task finishes, zero is returned, so it will be skipped in the next loop
  else if (doRotate_1 == 1)
  {
    // rotates the car 180 degrees anticlockwise
    doRotate_1 = rotate(startAngle + 180);
  }
  else if (doReverse_1 == 1)
  {
    // reverses the car until the closest obstacle is 10cm away
    doReverse_1 = reverse(10);
  }
  else if (doRotate_2 == 1)
  {
    // turns a further 90 degrees anticlockwise
    doRotate_2 = rotate((startAngle + 180) + 90);
  }
  else if (doReverse_2 == 1)
  {
    // reverses the car till the closest obstacle is 10cm away
    doReverse_2 = reverse(10);
  }
  else
  {
    // when everything has been conducted, puts into an infinite loop
    Serial.println("end");
    while (1)
    {
    }
  }

  delay(50);
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
/*---------------------------------------------------------------------------
   Inputs:
      int angleNeeded, this is the angular displacement needed, from the initial position

  rotates the car until the required angular displacement is reached

   Returns:
      0 to terminate that section of the loop
      1 to keep doing that section of the loop
  -----------------------------------------------------------------------------*/
int rotate(int angleNeeded)
{
  int error = 5;
  imu.update();
  int angle = (int)imu.getAngleZ();
  Serial.println(angle);

  if (angleNeeded + error < angle)
  {
    slaveWrite(255, 0);
  }
  else if (angleNeeded - error > angle)
  {
    slaveWrite(0, 255);
  }
  else
  {
    delay(1500);
    return 0;
  }

  return 1;
}
/*---------------------------------------------------------------------------
   Inputs:
      unsigned int distanceNeeded, this is the distance needed to stop

  moves the car back until the car is a set distance away from the closest obstacle

   Returns:
      0 to terminate that section of the loop
      1 to keep doing that section of the loop
  -----------------------------------------------------------------------------*/
int reverse(unsigned int distanceNeeded)
{
  unsigned int distance = sonar.ping_cm();
  Serial.println(distance);

  if (distance <= distanceNeeded)
  {
    slaveWrite(0, 0);
    delay(1500);
    return 0;
  }

  slaveWrite(-255, -255);
  return 1;
}
