#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <DS3231.h>

const char *ssid = "";
const char *password ="";

// NTP Servers:
IPAddress timeServer(192, 53, 103, 108 );  
// IPAddress timeServer(193,92,150,3);
// IPAddress timeServer(129,6,15,30); // time-a.timefreq.bldrdoc.gov
// IPAddress timeServer(132, 163, 4, 102); // time-b.timefreq.bldrdoc.gov
// IPAddress timeServer(132, 163, 4, 103); // time-c.timefreq.bldrdoc.gov

WiFiUDP Udp; // A UDP instance to let us send and receive packets over UDP
unsigned int localPort = 8888;      // local port to listen for UDP packets

const int timeZone = 1;     // Central European Time
//const int timeZone = -5;  // Eastern Standard Time (USA)
//const int timeZone = -4;  // Eastern Daylight Time (USA)
//const int timeZone = -8;  // Pacific Standard Time (USA)
//const int timeZone = -7;  // Pacific Daylight Time (USA)

String incomingString;
boolean stringReady;

//Object representing the RTC-Module
DS3231 Clock;


void setup()
{
  Serial.begin(115200);

  GetTime(true);
}

void loop()
{
  incomingString="";
  stringReady = false;
  
  //wait for command given via serial
  while(Serial.available())
  {
    incomingString = Serial.readString();
    stringReady = true;
  }
  
  if(stringReady)
  {
    Serial.println("ack: " + incomingString);
    
    if(incomingString == "g")
    {
      //get the current time without setting the RTC
      GetTime(false);
    }
    else if(incomingString == "s")
    {
      //get the current time and set the RTC
      GetTime(true);
    }
    else if(incomingString == "h")
    {
      Serial.println("ESP8266-Module for getting current Time via NTP.");
      Serial.println("'g' triggers GetTime-Function.");
      Serial.println("'s' gets current time and sets the RTC.");
      Serial.println("'h' this Info-Text.");
    }
  }
}
