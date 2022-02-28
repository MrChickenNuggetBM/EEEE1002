#include <MPU6050_tockn.h>
#include <Wire.h>

#define LED_PIN 3 // defines the pin, which the LED is connected to (the LED also connected to ground)

float fadeValue;
MPU6050 mpu6050(Wire); // states that the MPU is connected to the I2C Wire

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true); // activates the Gyroscope of the MPU
  pinMode(LED_PIN, OUTPUT); // sets the microcontroller pin connected to the LED as an output
}

void loop() {
  mpu6050.update(); // gets new readings from the MPU
  float angle = abs(mpu6050.getAngleZ()); // gets the angle around the z-axis
  fadeValue = 255 * (angle/1000);

  Serial.print("Angle: ");
  Serial.println(angle);
  Serial.print("Fade Value: ");
  Serial.print(fadeValue);

  analogWrite(LED_PIN, fadeValue); //sends a voltage to the LED
}
