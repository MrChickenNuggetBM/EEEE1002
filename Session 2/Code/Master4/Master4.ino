#include <Wire.h>

String message_rec;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}
void loop() {
  reportVendor();
  Serial.print("Vendor: ");
  Serial.println(message_rec);
  delay(500);

  reportModel();
  Serial.print("Model: ");
  Serial.println(message_rec);
  delay(500);

  reportVersion();
  Serial.print("Version: ");
  Serial.println(message_rec);

  delay(500);
  Serial.println();
}
void reportVendor(){
  message_rec = "";
  Wire.beginTransmission(0x08);  // transmit to device #8
  Wire.write("vendor");          // sends six bytes
  Wire.endTransmission();        // stop transmitting  

  Wire.requestFrom(0x08, 32);

  while (Wire.available()) {  //loop whilst bus is busy
    char c = Wire.read();     //receive data byte by byte
    if (c == '#') break;      //check for end of message
    message_rec += c;         //build complete message
  }
}
void reportModel(){
  message_rec = "";
  Wire.beginTransmission(0x08);  // transmit to device #8
  Wire.write("model");           // sends five bytes
  Wire.endTransmission();        // stop transmitting 

  Wire.requestFrom(0x08, 32);

  while (Wire.available()) {  // loop whilst bus is busy
    char c = Wire.read();     // receive data byte by byte
    if (c == '#') break;      // check for end of message
    message_rec += c;         // build complete message
  }
}
void reportVersion(){
  message_rec = "";
  Wire.beginTransmission(0x08);  // transmit to device #8
  Wire.write("version");         // sends seven bytes
  Wire.endTransmission();        // stop transmitting  

  Wire.requestFrom(0x08, 32);

  while (Wire.available()) {  // loop whilst bus is busy
    char c = Wire.read();     // receive data byte by byte
    if (c == '#') break;      // check for end of message
    message_rec += c;         // build complete message
  }
}
