boolean scan_for_network(String& errormessage)
{
  boolean found = false;
  //scan networks, look for hardcoded ssid
  String result ="";

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  
  if (n == 0)
  {
      result = "no networks found\n";
      found=false;
  }
  else
  {
    result += "network-SSID '";
    result += ssid;
    result += "' could not be found.\n found networks: \n\n";
    
    for (int i = 0; i < n; ++i)
    {
      //search for SSID for each network found
      if(WiFi.SSID(i) == ssid)
      {
        errormessage="";
        found=true;
        break;
      }
      else
      {
        result += String(i+1) + ": " + WiFi.SSID(i) + "\n";
      }
    }
  }
  errormessage = result;
  return found;
}

boolean connect_to_network()
{
  boolean connected_to_wlan = false;
  //try to connect to hardcoded ssid, return false if not possible to

  WiFi.begin(ssid, password);

  int counter =0;
  int max_timeout = 100;
  // Wait for connection
  while ((WiFi.status() != WL_CONNECTED) && (counter <= max_timeout)) 
  {
    delay(500);
    //Serial.print(".");
    counter +=1;
  }

  if(counter >= max_timeout)
  {
    connected_to_wlan = false;
  }
  else
  {
    if(WiFi.status() == WL_CONNECTED)
    {
      connected_to_wlan=true;
    }
    else
    {
      connected_to_wlan=false;
    }
  }
  return connected_to_wlan;
}
