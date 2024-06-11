#include "web.h"

DNSServer dnsServer;
AsyncWebServer server(80);

Config webConfig;

std::map<String, String> inputMap;
std::array<std::map<String, String>, NUM_LEVELS> levelsMap;
std::array<std::map<String, String>, MAX_CHANNELS> outputsMap;

unsigned long webBusyUntilTime=0;

void addBusyTime(unsigned long time){
  if(webBusyUntilTime < millis()){
    webBusyUntilTime = millis() + time;
  }else{
    webBusyUntilTime += time;
  }
}

void WiFiEvent(WiFiEvent_t event) {
    switch(event) {
        case SYSTEM_EVENT_AP_STACONNECTED:
            Serial.println("A client has connected to the ESP32's WiFi.");
            addBusyTime(30000);
            break;
        case SYSTEM_EVENT_AP_STADISCONNECTED:
            Serial.println("A client has disconnected from the ESP32's WiFi.");
            webBusyUntilTime = millis();
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

  //buildConfigMap();
  buildInputMap();
  buildLevelMaps();
  buildOutputMaps();

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("sending JS");
    addBusyTime(5000);
    request->send(SPIFFS, "/web_cfg.js", "text/javascript");
  });

  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("sending CSS");
    addBusyTime(5000);
    request->send(SPIFFS, "/web_cfg.css", "text/css");
  });

  server.on("/htmx.js", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("sending htmx.js");
    addBusyTime(5000);
    request->send(SPIFFS, "/htmx.js", "text/javascript");
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing redesign page");
    addBusyTime(5000);
    request->send(SPIFFS, "/web_cfg.htm", String(), false, inputProcessor);
  });

  server.on("/input.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing input page");
    addBusyTime(5000);
    request->send(SPIFFS, "/input.htm", String(), false, inputProcessor);
  });

  server.on("/levels.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing levels page");
    addBusyTime(5000);
    request->send(SPIFFS, "/levels.htm", String(), false, level1Processor);
  });

  server.on("/level1.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing level1 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/level.htm", String(), false, level1Processor);
  });

  server.on("/level2.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing level2 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/level.htm", String(), false, level2Processor);
  });

  server.on("/level3.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing level3 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/level.htm", String(), false, level3Processor);
  });

  server.on("/outputs.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output page");
    addBusyTime(5000);
    request->send(SPIFFS, "/outputs.htm", String(), false, out1Processor);
  });

  server.on("/output1.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output1 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/output.htm", String(), false, out1Processor);
  });

  server.on("/output2.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output2 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/output.htm", String(), false, out2Processor);
  });

  server.on("/output3.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output3 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/output.htm", String(), false, out3Processor);
  });

  server.on("/output4.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output4 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/output.htm", String(), false, out4Processor);
  });

  server.on("/output5.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output5 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/output.htm", String(), false, out5Processor);
  });

  server.on("/output6.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output6 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/output.htm", String(), false, out6Processor);
  });

  server.on("/output7.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output7 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/output.htm", String(), false, out7Processor);
  });

  server.on("/output8.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output8 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/output.htm", String(), false, out8Processor);
  });

  server.on("/output9.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output9 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/output.htm", String(), false, out9Processor);
  });

  server.on("/output10.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output10 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/output.htm", String(), false, out10Processor);
  });

  server.on("/output11.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output11 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/output.htm", String(), false, out11Processor);
  });
  
  server.on("/output12.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing output12 page");
    addBusyTime(5000);
    request->send(SPIFFS, "/output.htm", String(), false, out12Processor);
  });

  server.on("/loadDefaults", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("resetting to defaults");
    webConfig = GetDefaultConfig();
    request->send(200);
    SaveConfig(webConfig);
    ESP.restart();
  });

  //post requests
   server.on("/input", HTTP_POST, [](AsyncWebServerRequest *request){
    //Serial.println("POST request received");
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    // for (size_t i = 0; i < len; i++) {
    //   Serial.write(data[i]);
    // }

    JsonDocument doc;
    deserializeJson(doc, (const char*)data);
    webConfig = parseInputConfig(doc);
    request->send(200);
    SaveConfig(webConfig);
    Serial.println("restarting");
    ESP.restart();
  });

  server.on("/level", HTTP_POST, [](AsyncWebServerRequest *request){
    //Serial.println("POST request received");
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    // for (size_t i = 0; i < len; i++) {
    //   Serial.write(data[i]);
    // }

    JsonDocument doc;
    deserializeJson(doc, (const char*)data);
    webConfig = parseLevelConfig(doc);
    request->send(200);
    SaveConfig(webConfig);
    Serial.println("restarting");
    ESP.restart();
  });

  server.on("/output", HTTP_POST, [](AsyncWebServerRequest *request){
    //Serial.println("POST request received");
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    // for (size_t i = 0; i < len; i++) {
    //   Serial.write(data[i]);
    // }

    JsonDocument doc;
    deserializeJson(doc, (const char*)data);
    webConfig = parseOutConfig(doc);
    request->send(200);
    SaveConfig(webConfig);
    Serial.println("restarting");
    ESP.restart();
  });


  //old endpoints below
  // server.on("/recover", HTTP_GET, [](AsyncWebServerRequest *request){
  //   Serial.println("web request");
  //   webConfig = GetDefaultConfig();
  //   request->send(SPIFFS, "/recover.htm", String(), false, webCfgMapProcessor); //TODO: Make simple recovery page
  //   SaveConfig(webConfig);
  //   Serial.println("restarting");
  //   ESP.restart();
  // });

  server.on("/loadDefaults", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("resetting to defaults");
    webConfig = GetDefaultConfig();
    request->send(SPIFFS, "/web_cfg.htm", String(), false, inputProcessor);
    SaveConfig(webConfig);
    Serial.println("restarting");
    ESP.restart();
  });

  server.begin();
}

void ProcessWifi(){
  dnsServer.processNextRequest();
}

bool IsActiveWebClient(){
  return webBusyUntilTime > millis();
}