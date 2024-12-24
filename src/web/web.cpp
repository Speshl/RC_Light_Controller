#include "web.h"

DNSServer dnsServer;
AsyncWebServer server(80);

Config webConfig;

bool clientDetected = false;

String inputDataBuffer;

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

void ProcessWifi(){
  dnsServer.processNextRequest();
}

bool IsActiveWebClient(){
  return clientDetected;
}

void SetupWifi(Config cfg){
  webConfig = cfg;
  if (!SPIFFS.begin(true)) {
    Serial.println("an error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.softAPConfig(LOCAL_IP, GATEWAY, SUBNET);
  WiFi.softAP("RCLC-Config");
  WiFi.onEvent(WiFiEvent);

  dnsServer.start(53, "rclcconfig", WiFi.softAPIP());

  buildMaps(&webConfig);

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("sending JS");
    clientDetected = true;
    request->send(SPIFFS, "/web/shared/web_cfg.js", "text/javascript");
  });

  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("sending CSS");
    clientDetected = true;
    request->send(SPIFFS, "/web/shared/web_cfg.css", "text/css");
  });

  server.on("/htmx.js", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("sending htmx.js");
    clientDetected = true;
    request->send(SPIFFS, "/web/shared/htmx.js", "text/javascript");
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing redesign page");
    clientDetected = true;
    request->send(SPIFFS, "/web/shared/web_cfg.htm", String(), false, createDefaultProcessor());
  });

  server.on("/input.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing input page");
    clientDetected = true;
    request->send(SPIFFS, "/web/input/input.htm", String(), false, createProcessor(0, INPUT_PROCESSOR));
  });

  server.on("/outputs.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing input page");
    clientDetected = true;
    request->send(SPIFFS, "/web/outputs/outputs.htm", String(), false, createProcessor(0, OUTPUT_BASE_PROCESSOR));
  });

  server.on("/levels.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing input page");
    clientDetected = true;
    request->send(SPIFFS, "/web/levels/levels.htm", String(), false, createProcessor(0, LEVEL_PROCESSOR));
  });

  for(int i = 0; i < NUM_LEVELS; i++){
    String path = "/level" + String(i + 1) + ".htm";
    server.on(path.c_str(), HTTP_GET, [i](AsyncWebServerRequest *request){
      //Serial.println("showing level" + String(i + 1) + " page");
      clientDetected = true;
      request->send(SPIFFS, "/web/levels/level.htm", String(), false, createProcessor(i, LEVEL_PROCESSOR));
    });
  }

  for(int i = 0; i < MAX_CHANNELS; i++){
    String path = "/output" + String(i + 1) + ".htm";
    server.on(path.c_str(), HTTP_GET, [i](AsyncWebServerRequest *request){
      //Serial.println("showing output" + String(i + 1) + " page");
      clientDetected = true;
      request->send(SPIFFS, "/web/outputs/base_output.htm", String(), false, createProcessor(i, OUTPUT_BASE_PROCESSOR));
    });
  }

  for(int i = 0; i < MAX_CHANNELS; i++){
    String path = "/outputType" + String(i + 1) + ".htm";
    server.on(path.c_str(), HTTP_GET, [i](AsyncWebServerRequest *request){
      clientDetected = true;
      //Serial.println("showing output" + String(i + 1) + " page");

      String paramValue = "single";
      if (request->hasParam("out_type")) {
        paramValue = request->getParam("out_type")->value();
      }
      
      if (paramValue != "strip") {
        request->send(SPIFFS, "/web/outputs/role_output.htm", String(), false, createProcessor(i, OUTPUT_ROLE_PROCESSOR));
      }else{
        request->send(SPIFFS, "/web/outputs/strip_output.htm", String(), false, createProcessor(i, OUTPUT_STRIP_PROCESSOR));
      }  
    });
  }

  for(int i = 0; i < MAX_CHANNELS; i++){
    String path = "/outputAnimation" + String(i + 1) + ".htm";
    server.on(path.c_str(), HTTP_GET, [i](AsyncWebServerRequest *request){
      clientDetected = true;
      //Serial.println("showing output" + String(i + 1) + " page");

      String paramValue = "underglow";
      if (request->hasParam("out_animation")) {
        paramValue = request->getParam("out_animation")->value();
      }

      switch(GetStripAnimationFromString(paramValue.c_str())){
        case UNDERGLOW:
          request->send(SPIFFS, "/web/anim/underglow.htm", String(), false, createProcessor(i, OUTPUT_UNDERGLOW_PROCESSOR));
          break;
        case THROTTLE_BRAKE:
          request->send(SPIFFS, "/web/anim/throttle_brake.htm", String(), false, createProcessor(i, OUTPUT_THROTTLE_BRAKE_PROCESSOR));
          break;
        case EXHAUST:
          request->send(SPIFFS, "/web/anim/exhaust.htm", String(), false, createProcessor(i, OUTPUT_EXHAUST_PROCESSOR));
          break;
        case EMERGENCY:
          request->send(SPIFFS, "/web/anim/emergency.htm", String(), false, createProcessor(i, OUTPUT_EMERGENCY_PROCESSOR));
          break;
      }
    });
  }

  server.on("/utility.htm", HTTP_GET, [](AsyncWebServerRequest *request){
    //Serial.println("showing utility page");
    clientDetected = true;
    request->send(SPIFFS, "/web/utility/utility.htm", String(), false, createDefaultProcessor());
  });

  server.on("/loadDefaults", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("resetting to defaults");
    clientDetected = true;
    webConfig = GetDefaultConfig();
    SaveConfig(webConfig);
    buildMaps(&webConfig);
    request->send(200);
    SaveConfigWithRestart(webConfig);
  });

  //post requests
   server.on("/input", HTTP_POST, [](AsyncWebServerRequest *request){
    //Serial.println("POST request received");
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {

    clientDetected = true;
    JsonDocument doc;
    deserializeJson(doc, (const char*)data);
    parseInputConfig(&webConfig, doc);
    SaveConfig(webConfig);
    buildMaps(&webConfig);
    request->send(200);
    //SaveConfigWithRestart(webConfig);
  });

  server.on("/level", HTTP_POST, [](AsyncWebServerRequest *request){
    //Serial.println("POST request received");
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) { 

    clientDetected = true;
    JsonDocument doc;
    deserializeJson(doc, (const char*)data);
    parseLevelConfig(&webConfig, doc);
    SaveConfig(webConfig);
    buildMaps(&webConfig);
    request->send(200);
    //SaveConfigWithRestart(webConfig);
  });

  server.on("/output", HTTP_POST, [](AsyncWebServerRequest *request){
    //Serial.println("POST request received");
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {

    clientDetected = true;
    JsonDocument doc;
    deserializeJson(doc, (const char*)data);
    parseOutConfig(&webConfig, doc, true);
    SaveConfig(webConfig);
    buildMaps(&webConfig);
    request->send(200);
    //SaveConfigWithRestart(webConfig);
  });

  server.on("/recover", HTTP_GET, [](AsyncWebServerRequest *request){
    clientDetected = true;
    Serial.println("recovering to defaults");
    request->send(SPIFFS, "/web/utility/recover.htm", String(), false, createDefaultProcessor());
    webConfig = GetDefaultConfig();
    SaveConfigWithRestart(webConfig);
  });

  server.on("/loadDefaults", HTTP_POST, [](AsyncWebServerRequest *request){
    clientDetected = true;
    Serial.println("resetting to defaults");
    webConfig = GetDefaultConfig();
    SaveConfig(webConfig);
    buildMaps(&webConfig);
    request->send(SPIFFS, "/web/shared/web_cfg.htm", String(), false, createDefaultProcessor());
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

    String output;
    serializeJson(doc, output);

    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", output);
    response->addHeader("Content-Disposition", "attachment; filename=config.json");
    
    request->send(response);
  });

  server.on("/import", HTTP_POST, [](AsyncWebServerRequest *request){
    //Serial.println("POST request received");
    inputDataBuffer = "";
    clientDetected = true;
    Serial.println("importing config");
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    for (size_t i = 0; i < len; i++) {
      inputDataBuffer += (char)data[i];
    }
    
    if(index + len == total){
      Serial.println("Total data received");
      JsonDocument doc;
      deserializeJson(doc, inputDataBuffer);
      webConfig = parseConfig(doc);
      SaveConfig(webConfig);
      buildMaps(&webConfig);
      request->send(200);
      SaveConfigWithRestart(webConfig);
    }
  });

  server.begin();
}