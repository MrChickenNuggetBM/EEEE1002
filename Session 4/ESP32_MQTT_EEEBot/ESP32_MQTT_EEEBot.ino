//****************************************//
//* ESP32 MQTT EEEBot Template           *//
//* Modified from Rui Santos'            *//
//* https://randomnerdtutorials.com      *//
//*                                      *//
//* ESP32 Code                           *//
//*                                      *//
//* UoN 2022 - ND                        *//
//****************************************//

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <WireSlave.h>

#include <ESP32Encoder.h>

// IO21 & IO22 are the default I2C pins on the ESP32
#define SDA_PIN 21
#define SCL_PIN 22
#define I2C_SLAVE_ADDR 0x04

#define PWMa 14
#define PWMb 27
#define PWMc 26
#define PWMd 25

// I2C and motor global variables
void receiveEvent(int howMany);
void requestEvent();

ESP32Encoder encoder;
int encoderCount;

const int freq = 30000;
const int resolution = 8;
const int pwmChannela = 0;
const int pwmChannelb = 1;
const int pwmChannelc = 2;
const int pwmChanneld = 3;

int leftMotor_speed = 0;
int rightMotor_speed = 0;

// Wifi global variables
const char *ssid = "B08Ghali was not an imposter";
const char *password = "_eeymg2_";

const char *mqtt_server = "192.168.2.1"; // MQTT Broker IP address

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup()
{
  Serial.begin(115200);

  // attempts to connect to the I2C
  bool success = WireSlave.begin(SDA_PIN, SCL_PIN, I2C_SLAVE_ADDR);
  if (!success)
  {
    Serial.println("I2C Slave Init Failed");
    while (1)
      delay(100);
  }

  // defines the function that needs to be executed when receiving, or requesting data
  WireSlave.onReceive(receiveEvent);
  WireSlave.onRequest(requestEvent);

  // connect to encoder, using internal weak pull up resistors, and reset count to 0
  ESP32Encoder::useInternalWeakPullResistors = UP;
  encoder.attachHalfQuad(32, 33);
  encoder.setCount(0);

  // Serial.println("Encoder Start = " + String((int32_t)encoder.getCount()));

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

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
  WireSlave.update();

  // get Wifi
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000)
  {
    lastMsg = now;

    // sends the encoder data
    encoderCount = encoder.getCount();

    char encoderString[8];
    
    dtostrf(encoderCount, 1, 0, encoderString);
    Serial.print("Count: ");
    Serial.println(encoderString);
    client.publish("esp32/count", encoderString);

    // Add your own code here i.e. sensor measurements, publish topics & subscribe topics for GPIO control
    // --

    // --
  }
}

// this function executes when data is requested from the master device
void requestEvent(void)
{
  WireSlave.write(encoderCount);
}

// this function executes whenever data is received from the master device
void receiveEvent(int howMany)
{
  if (howMany != 4) // for 2 16-bit numbers, the data will be 4 bytes long - anything else is an error
  {
    emptyBuffer();
    return;
  }

  int16_t leftMotor_speed = 0;
  int16_t rightMotor_speed = 0;

  uint8_t leftMotor_speed16_9 = WireSlave.read();  // receive bits 16 to 9 of x (one byte)
  uint8_t leftMotor_speed8_1 = WireSlave.read();   // receive bits 8 to 1 of x (one byte)
  uint8_t rightMotor_speed16_9 = WireSlave.read(); // receive bits 16 to 9 of y (one byte)
  uint8_t rightMotor_speed8_1 = WireSlave.read();  // receive bits 8 to 1 of y (one byte)

  leftMotor_speed = (leftMotor_speed16_9 << 8) | leftMotor_speed8_1;    // combine the two bytes into a 16 bit number
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
  while (WireSlave.available())
  {
    WireSlave.read();
  }
}

// function to run the right motor
void runRightMotor(int rightMotor_speed)
{
  rightMotor_speed = constrain(rightMotor_speed, -255, 255); // limits the speed value an 8 bit PWM value - the negative is handled below
  if (rightMotor_speed < 0)
  { // if the value is negative, run the motor 'backwards'
    ledcWrite(pwmChannela, abs(rightMotor_speed));
    ledcWrite(pwmChannelb, 0); // abs() takes the absolute value i.e. removes the negative sign, as the PWM value has to be between 0 and 255
  }

  else
  { // else run the motor 'forwards' or stop
    ledcWrite(pwmChannela, 0);
    ledcWrite(pwmChannelb, rightMotor_speed);
  }
}

// function to run the left motor
void runLeftMotor(int leftMotor_speed)
{
  leftMotor_speed = constrain(leftMotor_speed, -255, 255); // limits the speed value an 8 bit PWM value - the negative is handled below
  if (leftMotor_speed < 0)
  { // if the value is negative, run the motor 'backwards'
    ledcWrite(pwmChannelc, 0);
    ledcWrite(pwmChanneld, abs(leftMotor_speed)); // abs() takes the absolute value i.e. removes the negative sign, as the PWM value has to be between 0 and 255
  }

  else
  { // else run the motor 'forwards' or stop
    ledcWrite(pwmChannelc, leftMotor_speed);
    ledcWrite(pwmChanneld, 0);
  }
}

// Wifi functions
void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client"))
    {
      Serial.println("connected");
      client.subscribe("esp32/output");
      // Add your subscribe topics here
      // --

      // --
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Add your subscribed topics here i.e. statements to control GPIOs with MQTT
  // --

  // --
}

void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
