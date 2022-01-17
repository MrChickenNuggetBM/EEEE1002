#include <Wire.h>               // include Wire library

void setup() {
  Wire.begin(0x08);             // join i2c bus with address 8
  Wire.onRequest(requestEvent); // create a receive event
}

void loop() {
  delay(500);
}

void requestEvent() {
  Wire.write("hello");          // respond with message - 5 bytes long
}
