#include <NewPing.h>

#define TRIGGER_PING 11
#define ECHO_PING 12
#define MAX_DISTANCE 200

#define PIN 3

NewPing sonar(TRIGGER_PING,ECHO_PING,MAX_DISTANCE);

float fadeValue;

void setup()
{
  Serial.begin(9600);
  pinMode(PIN, OUTPUT);
}

void loop()
{
  delay(50);
  unsigned int distance = sonar.ping_cm();
  Serial.print(distance);
  Serial.println(" cm");

  fadeValue = (255 * ((float)distance/1000));

  Serial.print("fadeValue = ");
  Serial.println(fadeValue);

  analogWrite(PIN, fadeValue);
  delay(100);
}
