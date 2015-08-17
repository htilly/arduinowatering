# arduinowatering

Simple solution for watering my plants....

The following HW is beeing used:

-	Arduino Uno
-	Moisture Sensor, http://www.miniinthebox.com/sv/fuktighetssensor-ground-luftfuktighet-sensor-module_p903362.html
-	Magnetic Valve, https://www.sparkfun.com/products/10456

NOTE:

Libraries in both original Arduino and WiFi has been modified in order to get this to work.

You will need to modify the next 3 lines to match you WiFi network and you ThingSpeak account.
NOTE - For EPS8266 to work you NEED to modify SoftwareSerial.h.
Make sure it is: #define _SS_MAX_RX_BUFF 256 // RX buffer size
For OSX, this is the file:
/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/libraries/SoftwareSerial/SoftwareSerial.h	


Problem right now:
Moisture Sensor get broken within a week. Problem is that it´s constantly getting 5V causing corrosion.
To solve the problem I will power the sensor thru a relay.


TODO:
-	Power Moisture Sensor thru relay
-	Pull setting from external source
