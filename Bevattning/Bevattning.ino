#include <SPI.h>
#include <SimpleTimer.h>
#include <dht.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Wireless.h"

dht DHT;
#define dht_apin A0

//You will need to modify the next 3 lines to match you WiFi network and you ThingSpeak account.
// NOTE - For EPS8266 to work you NEED to modify SoftwareSerial.h.
// Make sure it is: #define _SS_MAX_RX_BUFF 256 // RX buffer size
// For OSX, this is the file:
// /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/libraries/SoftwareSerial/SoftwareSerial.h


const String APSSID = ""; //The name of the AP/SSID you connect to
const String wpaKey = ""; //The WPA key of your AP
const String ThingSpeakKey = ""; //You get this key when you sign up for a ThingSpeak account.




Wireless wifi(6,7); //Set up the WiFi library. Parameters: RX pin, TX pin, Enable pin, Reset pin. Normally: 10,4,2,3


/*
  Pin configuration
*/


//Soil Moisture Sensor
int moistureInputPin = A0;

//Temp & Humidity
int dhtInputPin = A1;

//Water valve
int valveOutputPin = 9;

//Power to moisture sensor via relay (save the equipment from corrosion)
int moistureOutputPin = 10;


/*
  How often to check the plant needs watering
  and to send readings to the server
*/
unsigned long pollMillis = 1800000; // 30 min

//unsigned long pollMillis = 30000; // 1 min

/*
Calebrating..
300 - Dry dirt !
700 OK
Finally - set it to 650
*/

int waterAtMoisture = 620;

/*
  When the soil gets dry enough to warrant a watering,
  how many millis to open the valve for.
*/
int waterForMillis = 1500; // 3,5 sconds



SimpleTimer timer;



void setup() {
  pinMode(valveOutputPin, OUTPUT);
  pinMode(moistureOutputPin, OUTPUT);




  Serial.begin(9600);
  Serial.println("Connecting to WiFi.");
  debug(4);; //The WiFi module need a little time to start, so we will wait before connecting to AP.

  wifi.connectToAP(APSSID, wpaKey); //Connects to the access point. The WiFi module will remember this network an connect automatically next time.
  debug(4);; //Wait a little to make sure it has time to connect.

  Serial.println("Checking IP.");
  wifi.getIP(); //Check if got an IP.
  debug(8);
  wifi.getStatus(); //Get the connection status.
  debug(8);
  Serial.println("Ready...");

  timer.setInterval(pollMillis, poll);
}

void loop() {

  DHT.read11(dhtInputPin);
  timer.run();

}

/*
  Main function that is run once per poll
*/
void poll() {
  Serial.print("Polling... ");

  Serial.print("Humidity & Temperature:");
  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(   .temperature);
  Serial.println("C  ");
  Serial.println();
  Serial.println();
  Serial.println();


  //Using int for watered rather than boolean
  //as the cube server doesn't report metrics
  //on booleans very well
  int moisture = getSoilMoisture();
  int watered = 0;
  Serial.print("Moisture:");
  Serial.println(moisture);
  Serial.println();
  Serial.println();
  Serial.print("----- END -----");
  Serial.println();
  Serial.println();

  if (moisture < waterAtMoisture) {
    waterThePlant();
    watered = 1;
  }

  //Send data to server
  String request = "";
  request = request + "GET /update?key=" + ThingSpeakKey + "&field1=" + DHT.humidity + "&field2=" + DHT.temperature + "&field3=" + moisture + "&field4=" + watered + "&field5=" + waterAtMoisture + "&field6=" + waterForMillis +"\r\n";

  Serial.println("Connecting to server.");
  wifi.connectToServer("184.106.153.149", 80); //Connects to the Thingspeak server on port 80.
  debug(4);

  Serial.println("Sending request.");
  wifi.sendDataToServer(request);  //Sends the GET request.
  debug(10); //Wait 20 seconds

  Serial.println("Disconnecting from server.....");
  wifi.disconnectFromServer();
  debug(20);

  Serial.println("Done!");
  Serial.println();
  Serial.println("Going to sleep.");


}

/*
  Get the moisture
*/
int getSoilMoisture() {


  //Take a reading

  Serial.println();
  Serial.println ("Reading moisture... ");
  Serial.println();
  digitalWrite(moistureOutputPin, HIGH);
  delay(500);
  int reading = analogRead(moistureInputPin);
  delay(100);
  digitalWrite(moistureOutputPin, LOW);


  return reading;
}

/*
  Gives the plant a blast of water
*/
void waterThePlant() {
  Serial.println();
  Serial.println();
  Serial.println ("Watering... ");
  Serial.println();
  digitalWrite(valveOutputPin, HIGH);
  delay(waterForMillis);
  digitalWrite(valveOutputPin, LOW);
}

void debug(int loops) {
  for (int i = 0; i <= loops; i++) {
    while (wifi.available()) {
      Serial.write(wifi.readChar());
    }
    delay(1000);
  }
}
