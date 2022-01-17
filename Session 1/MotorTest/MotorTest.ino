#include <ESP32Encoder.h>

//**********************************//
//* Motor Test                     *//
//* for EEEBot                     *//
//*                                *//
//* UoN 2021                       *//
//**********************************//

// Use this code to correctly assign the four pins to move the car forwards, backwards, clockwise & counter-clockwise
// You first need to change the pin numbers for the four PWM pins below and then decided which go HIGH and LOW in each of the movements, stopMotors has been done for you
// ** marks where you need to insert the pin number or state

// name the motor control pins - replace the ** with your pin number
//#define PWMa 14
#define PWMb 27
#define PWMc 26
//#define PWMd 25

const int frequency = 5000;
const int resolution = 10;
const int PWMChannelB = 0;
const int PWMChannelC = 1;

ESP32Encoder encoder;

void setup() {
  // Enable the weak pull up resistors
  ESP32Encoder::useInternalWeakPullResistors=UP;

  // use pin 32 and 33 for the first encoder
  encoder.attachHalfQuad(32, 33);
  
  // clear the encoder's raw count and set the tracked count to zero
  encoder.clearCount();
  
  Serial.begin(9600);
  
  // configure the motor control pins as outputs
  float speed = 10/24500;
  pinMode(PWMa, OUTPUT);
  pinMode(PWMb, OUTPUT);
  pinMode(PWMc, OUTPUT);
  pinMode(PWMd, OUTPUT);

  ledcSetup(PWMChannelB, frequency, resolution);
  ledcSetup(PWMChannelC, frequency, resolution);

  ledcAttachPin(PWMb,PWMChannelB);
  ledcAttachPin(PWMc,PWMChannelC);
}

void loop() {
  //defines loop variable

  int countime = 650;

  signed long encoderCount = encoder.getCount();

  do
  {

    encoderCount = encoder.getCount();

    Serial.println(encoderCount);
    
    ledcWrite(PWMChannelB,0); //NON ROTARY
    ledcWrite(PWMChannelC,1023); //ROTARY
    

   if((encoderCount % 180) == 100)
   {
    ledcWrite(PWMChannelB,0); //NON ROTARY
    ledcWrite(PWMChannelC,1023); //ROTARY
    delay(20);
   }
   
  } while(encoderCount <= countime);

   Serial.println("end");

   while(encoderCount > countime)
   {
    stopMotors();
   }
  
     
}

void stopMotors(){
  digitalWrite(PWMa, LOW);
  digitalWrite(PWMb, LOW);
  digitalWrite(PWMc, LOW);
  digitalWrite(PWMd, LOW);
  ledcWrite(PWMChannelB,0); //NON ROTARY
  ledcWrite(PWMChannelC,0); //ROTARY
}
