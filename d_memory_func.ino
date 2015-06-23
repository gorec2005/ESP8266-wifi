void LoadParams()
{
  
  if (EEPROM.read(deviceidAddressbyte) == flagvalue) EepromUtil::eeprom_read_string(deviceidAddress, deviceid, BUFSIZE);
  if (EEPROM.read(ssidAddressbyte) == flagvalue) EepromUtil::eeprom_read_string(ssidAddress, ssid , BUFSIZE);
  if (EEPROM.read(passwordAddressbyte) == flagvalue) EepromUtil::eeprom_read_string(passwordAddress, password, BUFSIZE);
  if (EEPROM.read(mqttAddressbyte) == flagvalue) 
  {
    //EepromUtil::eeprom_read_string(mqttAddress, mqttserver, BUFSIZE);
     for (int i=0; i<4; i++) {  // SAVE NEW TO EEPROM
    MQTTserver[i] = EEPROM.read( mqttAddress+i);
   }
   
   mqttserver_string = String(MQTTserver[0]) + "." + String(MQTTserver[1]) + "." + String(MQTTserver[2]) + "." + String(MQTTserver[3]) ; 

   //Serial.print("SAVED MqqttServer: ");
   //Serial.println(mqttserver);
  }
  
  if (EEPROM.read(MQTTenabledbyte) == flagvalue) {
  	MQTT_enabled = true;
  } else {
  	MQTT_enabled = false;
  }





  if (EEPROM.read(DEBUGenabledbyte) != 0) {
  		if (EEPROM.read(DEBUGenabledbyte) == 1) {
  			debug_command("timer");
  		}
  
	} else {
	  	DEBUG = false;

	}

}


void EEPROM_wipe() {

for (int i = 0; i < 512; i++) EEPROM.write(i,0);
EEPROM.commit();
Serial.print("EEPROM WIPED");
delay(100);
}


void Load_LED_Defaults (uint16_t address) {
uint8_t temp,tempb; 

  // START_address_settings = 160; 

// 1 --------------------------------   LAST OP STATE ------------------------
     temp = EEPROM.read(address++);

    if (isnan(temp)) temp = 0;

    LastOpState = (operatingState)temp;
// 2 --------------------------------   Timer ---------------------------------
    
     temp = EEPROM.read(address++);
     tempb = EEPROM.read(address++);
        if(isnan(temp)) temp = 0;
        if(isnan(tempb)) temp = 0;
        WS2812interval = temp*256+tempb;
// 3 --------------------------------  Animation speed -------------------------

     temp = EEPROM.read(address++);
     tempb = EEPROM.read(address++);
        if(isnan(temp)) temp = 0;
        if(isnan(tempb)) temp = 0;
        CurrentAnimationSpeed = temp*256+tempb;

// 4--------------------------------  Brightness -------------------------

        CurrentBrightness = EEPROM.read(address++);
        if (isnan(CurrentBrightness) || CurrentBrightness == 0) CurrentBrightness = 255;

// 5--------------------------------  R G B  -------------------------

      uint8_t R = EEPROM.read(address++);
      uint8_t G = EEPROM.read(address++);
      uint8_t B = EEPROM.read(address++);

      NewColour = RgbColor(R,G,B);

      WebRGBcolour = String(R,HEX);
      WebRGBcolour += String(G,HEX);
      WebRGBcolour += String(B,HEX);
     
// 6--------------------------------  Vars 1 - 10   -------------------------

      var1 = EEPROM.read(address++); 
      var2 = EEPROM.read(address++); 
      var3 = EEPROM.read(address++); 
      var4 = EEPROM.read(address++); 
      var5 = EEPROM.read(address++); 
      var6 = EEPROM.read(address++); 
      var7 = EEPROM.read(address++); 
      var8 = EEPROM.read(address++); 
      var9 = EEPROM.read(address++); 
      var10 = EEPROM.read(address++); 
}





void Save_LED_Defaults (uint16_t address) {

  // START_address_settings = 160; 

// 1 --------------------------------   LAST OP STATE ------------------------
     EEPROM.write(address++, LastOpState);

// 2 --------------------------------   Timer ---------------------------------
    


     EEPROM.write(address++, WS2812interval / 256 );
     EEPROM.write(address++, WS2812interval % 256 );


// 3 --------------------------------  Animation speed -------------------------

     EEPROM.write(address++, CurrentAnimationSpeed / 256 );
     EEPROM.write(address++, CurrentAnimationSpeed % 256 );

// 4--------------------------------  Brightness -------------------------


    EEPROM.write(address++, CurrentBrightness );

// 5--------------------------------  R G B  -------------------------

      EEPROM.write( address++, NewColour.R);
      EEPROM.write(address++, NewColour.G);
      EEPROM.write(address++ , NewColour.B);
     
// 6--------------------------------  Vars 1 - 10   -------------------------

     EEPROM.write(address++, var1);
     EEPROM.write(address++, var2);
     EEPROM.write(address++, var3);
     EEPROM.write(address++, var4);
     EEPROM.write(address++, var5);
     EEPROM.write(address++, var6);
     EEPROM.write(address++, var7);
     EEPROM.write(address++, var8);
     EEPROM.write(address++, var9);
     EEPROM.write(address++, var10);

     EEPROM.commit();

}

