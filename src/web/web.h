#ifndef WEB_CFG_H
#define WEB_CFG_H
#include <map>
#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include <SPIFFS.h>
#include "Arduino.h"
#include <ArduinoJson.h>
#include "../config/config.h"

#define LOCAL_IP IPAddress(192, 168, 4, 20)
#define GATEWAY IPAddress(192, 168, 4, 20)
#define SUBNET IPAddress(255, 255, 255, 0)

void buildMaps(Config* webConfig);

String inputProcessor(const String& var);
std::function<String(const String&)> createLevelProcessor(int level);
std::function<String(const String&)> createOutputProcessor(int output);

void SetupWifi(Config cfg);
void ProcessWifi();
bool IsActiveWebClient();
String webCfgProcessor(const String& var);
Config parseConfig(JsonDocument doc);

#endif