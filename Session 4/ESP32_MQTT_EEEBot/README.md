"ESP32_MQTT_EEEBot.ino" contains the code, in which the ESP32 communicates with the broker using
the MQTT protocol.
The ESP32 sends sensor data to the broker. The ESP32 also receives control signals from the broker
and acts accordingly.

Please ensure you have these libraries installed:
https://github.com/gutierrezps/ESP32_I2C_Slave
https://www.arduino.cc/reference/en/libraries/pubsubclient/