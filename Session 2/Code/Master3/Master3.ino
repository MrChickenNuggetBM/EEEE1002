#include <Wire.h>    // include Wire library

String message = "";
bool   message_flag = false;

void setup() {
  Wire.begin();       // join i2c bus (address optional for master)
  Serial.begin(9600); // start serial to visualise data
                      // received via serial monitor in the IDE
}

void loop() {
  Wire.requestFrom(0x08, 5);    // request 6 bytes from slave device #8
  while (Wire.available()) {    // loop whilst slave sends data
                                // i.e. whilst bus is busy
    char c = Wire.read();       // receive data byte by byte
    message += c;               // form complete string
    message_flag = true;         // set true to indicate message received
  }

  if (message_flag == true) {
    Serial.println (message);
    message = "";
    message_flag = false;
  }
  
  delay(500);
}
