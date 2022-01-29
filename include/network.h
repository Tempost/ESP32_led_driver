#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

class Network {
    // Replace with your network credentials
    const char* ssid = "Diamond Home 2";
    const char* password = "";
 
    static String processor(const String& var);

public:
    // Stores LED state
    static String ledState;
    String getLEDState();
    void setLEDState();
    void init();
}

#endif NETWORK_H
