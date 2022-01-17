#include <Wire.h>            // include Wire library
#define SLAVE_ADDRESS 0x08

String message_in, message_out;
char message[8];

void setup() {
  Wire.begin(SLAVE_ADDRESS);      // join i2c bus with address 8
  Wire.onReceive(receiveEvent);   // create a receive event
  Wire.onRequest(requestEvent);   // create a receive event
  Serial.begin(9600);         // start serial for output
}

void loop() {
}

void receiveEvent() {
  message_in = "";
  while (Wire.available()) {      // loop whilst bus is busy
  char c = Wire.read();       // receive data byte by byte
  message_in += c;        // form complete string
  }
  Serial.println(message_in);
  delay (500);
} 
void requestEvent() {
  if (message_in == "vendor") {
      message_out = "Arduino#";
  }
  if (message_in == "model") {
      message_out = "Nano#";
  }
  if (message_in == "version") {
      message_out = "v3.1#";
  }
  int buffer = message_out.length();
  message_out.toCharArray(message, buffer + 1);
  Serial.println(message); 
  Wire.write(message);
}
