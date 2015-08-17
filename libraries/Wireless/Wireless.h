/*
Wireless.h - Library for Wireless networking using the 8266Wing WiFi shield
Created by Emil Johnsen, December 2014 - January 2015.
Released into the public domain.
  
Contact information: www.zeptobit.com emil@zeptobit.com
	
This is version 1.01 of this library.

This is an early release. It does not include all planned functionality, but
all included code is fully functional. (Any partially finished or buggy 
functionality has been removed from this release.)
*/

#ifndef Wireless_h
#define Wireless_h
#include <Arduino.h>
#include <SoftwareSerial.h>

class Wireless {
  public:
  
  //Tilly mod
 //   Wireless(int RX, int TX, int enable, int reset);
 Wireless(int RX, int TX);
    void connectToAP(String APSSID, String key);
    void disconnectAP();
    void createAP(String APSSID, String key, int channel);
    void connectToServer(String IP, int port);
    void disconnectFromServer();
    void sendDataToServer(String data);
    void sendDataToClient(String data, int client);
    void getIP();
    void startServer(int port);
    void softReset();
    void stopServer();
    void getStatus();
    void hardReset();
    void enable();
    void disable();
	int readChar();
	int available();
    
  private:
    int _pin;
    SoftwareSerial *Module;
    int _enable;
    int _reset;
    
};

#endif
