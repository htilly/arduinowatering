# arduinowatering

Solution for watering plants with Arduino....
Started out as a simple project but has become more complex over time =)

There are quite some trix to get the ESP8266-01 working correctly. I won´t cover this in details here.
Howerver, the files included in this project assume that the ESP8266 is communication at 9600 baud.


The following HW is beeing used:

-	Arduino Uno
-	WiFi module, ESP8266-01. http://www.miniinthebox.com/sv/esp8266-serie-wifi-tradlosa-modulen-wifi-tradlos-modul_p3247309.html
	- LD1117V33, http://eu.mouser.com/ProductDetail/STMicroelectronics/LD1117V33/?qs=sGAEpiMZZMsGz1a6aV8DcCz10aAT%252bcfyfixmM%2fM6hTA%3d
-	Moisture Sensor, http://www.miniinthebox.com/sv/fuktighetssensor-ground-luftfuktighet-sensor-module_p903362.html
-	Magnetic Valve, https://www.sparkfun.com/products/10456
-	Relay, http://www.dx.com/p/arduino-compatible-4-channel-relay-shield-module-144762#.VdGtdbT6Q1E
-	Temperature / Humidity Sensor, http://www.miniinthebox.com/temperature-humidity-sensor-dht11-module-for-arduino-deep-blue-works-with-official-arduino-board_p1141519.html

NOTE:

Libraries in both original Arduino and WiFi has been modified in order to get this to work.

You will need to modify the next 3 lines to match you WiFi network and you ThingSpeak account.
NOTE - For EPS8266 to work you NEED to modify SoftwareSerial.h.

Make sure it is: #define _SS_MAX_RX_BUFF 256 // RX buffer size
For OSX, this is the file:

/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/libraries/SoftwareSerial/SoftwareSerial.h	


Problem right now:
Moisture Sensor get broken within a week. Problem is that it´s constantly getting 5V causing corrosion.
To solve the problem I will power the sensor only when needed thru a relay.


TODO:
-	Power Moisture Sensor thru relay.
-	Pull setting from external source.


More informarion and original libraries for ESP8266-01, see:
http://www.zeptobit.com/8266wing/
