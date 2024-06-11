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

void buildInputMap();
void buildLevelMaps();
void buildOutputMaps();

String inputProcessor(const String& var);
String level1Processor(const String& var);
String level2Processor(const String& var);
String level3Processor(const String& var);
String out1Processor(const String& var);
String out2Processor(const String& var);
String out3Processor(const String& var);
String out4Processor(const String& var);
String out5Processor(const String& var);
String out6Processor(const String& var);
String out7Processor(const String& var);
String out8Processor(const String& var);
String out9Processor(const String& var);
String out10Processor(const String& var);
String out11Processor(const String& var);
String out12Processor(const String& var);

Config parseInputConfig(JsonDocument doc);
Config parseLevelConfig(JsonDocument doc);
Config parseOutConfig(JsonDocument doc);

void SetupWifi(Config cfg);
void ProcessWifi();
bool IsActiveWebClient();
String webCfgProcessor(const String& var);
Config parseConfig(JsonDocument doc);

#endif