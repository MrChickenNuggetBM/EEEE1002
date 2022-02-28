#include <NewPing.h>

#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define MAX_DISTANCE 100

#define LED_PIN 3 // defines the pin, which the LED is connected to (the LED also connected to ground)

NewPing sonar(TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE); // initiating a connection to the ultrasonic sensor

float fadeValue;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  delay(50);
  unsigned int distance = sonar.ping_cm(); // finds the distance, in cm
  Serial.print(distance);
  Serial.println(" cm");

  fadeValue = (255 * ((float)distance/1000)); //uses the distance to find the ratio of voltage to give to the LED light (out of 255)

  Serial.print("fadeValue = ");
  Serial.println(fadeValue);

  analogWrite(LED_PIN, fadeValue); //sends a voltage to the LED
  delay(100);
}
