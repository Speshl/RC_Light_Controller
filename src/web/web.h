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

enum ProcessorType {
    INPUT_PROCESSOR,
    LEVEL_PROCESSOR,
    OUTPUT_BASE_PROCESSOR,
    OUTPUT_ROLE_PROCESSOR,
    OUTPUT_STRIP_PROCESSOR,
    OUTPUT_UNDERGLOW_PROCESSOR,
    OUTPUT_THROTTLE_BRAKE_PROCESSOR,
    OUTPUT_EXHAUST_PROCESSOR,
    OUTPUT_EMERGENCY_PROCESSOR
};

#define LOCAL_IP IPAddress(192, 168, 4, 20)
#define GATEWAY IPAddress(192, 168, 4, 20)
#define SUBNET IPAddress(255, 255, 255, 0)

void buildMaps(Config* webConfig);

std::function<String(const String&)> createProcessor(int idx, ProcessorType type);
std::function<String(const String&)> createDefaultProcessor();

void SetupWifi(Config cfg);
void ProcessWifi();
bool IsActiveWebClient();
String webCfgProcessor(const String& var);
Config parseConfig(JsonDocument doc);

#endif