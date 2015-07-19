// #include <Ethernet.h>
#include <SPI.h>
// #include <aJSON.h>
#include <SimpleTimer.h>
// #include <sha1.h>
// #include <mysql.h>


/*
  Pin configuration
*/
int moistureInputPin = 0;
// int moistureOutputPinTop = 3;
// int moistureOutputPinBottom = 4;
// int valveOutputPin = 9;
int valveOutputPin = 8;



/*
  How often to check the plant needs watering
  and to send readings to the server
*/
unsigned long pollMillis = 900000; // 15 min


/*
  How dry the soil should get before watering.
  (Max) 1023 = Drier than the Atacama Desert
        400  = Damp
  (Min) 0    = Have you used copper instead of soil?
*/
int waterAtMoisture = 100;

/*
  When the soil gets dry enough to warrant a watering,
  how many millis to open the valve for.
*/
int waterForMillis = 3500;


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
  //  pinMode(moistureOutputPinTop, OUTPUT);
  //  pinMode(moistureOutputPinBottom, OUTPUT);
  pinMode(valveOutputPin, OUTPUT);

  Serial.begin(9600);
  /*
    Serial.begin(9600);

    Ethernet.begin(mac, ip, dns, gateway, submask);

    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
   */


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

  //   postToServer(moisture, watered);
}

/*
  Drives a current though two digital pins
  and reads the resistance through the
  analogue pin
*/
int getSoilMoisture() {
  //Drive a current through the divider in one direction
  //  digitalWrite(moistureOutputPinTop, HIGH);
  //  digitalWrite(moistureOutputPinBottom, LOW);
  //  delay(1000);

  //Take a reading
  int reading = analogRead(moistureInputPin);

  //Reverse the current
  //  digitalWrite(moistureOutputPinTop, LOW);
  //  digitalWrite(moistureOutputPinBottom, HIGH);
  //  delay(1000);

  //Stop the current
  //  digitalWrite(moistureOutputPinBottom, LOW);

  return reading;
}

/*
  Gives the plant a two second blast of water
*/
void waterThePlant() {
  Serial.println ("Watering... ");
  digitalWrite(valveOutputPin, HIGH);
  delay(waterForMillis);
  digitalWrite(valveOutputPin, LOW);
}


