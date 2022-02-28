#include <ESP32Encoder.h>

#define PWMa 27 // Pin connected to left motor
#define PWMb 26 //Pin connected to right motor

const int frequency = 5000; // frequency of pulses
const int resolution = 10; // resolution of voltages to select
const int PWMChannelA = 0; // channel which sends signal to PMWa pin
const int PWMChannelB = 1; // channel which sends signal to PMWb pin

int countime = 650;

ESP32Encoder encoder;

void setup() {
  ESP32Encoder::useInternalWeakPullResistors = UP;

  // initiate encoder use with pins 32 and 33
  encoder.attachHalfQuad(32, 33);

  // reset the encoder count to 0
  encoder.clearCount();

  Serial.begin(9600);

  // configure the motor control pins as outputs
  pinMode(PWMa, OUTPUT);
  pinMode(PWMb, OUTPUT);

  // establish voltage connection with both channels
  ledcSetup(PWMChannelA, frequency, resolution);
  ledcSetup(PWMChannelB, frequency, resolution);

  // attaches each channel to the pin
  ledcAttachPin(PWMa, PWMChannelA);
  ledcAttachPin(PWMb, PWMChannelB);
}

void loop() {
  signed long encoderCount = encoder.getCount();

  do
  {

    encoderCount = encoder.getCount();

    Serial.println(encoderCount);

    ledcWrite(PWMChannelA, 1023); //NON ROTARY
    ledcWrite(PWMChannelB, 1023); //ROTARY

    //every 180 cycles, turns right a bit, to help it go in a straight line (random motion so not fully predictable)
    if ((encoderCount % 180) == 100)
    {
      ledcWrite(PWMChannelA, 0); //NON ROTARY
      ledcWrite(PWMChannelB, 1023); //ROTARY
      delay(20);
    }

  } while (encoderCount <= countime);

  //when the required distance has been travelled, ends the motion
  Serial.println("end");

  while (encoderCount > countime)
  {
    stopMotors();
  }
}

void stopMotors() {
  ledcWrite(PWMChannelA, 0); //NON ROTARY
  ledcWrite(PWMChannelB, 0); //ROTARY
}
