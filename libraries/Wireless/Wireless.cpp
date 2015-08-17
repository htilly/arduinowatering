/*
Wireless.cpp
Version 1.01
See Wireless.h for more info.
*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Wireless.h"

SoftwareSerial *Module;


//Tilly mod
// int _enable;
// int _reset;

/*Constructor
Enable and reset pins are defined and set to a known state.
Sets up SoftwareSerial for communication with the module.
*/

//Tilly mod
// Wireless::Wireless(int RXpin, int TXpin, int enablepin, int resetpin) {
   Wireless::Wireless(int RXpin, int TXpin) {
//Tilly mod
//  _enable = enablepin; 
//  _reset = resetpin; 
//Tilly mod
//	pinMode(_enable, OUTPUT);
//	pinMode(_reset, OUTPUT);

//	digitalWrite(_enable, HIGH);
//	digitalWrite(_reset, HIGH);
  Module = new SoftwareSerial(RXpin,TXpin);
  Module->begin(9600);
}

/*
Connects to a Access Point.
The modules will automatically reconnect to the last AP used on power on.
*/
void Wireless::connectToAP(String APSSID, String key) {
  String outString = "";
  outString = outString + "AT+CWJAP=\"" + APSSID + "\",\"" + key + "\"";
  	  delay(1000);
  Module->println("AT+CWMODE=1"); //Client mode.
  Module->println(outString); //Connect to AP
}

/* 
Disconnect from Access Point
*/
void Wireless::disconnectAP() {
  Module->println("AT+CWQAP"); //Disconnects from AccessPoint 
}

/*
Sets up the module to function as a Access Point.
Uses WPA encryption.
*/
void Wireless::createAP(String APSSID, String key, int channel) {
  //TODO: Verify start AP command.
  String outString = "";
  outString = outString + "AT+CWSAP=\"" + APSSID + "\",\"" + key + "\",\"" + channel + ",\"WPA\"";
    delay(1000);
  Module->println("AT+CWMODE=2"); //AP mode.
  Module->println(outString); //Start AP
}

/*
Opens a connection to a server.
*/
void Wireless::connectToServer(String IP, int port) {
  Module->println("AT+CIPMUX=0"); //Single connection mode. Required for connecting to a server.
  	delay(4000);
  String connectString = "";
   delay(4000);
  connectString = connectString + "AT+CIPSTART=\"TCP\",\"" + IP + "\"," + port;
   delay(4000);
  Module->println(connectString);
}

/*
Closes a connection to a server.
*/
void Wireless::disconnectFromServer() {
  Module->println("AT+CIPCLOSE");
}

/*
Sends a string of data to the connected server.
Example: sendDataToServer("GET /index.html");
*/
void Wireless::sendDataToServer(String data) {
  String outString = "AT+CIPSEND=";
   delay(4000);
  outString = outString + data.length(); 
   delay(4000);
  Module->println(outString); //Tells the module to expect a string of a specific length for sending.
   delay(4000);
  Module->print(data); //Send the actual string to the server
}

/*
Sends data to a client connected when the module if functioning as a server.
*/
void Wireless::sendDataToClient(String data, int client) {
  String outString = "AT+CIPSEND=";
  outString = outString + client + "," + data.length();
  Module->println(outString); //Tells the module to expect a string of a specific length for sending to the specified client.
  Module->println(data); //Send the actual string to the client.
}

/*
The module will output it's IP address. (0.0.0.0 if no IP)
*/
void Wireless::getIP() {
  Module->println("AT+CIFSR"); //Module will output it's IP address.
}

/*
Starts server. The module will listen for connections.
*/
void Wireless::startServer(int port) {
  Module->println("AT+CIPMUX=1"); //Enable multiple connections. Required to start a server.
  	  delay(1000);
  String outString = "AT+CIPSERVER=1,";
  outString = outString + port; 
  Module->println(outString); //Connect to the server
}

/*
Stops server and restarts the module. (The restart is required after stopping the server.)
*/
void Wireless::stopServer() {
  Module->println("AT+CIPSERVER=0"); //Stop server
  softReset(); //Restart module. Required after stopping the server.
}

/*
Resets the module. 
*/
void Wireless::softReset() {
  Module->println("AT+RST"); //Restart module.
}

/*
The module will return the connection status.
*/
void Wireless::getStatus() {
  Module->println("AT+CIPSTATUS");
}

/*
Performs a hardware reset of the module.
Not normally needed. Use softReset() instead for restarting the module.
*/
//Tilly mod
//void Wireless::hardReset() {
//  digitalWrite(_reset, LOW); //Pull reset pin low
//  delay(1000); 
//  digitalWrite(_reset, HIGH);  //Pull high to start module again
//}

/*
Enables the module.
*/

//Tilly mod
//void Wireless::enable() {
//  digitalWrite(_enable, HIGH);
//}

/*
Disables the module.
It will draw very little current but will not respond to any commands.
*/

//Tilly mod
//void Wireless::disable() {
//  digitalWrite(_enable, LOW);
//}

/*
Reads a character from the module.
*/
int Wireless::readChar() {
	return Module->read();
}

/*
Returns true if any data is available.
*/
int Wireless::available() {
	return Module->available();
}
