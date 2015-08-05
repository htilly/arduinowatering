// #include <Ethernet.h>
#include <SPI.h>
// #include <aJSON.h>
#include <SimpleTimer.h>
// #include <sha1.h>



/*
  Pin configuration
*/
int moistureInputPin = 0;
int valveOutputPin = 8;



/*
  How often to check the plant needs watering
  and to send readings to the server
*/
unsigned long pollMillis = 1800000; // 30 min


/* Shall be 700
Testing with 800 

Calebrating..
300 - Dry dirt !
700 OK
Finally - set it to 650
*/
int waterAtMoisture = 650;

/*
  When the soil gets dry enough to warrant a watering,
  how many millis to open the valve for.
*/
int waterForMillis = 3500; // 3,5 sconds


/*
  Local IP settings


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 172, 16, 200, 138 };
byte submask[] = { 255, 255, 255, 0 };
byte gateway[] = { 172, 16, 200, 1 };
byte dns[] = { 8, 8, 8, 8 };

EthernetClient client;
*/

SimpleTimer timer;



void setup() {
  pinMode(valveOutputPin, OUTPUT);

  Serial.begin(9600);
  
  Ethernet.begin(mac, ip, dns, gateway, submask);

    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());



  timer.setInterval(pollMillis, poll);
}

void loop() {
  timer.run();
}

/*
  Main function that is run once per poll
*/
void poll() {
  Serial.print("Polling... ");

  //Using int for watered rather than boolean
  //as the cube server doesn't report metrics
  //on booleans very well
  int moisture = getSoilMoisture();
  int watered = 0;

  Serial.println(moisture);

  if (moisture < waterAtMoisture) {
    waterThePlant();
    watered = 1;
  }


}

/*
  Get the moisture
*/
int getSoilMoisture() {


  //Take a reading
  int reading = analogRead(moistureInputPin);

  return reading;
}

/*
  Gives the plant a blast of water
*/
void waterThePlant() {
  Serial.println ("Watering... ");
  digitalWrite(valveOutputPin, HIGH);
  delay(waterForMillis);
  digitalWrite(valveOutputPin, LOW);
}


