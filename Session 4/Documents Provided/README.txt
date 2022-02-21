*********************************
RASPBERRY PI LOGIN DETAILS:
	HOST NAME: b08ghali
	PASSWORD: eeymg2
*********************************

*********************************
RASPBERRY PI WIFI Details:
	SSID: b08ghali
	PASSWORD: 0eeymg20
*********************************

Please note that the files contained in this directory were obtained from the University of Nottingham Moodle for the "EEEE1002 - Applied Electrical and Electronic Engineering Construction Project" module.
The text below, contains the instructions given on Moodle, and the relevant files for each step.

/****************************************************************************************************************************************************************************************************************

Introduction:
	
In order to complete the session successfully, please familiarise yourself with all the documents below and only then work through the information in the order that it is presented.
It's not a race so please do not rush, take your time and make use of the support on offer.
This session builds on the material covered to date with the aim of creating and demonstrating a V2X communication system for the EEEBot.

Relevant Documents:
	1. Introduction.pdf

/****************************************************************************************************************************************************************************************************************

Step 1: Set Up the R-Pi

This guide will help you get up and running with your new Raspberry Pi Zero.
It will assist you through installing an Operating System, help you configure the Pi’s basic settings, enable you to communicate with your Pi by a variety of useful means.

Relevant Documents:
	2. From zero to Pi 3 A+ with zero additional hardware in a.pdf
	3. Configure your Pi3 A+ as a wireless station.pdf

/****************************************************************************************************************************************************************************************************************

Step 2: Set Up MQTT & Node-RED

This guide will walk you through the installation of the Mosquito MQTT broker and the Node-RED on your R-Pi.
This will enable you to develop a web based control panel to send/receive data to/from your R-Pi via a Node-RED dashboard.

Note: the example presented uses a different sensor to those available on the EEEBot, so you will need to adapt the example code to accommodate your sensors.
This is a key engineering skill as, typically, information online will not entirely match your specific application, and so the key appropriate information and/or code snippets need to be identified and used.

Relevant Documents:
	4. V2X Communications.pdf
	ESP32_MQTT_Example_Code
	ESP32_MQTT_EEEBot_Template

/****************************************************************************************************************************************************************************************************************

Step 3: All EEEBots in a Group to Communicate with a Single R-Pi

You will need now to work as a group and each member of the group will be responsible for:

1. Equipping their own vehicle with a sensor that can send data to the central controller to be displayed via a GUI. Each vehicle in the group must use a different sensor(s)
2. Equipping their vehicle with a device that can be controlled from the central controller’s GUI. The device can be the same for all vehicles in the group

Note: Successful completion of the above is worth 70% of session 4 and grade will be based on level of technical achievement

Some examples of what you could look to implement on your EEEBot are in the document linked below.
However, your are only constrained by your imagination!

Relevant Documents:
	5. Suggested MQTT tasks.pdf

/****************************************************************************************************************************************************************************************************************

Step 4: Set Up the R-Pi

Note: This step is worth the remaining 30% of the grade associated with session 4. Actual grade will depend of level of technical achievement.

At the end of the session the group is to present a single vehicle equipped with a number of sensors and is capable of line following that sends/receives data to/from the central controller that can:

	* Display status of each IR sensor
	* Display the weighted average
	* Vary the PID constants
