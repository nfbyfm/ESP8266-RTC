# ESP8266-RTC
 Arduino-sketch for ESP8266-based boards for setting the Time of a DS3231-Module via NTP / WiFi

## Usage

Connect the DS3231-Module to your ESP8266-based board. In case of a Wemos mini it should look like this:

![Example Wemos mini and DS3231](https://raw.githubusercontent.com/nfbyfm/ESP8266-RTC/master/doc/Example_Wemos_RTC.jpg)

Afterwards you have to enter the ssid and password of your WiFi-router in the sketch, compile and then upload the code.

Make sure you have all the necessary libraries installed. 

The code might not work if the NTP-Server can't be reached. In that case try another IP-adress;
