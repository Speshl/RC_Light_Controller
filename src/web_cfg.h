#ifndef WEB_CFG_H
#define WEB_CFG_H
#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <SPIFFS.h>
#include "Arduino.h"
#include <ArduinoJson.h>
#include "config.h"
#include "storage.h"

#define LOCAL_IP IPAddress(192, 168, 4, 20)
#define GATEWAY IPAddress(192, 168, 4, 20)
#define SUBNET IPAddress(255, 255, 255, 0)

void SetupWifi(Preferences* preferences, Config cfg);
void ProcessWifi();
String webCfgProcessor(const String& var);
Config parseConfig(JsonDocument doc);

#endif