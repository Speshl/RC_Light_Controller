#include "web.h"

DNSServer dnsServer;
AsyncWebServer server(80);

Config webConfig;

std::map<String, String> inputMap;
std::array<std::map<String, String>, NUM_LEVELS> levelsMap;
std::array<std::map<String, String>, MAX_CHANNELS> outputsMap;

bool clientDetected = false;

void WiFiEvent(WiFiEvent_t event) {
    switch(event) {
        case SYSTEM_EVENT_AP_STACONNECTED:
            Serial.println("A client has connected to the ESP32's WiFi.");
            clientDetected = true;
            break;
        case SYSTEM_EVENT_AP_STADISCONNECTED:
            Serial.println("A client has disconnected from the ESP32's WiFi.");
            clientDetected = false;
            break;
    }
}

void SetupWifi(Config cfg){
  webConfig = cfg;
  if (!SPIFFS.begin(true)) {
    Serial.println("an error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.softAPConfig(LOCAL_IP, GATEWAY, SUBNET);
  WiFi.softAP("light-control-config");
  WiFi.onEvent(WiFiEvent);

  dnsServer.start(53, "lightconfig", WiFi.softAPIP());

  buildInputMap();
  buildLevelMaps();
  buildOutputMaps();

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("sending JS");
    clientDetected = true;
    request->send(SPIFFS, "/web_cfg.js", "text/javascript");
  });

  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("sending CSS");
    clientDetected = true;
    request->send(SPIFFS, "/web_cfg.css", "text/css");
  });

  server.on("/htmx.js", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("sending htmx.js");
    clientDetected = true;
    request->send(SPIFFS, "/htmx.js", "text/javascript");
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing redesign page");
    clientDetected = true;
    request->send(SPIFFS, "/web_cfg.htm", String(), false, inputProcessor);
  });

  server.on("/input.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing input page");
    clientDetected = true;
    request->send(SPIFFS, "/input.htm", String(), false, inputProcessor);
  });

  server.on("/levels.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing levels page");
    clientDetected = true;
    request->send(SPIFFS, "/levels.htm", String(), false, level1Processor);
  });

  server.on("/level1.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing level1 page");
    clientDetected = true;
    request->send(SPIFFS, "/level.htm", String(), false, level1Processor);
  });

  server.on("/level2.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing level2 page");
    clientDetected = true;
    request->send(SPIFFS, "/level.htm", String(), false, level2Processor);
  });

  server.on("/level3.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing level3 page");
    clientDetected = true;
    request->send(SPIFFS, "/level.htm", String(), false, level3Processor);
  });

  server.on("/outputs.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output page");
    clientDetected = true;
    request->send(SPIFFS, "/outputs.htm", String(), false, out1Processor);
  });

  server.on("/output1.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output1 page");
    clientDetected = true;
    request->send(SPIFFS, "/output.htm", String(), false, out1Processor);
  });

  server.on("/output2.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output2 page");
    clientDetected = true;
    request->send(SPIFFS, "/output.htm", String(), false, out2Processor);
  });

  server.on("/output3.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output3 page");
    clientDetected = true;
    request->send(SPIFFS, "/output.htm", String(), false, out3Processor);
  });

  server.on("/output4.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output4 page");   
    clientDetected = true;
    request->send(SPIFFS, "/output.htm", String(), false, out4Processor);
  });

  server.on("/output5.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output5 page");
    clientDetected = true;
    request->send(SPIFFS, "/output.htm", String(), false, out5Processor);
  });

  server.on("/output6.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output6 page");
    clientDetected = true;
    request->send(SPIFFS, "/output.htm", String(), false, out6Processor);
  });

  server.on("/output7.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output7 page");
    clientDetected = true;
    request->send(SPIFFS, "/output.htm", String(), false, out7Processor);
  });

  server.on("/output8.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output8 page");
    clientDetected = true;
    request->send(SPIFFS, "/output.htm", String(), false, out8Processor);
  });

  server.on("/output9.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output9 page");
    clientDetected = true;
    request->send(SPIFFS, "/output.htm", String(), false, out9Processor);
  });

  server.on("/output10.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output10 page");
    clientDetected = true;
    request->send(SPIFFS, "/output.htm", String(), false, out10Processor);
  });

  server.on("/output11.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output11 page");
    clientDetected = true;
    request->send(SPIFFS, "/output.htm", String(), false, out11Processor);
  });
  
  server.on("/output12.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output12 page");
    clientDetected = true;
    request->send(SPIFFS, "/output.htm", String(), false, out12Processor);
  });

  server.on("/loadDefaults", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("resetting to defaults");
    clientDetected = true;
    webConfig = GetDefaultConfig();
    request->send(200);
    SaveConfigWithRestart(webConfig);
  });

  //post requests
   server.on("/input", HTTP_POST, [](AsyncWebServerRequest *request){
    //Serial.println("POST request received");
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    // for (size_t i = 0; i < len; i++) {
    //   Serial.write(data[i]);
    // }

    clientDetected = true;
    JsonDocument doc;
    deserializeJson(doc, (const char*)data);
    parseInputConfig(&webConfig, doc);
    request->send(200);
    SaveConfigWithRestart(webConfig);
  });

  server.on("/level", HTTP_POST, [](AsyncWebServerRequest *request){
    //Serial.println("POST request received");
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    // for (size_t i = 0; i < len; i++) {
    //   Serial.write(data[i]);
    // }

    clientDetected = true;
    JsonDocument doc;
    deserializeJson(doc, (const char*)data);
    parseLevelConfig(&webConfig, doc);
    request->send(200);
    SaveConfigWithRestart(webConfig);
  });

  server.on("/output", HTTP_POST, [](AsyncWebServerRequest *request){
    //Serial.println("POST request received");
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    // for (size_t i = 0; i < len; i++) {
    //   Serial.write(data[i]);
    // }

    clientDetected = true;
    JsonDocument doc;
    deserializeJson(doc, (const char*)data);
    parseOutConfig(&webConfig, doc);
    request->send(200);
    SaveConfigWithRestart(webConfig);
  });

  server.on("/recover", HTTP_GET, [](AsyncWebServerRequest *request){
    clientDetected = true;
    Serial.println("recovering to defaults");
    request->send(SPIFFS, "/recover.htm", String(), false, inputProcessor);
    webConfig = GetDefaultConfig();
    SaveConfigWithRestart(webConfig);
  });

  server.on("/loadDefaults", HTTP_POST, [](AsyncWebServerRequest *request){
    clientDetected = true;
    Serial.println("resetting to defaults");
    webConfig = GetDefaultConfig();
    request->send(SPIFFS, "/web_cfg.htm", String(), false, inputProcessor);
    SaveConfigWithRestart(webConfig);
  });

  server.on("/powerCycle", HTTP_GET, [](AsyncWebServerRequest *request){
    clientDetected = true;
    Serial.println("power cycling");
    request->send(200);
    webConfig.sysConfig.forcedShutdown = false;
    ESP.restart();
  });

  server.on("/export", HTTP_GET, [](AsyncWebServerRequest *request){
    clientDetected = true;
    Serial.println("exporting config");
    JsonDocument doc = ConfigToJson(&webConfig);
    
  });

  server.on("/import", HTTP_POST, [](AsyncWebServerRequest *request){
    //Serial.println("POST request received");
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    // for (size_t i = 0; i < len; i++) {
    //   Serial.write(data[i]);
    // }

    clientDetected = true;
    Serial.println("importing config");
    JsonDocument doc;
    deserializeJson(doc, (const char*)data);
    parseConfig(doc);
    request->send(200);
    SaveConfigWithRestart(webConfig);
  });

  server.begin();
}

void ProcessWifi(){
  dnsServer.processNextRequest();
}

bool IsActiveWebClient(){
  return clientDetected;
}