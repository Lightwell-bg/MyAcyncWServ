#include <Arduino.h>

#include "config.h" 
#include "configFile.h"
#include "WIFI-SSDP.h"
#include "timeFunc.h" 
#include "firmWareUpd.h"
#include "httpServer.h" 



void setup() {
    Serial.begin(115200);
    char host[16];
#ifdef ESP8266
    snprintf(host, 12, "ESP%08X", ESP.getChipId());
#else
    snprintf(host, 16, "ESP%012llX", ESP.getEfuseMac());
#endif  
    // Initialize SPIFFS
    if(!SPIFFS.begin()) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    } 
    loadConfig(); Serial.println(F("FileConfig init"));
    init_WIFI(); Serial.println(F("Wi-Fi init"));
    //init_SSDP(); Serial.println(F("SSDP init"));
    //MDNS.begin(host);
    //MDNS.addService("http", "tcp", 80);
    Serial.printf("Ready! Open http://%s.local in your browser\n", host); 
    init_Time(); Serial.println(F("Start Time"));  
    init_firmWareUpdate(); Serial.println(F("Start init FirmWare update")); 
    init_HTTPServer(); Serial.println(F("HTTPServer init"));
}

void loop() {
  
}