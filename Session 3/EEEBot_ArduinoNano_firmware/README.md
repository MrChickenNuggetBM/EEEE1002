"EEEBot_ArduinoNano_firmware.ino" contains the code, in which the Arduino Nano collects data
from the optical sensors and analyses them to find the weighted average. The value of the weighted
average is then used choose the correct PMW values to veer the EEEBot in the appropriate
direction. These values are then sent to the ESP32 using I2C

Please ensure you have this library installed: https://github.com/gutierrezps/ESP32_I2C_Slave
