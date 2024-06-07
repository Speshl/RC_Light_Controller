#include "web.h"

DNSServer dnsServer;
AsyncWebServer server(80);

Config webConfig;
Preferences* webPreferences;

String webCfgProcessor(const String& var){
  return String();
}

void SetupWifi(Config cfg){
  webConfig = cfg;
  if (!SPIFFS.begin(true)) {
    Serial.println("an error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.softAPConfig(LOCAL_IP, GATEWAY, SUBNET);
  WiFi.softAP("light-control-config");
  dnsServer.start(53, "lightconfig", WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("web request");
    request->send(SPIFFS, "/web_cfg.htm", String(), false, webCfgProcessor);
  });

  server.on("/loadDefaults", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("resetting to defaults");
    webConfig = GetDefaultConfig();
    request->send(SPIFFS, "/web_cfg.htm", String(), false, webCfgProcessor);
    SaveConfig(webConfig);
    ESP.restart();
  });

  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("POST request received");
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    JsonDocument doc;
    deserializeJson(doc, (const char*)data);
    webConfig = parseConfig(doc);
    request->send(SPIFFS, "/web_cfg.htm", String(), false, webCfgProcessor);
    SaveConfig(webConfig);
    Serial.println("restarting");
    ESP.restart();
  });


  server.begin();
}

Config parseConfig(JsonDocument doc){
  return webConfig;
}

void ProcessWifi(){
  dnsServer.processNextRequest();
}

String inputProcessor(const String& var){
    return "";
}