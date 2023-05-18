void GetTime(bool setRTC)
{
   // Set WiFi to station mode and disconnect from an AP if it was previously connected
    
  String errormessage ="";
  
  //scan for networks
  if(scan_for_network(errormessage) == true)
  {
    Serial.println("m1: Network " + String(ssid) + " found");
    
    if(connect_to_network() == true)
    {
      Serial.println("m2: connected to network");
      
      if(SetTime(setRTC) == true)
      {
        WiFi.disconnect();
        Serial.println("m5: Time has been set.");
      }
      else
      {
        Serial.println("e1: Time could not be set.");
      }
    }
    else
    {
      Serial.println("e2: networkname found, no connection could be established. Wrong password?");
    }
  }
  else
  {
     Serial.println("e3:" + errormessage);
  }

}

//set the RTC / serial print current time
boolean SetTime(bool setRTC)
{
  //get time from upd
  Udp.begin(localPort);
  setSyncProvider(getNtpTime);

  boolean exit_loop =false;
  int counter =0;
  
  while((exit_loop == false) && (counter <=100))
  {
    
    setSyncProvider(getNtpTime);
    if(timeStatus() != timeNotSet)
    {
      //set clock
      int y = (int) year();
      byte mo = (byte) month();
      byte d = (byte) day();        
      byte h = (byte) hour();
      byte m = (byte) minute();
      byte s = (byte) second();
      
      if(summertime_EU((int) year(), (byte) month(), (byte) day(), h, (byte) timeZone))
      {
        h +=1; //DST
      }

      if(setRTC == true)
      {
        Clock.setSecond(s);
        Clock.setMinute(m);
        Clock.setHour(h);
        
        //Clock.setClockMode(false);  // set to 24h; true = 12h
        Clock.setYear(y);
        Clock.setMonth(mo);
        Clock.setDate(d);
      }
      
      Serial.print("ye_");
      Serial.println(y);
      Serial.print("mo_");
      Serial.println(m);
      Serial.print("da_");
      Serial.println(d);

      Serial.print("ho_");
      Serial.println((int) h);
      Serial.print("mi_");
      Serial.println((int) m);
      Serial.print("se_");
      Serial.println((int) s);
      
      exit_loop = true;
      
      //return true if successful
      return true;

    }
    counter +=1;
  }
  return exit_loop;
}


/* 
 *  European Daylight Savings Time calculation
 *  input parameters: "normal time" for year, month, day, hour and tzHours (0=UTC, 1=MEZ)
 *  return value: returns true during Daylight Saving Time, false otherwise
 */
boolean summertime_EU(int year, byte month, byte day, byte hour, byte tzHours)
{
 if (month<3 || month>10) return false; // no DST in Jan, Feb, Nov, Dez
 if (month>3 && month<10) return true; // DST in Apr, Mai, Jun, Jul, Aug, Sep
 if (month==3 && (hour + 24 * day)>=(1 + tzHours + 24*(31 - (5 * year /4 + 4) % 7)) || month==10 && (hour + 24 * day)<(1 + tzHours + 24*(31 - (5 * year /4 + 1) % 7)))
   return true;
 else
   return false;
}
