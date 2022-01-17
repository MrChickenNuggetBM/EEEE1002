//***************************************//
//* Session 2:                          *//
//* EEEBot Template Code for the ESP32  *//
//*                                     *//
//* ESP32 Slave Code                    *//
//*                                     *//
//* UoN 2021 - ND                       *//
//***************************************//

// read through the accompanying readme file - only then ask for help if you are still unsure

// DO NOT modify or edit any of this code - for Session 2, the ESP32 code is provided for you
// the only exception is modify the pin numbers for the motors (if the motors do not spin the correct way)

// include libraries
#include <ESP32Encoder.h>
#include <Arduino.h>
#include <Wire.h>
#include <WireSlave.h>

// IO21 & IO22 are the default I2C pins on the ESP32
#define SDA_PIN 21
#define SCL_PIN 22
#define I2C_SLAVE_ADDR 0x04 // 4 in hexadecimal

void receiveEvent(int howMany);
void requestEvent();

// encoder variables
ESP32Encoder encoder;

int encoderCount;

// define the motor control pins
#define PWMa 14
#define PWMb 27
#define PWMc 26
#define PWMd 25
 
// set up of PWM properties
const int freq = 30000;
const int resolution = 8;
const int pwmChannela = 0;
const int pwmChannelb = 1;
const int pwmChannelc = 2;
const int pwmChanneld = 3;

// set up of the motor speeds, set to 0 by default
int leftMotor_speed = 0;
int rightMotor_speed = 0;


void setup() {
  Serial.begin(115200);

  bool success = WireSlave.begin(SDA_PIN, SCL_PIN, I2C_SLAVE_ADDR);
  if (!success) {
      Serial.println("I2C Slave Init Failed");
      while(1) delay(100);  // forever loop
  }

  WireSlave.onReceive(receiveEvent);
  WireSlave.onRequest(requestEvent);

  // enable the weak pull up resistors
  ESP32Encoder::useInternalWeakPullResistors=UP;

  // either change your connections to IO32 and IO33 or change the pin numbers in the code
  // to change whether the count increments or decrements when turning in a particular direction, 
  // switch the order of the pin numbers in attachHalQuad()
  encoder.attachHalfQuad(32, 33);                                                                 // <--------------

  // set starting count value after attaching
  encoder.setCount(0);

  // print statement used for testing
  //Serial.println("Encoder Start = " + String((int32_t)encoder.getCount()));
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannela, freq, resolution);
  ledcSetup(pwmChannelb, freq, resolution);
  ledcSetup(pwmChannelc, freq, resolution);
  ledcSetup(pwmChanneld, freq, resolution);
 
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(PWMa, pwmChannela);
  ledcAttachPin(PWMb, pwmChannelb);
  ledcAttachPin(PWMc, pwmChannelc);
  ledcAttachPin(PWMd, pwmChanneld);

  // configure the motor control pins as outputs
  pinMode(PWMa, OUTPUT);
  pinMode(PWMb, OUTPUT);
  pinMode(PWMc, OUTPUT);
  pinMode(PWMd, OUTPUT);
}


void loop() {
  encoderCount = encoder.getCount();
  WireSlave.update();
}


// this function executes when data is requested from the master device
void requestEvent(void)
{
  Wire.write(encoderCount);
}


// this function executes whenever data is received from the master device
void receiveEvent(int howMany)
{
  if(howMany != 4)  // for 2 16-bit numbers, the data will be 4 bytes long - anything else is an error
  {
    emptyBuffer();
    return;
  }
  
  int16_t leftMotor_speed = 0;
  int16_t rightMotor_speed = 0;
  
  uint8_t leftMotor_speed16_9 = WireSlave.read();  // receive bits 16 to 9 of x (one byte)
  uint8_t leftMotor_speed8_1 = WireSlave.read();   // receive bits 8 to 1 of x (one byte)
  uint8_t rightMotor_speed16_9 = WireSlave.read();   // receive bits 16 to 9 of y (one byte)
  uint8_t rightMotor_speed8_1 = WireSlave.read();   // receive bits 8 to 1 of y (one byte)

  leftMotor_speed = (leftMotor_speed16_9 << 8) | leftMotor_speed8_1; // combine the two bytes into a 16 bit number
  rightMotor_speed = (rightMotor_speed16_9 << 8) | rightMotor_speed8_1; // combine the two bytes into a 16 bit number

  Serial.print("Left Motor: ");
  Serial.print(leftMotor_speed);
  Serial.print("\t");
  Serial.print("Right Motor: ");
  Serial.println(rightMotor_speed);

  runLeftMotor(leftMotor_speed);
  runRightMotor(rightMotor_speed);
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


// function to run the right motor
void runRightMotor(int rightMotor_speed) {
  rightMotor_speed = constrain(rightMotor_speed, -255, 255);   // limits the speed value an 8 bit PWM value - the negative is handled below
  if (rightMotor_speed < 0) {    // if the value is negative, run the motor 'backwards'
    ledcWrite(pwmChannela, abs(rightMotor_speed));
    ledcWrite(pwmChannelb, 0);   // abs() takes the absolute value i.e. removes the negative sign, as the PWM value has to be between 0 and 255
  }

  else {    // else run the motor 'forwards' or stop
    ledcWrite(pwmChannela, 0);       
    ledcWrite(pwmChannelb, rightMotor_speed); 
  }
}


// function to run the left motor
void runLeftMotor(int leftMotor_speed) {
  leftMotor_speed = constrain(leftMotor_speed, -255, 255);   // limits the speed value an 8 bit PWM value - the negative is handled below
  if (leftMotor_speed < 0) {    // if the value is negative, run the motor 'backwards'
    ledcWrite(pwmChannelc, 0);
    ledcWrite(pwmChanneld, abs(leftMotor_speed));   // abs() takes the absolute value i.e. removes the negative sign, as the PWM value has to be between 0 and 255
  }

  else {    // else run the motor 'forwards' or stop
    ledcWrite(pwmChannelc, leftMotor_speed);       
    ledcWrite(pwmChanneld, 0); 
  }
}
    
