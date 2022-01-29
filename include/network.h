#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

String processor(const String& var);

void init_network();

#endif
