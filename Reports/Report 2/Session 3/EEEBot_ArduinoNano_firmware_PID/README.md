"EEEBot_ArduinoNano_firmware_PID.ino" contains the code, in which the Arduino Nano collects data
from the optical sensors and analyses them to find the weighted average. The value of the weighted
average is, along with the PID algorithm, to find PMW values to veer the EEEBot in the appropriate
direction. These values are then sent to the ESP32 using I2C.

Please ensure you have this library installed: https://github.com/gutierrezps/ESP32_I2C_Slave
