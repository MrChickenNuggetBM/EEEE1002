//***************************************//
//* Session 2:                          *//
//* EEEBot Template Code for the ESP32  *//
//*                                     *//
//* ESP32 Slave Code README File        *//
//*                                     *//
//* UoN 2021 - ND                       *//
//***************************************//

A readme file is commonly posted alongside code in order to explain how to use it
Always read these before implementing or modifying code in order to understand what
you do should/shouldn't change.

To run this code, install the ESP32 I2C Slave Library from Moodle or from 
https://github.com/gutierrezps/ESP32_I2C_Slave

DO NOT modify/delete any of the code from the EEEBot_ESP32_firmware sketch - it has
been setup with everything you need for Session 2. Write your own code for the
master Arduino based off the way the slave ESP32 is set up. REMEMBER, as you are
using an Arduino NANO as the master (with 5V pinout) and an ESP32 as the slave
(with a maximum pin tolerance of 3.3V), you need to have a voltage level shifter 
on both the SDA and SCL data lines - otherwise you risk damaging the ESP32.

You may only change the pin numbers relating to the motors if the wheels do not
spin in the correct direction i.e. forwards when a positive integer is sent and 
backwards when a negative integer is sent. 

Connect you encoder to IO pins 32 and 33. If you want to switch if the count
increments or decrements in a particular direction, which wires are in which pins
i.e. if wire A is in IO32 and wire B is in IO33, switch them so wire A is in IO33
and wire B is in IO32.

1. The ESP32 slave address is set as 4 (0x04) - use this in your master code.
2. The only data that the ESP32 slave accepts is four bytes i.e. two bytes per
   signed integer. In your master code, send two signed integer values sequentially.
   See Example 1 and Example 2 under Additional Information & Materials in Session
   2 on Moodle. 
3. The two integer values that are sent to the slave should be between -255 and 
   255. If the value is outside of this range, it will be limited to -255 or 255; 
   whichever is closer. This relates to the PWM value that the motor will run on.
4. The first integer relates to the left motor, the second integer relates to the 
   right motor. Depending on the motor, a PWM value between 0 and ~150 won't be
   sufficient to turn the motor - it is reccommened you use PWM values of 200+.
5. A positive value indicates 'forwards' motion on that wheel, a negative value
   indicates a 'backwards' motion on that wheel.
6. The motors will run at a specified speed until instructed otherwise - send 0,0
   in the appropriate format to stop the vehicle.
7. On request, the ESP32 slave will send the current encoder count raw value to the
   master - it is NOT set to 0 when this happens, so you need to account for this
   when working out how many encoder counts have passed