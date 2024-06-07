#include "web_cfg.h"

DNSServer dnsServer;
AsyncWebServer server(80);

Config webConfig;
Preferences* webPreferences;

void SetupWifi(Preferences* preferences,Config cfg){
  webConfig = cfg;
  webPreferences = preferences;
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
    SaveConfig(webPreferences, webConfig);
    ESP.restart();
  });

  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.println("POST request received");
  }, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    // for (size_t i = 0; i < len; i++) {
    //   Serial.write(data[i]);
    // }

    JsonDocument doc;
    deserializeJson(doc, (const char*)data);
    webConfig = parseConfig(doc);
    request->send(SPIFFS, "/web_cfg.htm", String(), false, webCfgProcessor);
    SaveConfig(webPreferences, webConfig);
    Serial.println("restarting");
    ESP.restart();
  });


  server.begin();
}

void ProcessWifi(){
  dnsServer.processNextRequest();
}

String inputProcessor(const String& var){
  if(var == "INPUT_SIGNAL_TYPE_CRSF"){
    if(webConfig.signalType == CRSF){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "INPUT_SIGNAL_TYPE_SBUS"){
    if(webConfig.signalType == SBUS){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "INPUT_TRIGGER_CHANNEL_10"){
    if(webConfig.triggerChannel == 10){
        return "selected";
    }else{
        return "";
    }
  }

  if(var == "INPUT_TRIGGER_CHANNEL_11"){
    if(webConfig.triggerChannel == 11){
        return "selected";
    }else{
        return "";
    }
  }

  if(var == "INPUT_TRIGGER_CHANNEL_12"){
    if(webConfig.triggerChannel == 12){
        return "selected";
    }else{
        return "";
    }
  }

  if(var == "INPUT_TRIGGER_CHANNEL_13"){
    if(webConfig.triggerChannel == 13){
        return "selected";
    }else{
        return "";
    }
  }

  if(var == "INPUT_TRIGGER_CHANNEL_14"){
    if(webConfig.triggerChannel == 14){
        return "selected";
    }else{
        return "";
    }
  }

  if(var == "INPUT_TRIGGER_CHANNEL_15"){
    if(webConfig.triggerChannel == 15){
        return "selected";
    }else{
        return "";
    }
  }

  if(var == "INPUT_TRIGGER_CHANNEL_16"){
    if(webConfig.triggerChannel == 16){
        return "selected";
    }else{
        return "";
    }
  }

  if(var == "INPUT_LEVEL_CHANNEL_10"){
    if(webConfig.levelChannel == 10){
        return "selected";
    }else{
        return "";
    }
  }

  if(var == "INPUT_LEVEL_CHANNEL_11"){
    if(webConfig.levelChannel == 11){
        return "selected";
    }else{
        return "";
    }
  }

  if(var == "INPUT_LEVEL_CHANNEL_12"){
    if(webConfig.levelChannel == 12){
        return "selected";
    }else{
        return "";
    }
  }

  if(var == "INPUT_LEVEL_CHANNEL_13"){
    if(webConfig.levelChannel == 13){
        return "selected";
    }else{
        return "";
    }
  }

  if(var == "INPUT_LEVEL_CHANNEL_14"){
    if(webConfig.levelChannel == 14){
        return "selected";
    }else{
        return "";
    }
  }

  if(var == "INPUT_LEVEL_CHANNEL_15"){
    if(webConfig.levelChannel == 15){
        return "selected";
    }else{
        return "";
    }
  }

  if(var == "INPUT_LEVEL_CHANNEL_16"){
    if(webConfig.levelChannel == 16){
        return "selected";
    }else{
        return "";
    }
  }

  return String();
}

String optionsProcessor(const String& var){
  if(var == "OPTIONS_INVERT_STEERING"){
    if(webConfig.invertSteering){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "OPTIONS_INVERT_ESC"){
    if(webConfig.invertESC){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "OPTIONS_ENABLE_TURN_SIGNALS"){
    if(webConfig.enableTurnSignals){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "OPTIONS_TURN_SIGNALS_HEAD"){
    if(webConfig.turnSignalsAlsoHead){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "OPTIONS_TURN_SIGNS_BRAKE"){
    if(webConfig.turnSignalsAlsoBrake){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "OPTIONS_ENABLE_HAZARDS"){
    if(webConfig.enableHazards){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "OPTIONS_ENABLE_FLASH"){
    if(webConfig.enableFlash){
        return "checked";
    }else{
        return "";
    }
  }

  return String();
}

String levelProcessor(const String& var){
  char numberChar = var[6]; // Get the character at the 6th index
  int number = numberChar - '0'; // Convert the character to an integer
  int i = number - 1; // Subtract 1 from the integer to get the correct index

  if(i >= NUM_LEVELS || i < 0){
    return String();
  }

  if(var == "LEVEL_"+String(i+1)+"_HAZARDS"){
    if(webConfig.levelCfgs[i].hazards){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "LEVEL_"+String(i+1)+"_TURN"){
    if(webConfig.levelCfgs[i].turnSignals){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "LEVEL_"+String(i+1)+"_BRAKE"){
    if(webConfig.levelCfgs[i].brakes){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "LEVEL_"+String(i+1)+"_HEAD"){
    if(webConfig.levelCfgs[i].headLights){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "LEVEL_"+String(i+1)+"_FLASH"){
    if(webConfig.levelCfgs[i].flashLights){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "LEVEL_"+String(i+1)+"_DRIFT"){
    if(webConfig.levelCfgs[i].driftLights){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "LEVEL_"+String(i+1)+"_UNDERGLOW"){
    if(webConfig.levelCfgs[i].underglow){
        return "checked";
    }else{
        return "";
    }
  }

  if(var == "LEVEL_"+String(i+1)+"_AUX"){
    if(webConfig.levelCfgs[i].auxLights){
      return "checked";
    }else{
      return "";
    }
  }

  if(var == "LEVEL_"+String(i+1)+"_EXHAUST"){
    if(webConfig.levelCfgs[i].exhaust){
      return "checked";
    }else{
      return "";
    }
  }

  return String();
}

String outProcessor(const String& var){
  char numberChar = var[4]; // Get the character at the 4th index
  int number = numberChar - '0'; // Convert the character to an integer
  int i = number - 1; // Subtract 1 from the integer to get the correct index

  if(i >= NUM_LIGHT_OUTPUTS || i < 0){
    Serial.println("out of bounds: " + String(i) + " " + var);
    return String();
  }

  if(var == "OUT_"+String(i+1)+"_RIGHT_HEAD"){
    if(webConfig.outCfgs[i].lightType == RIGHT_HEAD){
      return "selected";
    }else{
      return "";
    }
  }

  for(int j=0; j<NUM_FLASH_GROUPS; j++){
    if(var == "OUT_"+String(i+1)+"_FLASH_GROUP_"+String(j)+""){
      if(webConfig.outCfgs[i].flashGroup == j){
        return "checked";
      }else{
        return "";
      }
    }
  }

  if(var == "OUT_"+String(i+1)+"_RIGHT_HEAD"){
    if(webConfig.outCfgs[i].lightType == RIGHT_HEAD){
      return "selected";
    }else{
      return "";
    }
  }

  if(var == "OUT_"+String(i+1)+"_LEFT_HEAD"){
    if(webConfig.outCfgs[i].lightType == LEFT_HEAD){
      return "selected";
    }else{
      return "";
    }
  }

  if(var == "OUT_"+String(i+1)+"_RIGHT_FRONT_TURN"){
    if(webConfig.outCfgs[i].lightType == RIGHT_FRONT_TURN){
      return "selected";
    }else{
      return "";
    }
  }

  if(var == "OUT_"+String(i+1)+"_LEFT_FRONT_TURN"){
    if(webConfig.outCfgs[i].lightType == LEFT_FRONT_TURN){
      return "selected";
    }else{
      return "";
    }
  }

  if(var == "OUT_"+String(i+1)+"_RIGHT_BRAKE"){
    if(webConfig.outCfgs[i].lightType == RIGHT_BRAKE){
      return "selected";
    }else{
      return "";
    }
  }

  if(var == "OUT_"+String(i+1)+"_LEFT_BRAKE"){
    if(webConfig.outCfgs[i].lightType == LEFT_BRAKE){
      return "selected";
    }else{
      return "";
    }
  }

  if(var == "OUT_"+String(i+1)+"_RIGHT_REAR_TURN"){
    if(webConfig.outCfgs[i].lightType == RIGHT_REAR_TURN){
      return "selected";
    }else{
      return "";
    }
  }

  if(var == "OUT_"+String(i+1)+"_LEFT_REAR_TURN"){
    if(webConfig.outCfgs[i].lightType == LEFT_REAR_TURN){
      return "selected";
    }else{
      return "";
    }
  }

  if(var == "OUT_"+String(i+1)+"_AUX"){
    if(webConfig.outCfgs[i].lightType == AUX){
      return "selected";
    }else{
      return "";
    }
  }

  return String();
}

String stripProcessor(const String& var){
  char numberChar = var[6]; // Get the character at the 6th index
  int number = numberChar - '0'; // Convert the character to an integer
  int i = number - 1; // Subtract 1 from the integer to get the correct index

  if(i >= NUM_STRIPS || i < 0){
    Serial.println("out of bounds: " + String(i) + " " + var);
    return String();
  }

  if(var == "STRIP_"+String(i+1)+"_DRIFT_TYPE"){
    if(webConfig.stripCfgs[i].stripType == DRIFT_LIGHT){
      return "selected";
    }else{
      return "";
    }
  }

  if(var == "STRIP_"+String(i+1)+"_UNDERGLOW_TYPE"){
    if(webConfig.stripCfgs[i].stripType == UNDERGLOW){
      return "selected";
    }else{
      return "";
    }
  }

  if(var == "STRIP_"+String(i+1)+"_UNDERGLOW_COLOR"){
    char hexColor[8];
    sprintf(hexColor, "#%02X%02X%02X", webConfig.stripCfgs[i].color.r, webConfig.stripCfgs[i].color.g, webConfig.stripCfgs[i].color.b);
    return String(hexColor);
  }

  if(var == "STRIP_"+String(i+1)+"_EXHAUST_TYPE"){
    if(webConfig.stripCfgs[i].stripType == EXHAUST){
      return "selected";
    }else{
      return "";
    }
  }

  if(var == "STRIP_"+String(i+1)+"_NUM_LEDS"){
      return String(webConfig.stripCfgs[i].numLeds);
  }

  if(var == "STRIP_"+String(i+1)+"_DRIFT_MIDDLE"){
    if(webConfig.stripCfgs[i].driftLightType == MIDDLE_OUT){
      return "selected";
    }else{
      return "";
    }
  }

  if(var == "STRIP_"+String(i+1)+"_DRIFT_FRONT"){
    if(webConfig.stripCfgs[i].driftLightType == FRONT_TO_BACK){
      return "selected";
    }else{
      return "";
    }
  }

  if(var == "STRIP_"+String(i+1)+"_DRIFT_BACK"){
    if(webConfig.stripCfgs[i].driftLightType == BACK_TO_FRONT){
      return "selected";
    }else{
      return "";
    }
  }

  return String();
}

String webCfgProcessor(const String& var){
  if (var.startsWith("INPUT_")) {
    return inputProcessor(var);
  }else if(var.startsWith("OPTIONS_")){
    return optionsProcessor(var);
  }else if(var.startsWith("LEVEL_")){
    return levelProcessor(var);
  }else if(var.startsWith("OUT_")){
    return outProcessor(var);
  }else if(var.startsWith("STRIP_")){
    return stripProcessor(var);
  }
  
  Serial.println("no match: " + var);
  return String();
}

Config parseConfig(JsonDocument doc){
  Serial.println("parsing config");
  Config cfg;
  cfg.signalType = GetSignalTypeFromString(doc["signal_type"]);
  cfg.triggerChannel = doc["trigger_channel"];
  if(cfg.triggerChannel < 10 || cfg.triggerChannel > 16){
    cfg.triggerChannel = SYSTEM_ENABLE_CHANNEL;
  }

  cfg.levelChannel = doc["level_channel"];
  if(cfg.levelChannel < 10 || cfg.levelChannel > 16){
    cfg.levelChannel = LIGHT_LEVEL_CHANNEL;
  }

  if(cfg.levelChannel == cfg.triggerChannel){ //ensure seprate channels
    cfg.levelChannel = LIGHT_LEVEL_CHANNEL;
    cfg.triggerChannel = SYSTEM_ENABLE_CHANNEL;
  }

  cfg.invertSteering = GetBoolFromString(doc["invert_steer"]);
  cfg.invertESC = GetBoolFromString(doc["invert_throttle"]);
  cfg.enableTurnSignals = GetBoolFromString(doc["enable_turnsignals"]);
  cfg.turnSignalsAlsoHead = GetBoolFromString(doc["turnsignals_as_head"]);
  cfg.turnSignalsAlsoBrake = GetBoolFromString(doc["turnsignals_as_brake"]);
  cfg.enableHazards = GetBoolFromString(doc["enable_hazards"]);
  cfg.enableFlash = GetBoolFromString(doc["enable_flashing"]);

  Serial.println("parsing levels");
  for(int i=0; i<NUM_LEVELS; i++){
    cfg.levelCfgs[i].hazards = GetBoolFromString(doc["level_"+String(i+1)+"_hazards"]);
    cfg.levelCfgs[i].turnSignals = GetBoolFromString(doc["level_"+String(i+1)+"_turn"]);
    cfg.levelCfgs[i].brakes = GetBoolFromString(doc["level_"+String(i+1)+"_brake"]);
    cfg.levelCfgs[i].headLights = GetBoolFromString(doc["level_"+String(i+1)+"_head"]);
    cfg.levelCfgs[i].flashLights = GetBoolFromString(doc["level_"+String(i+1)+"_flashing"]);
    cfg.levelCfgs[i].driftLights = GetBoolFromString(doc["level_"+String(i+1)+"_drift"]);
    cfg.levelCfgs[i].underglow = GetBoolFromString(doc["level_"+String(i+1)+"_underglow"]);
    cfg.levelCfgs[i].auxLights = GetBoolFromString(doc["level_"+String(i+1)+"_aux"]);
    cfg.levelCfgs[i].exhaust = GetBoolFromString(doc["level_"+String(i+1)+"_exhaust"]);
  }

  Serial.println("parsing outputs");
  for(int i=0; i<NUM_LIGHT_OUTPUTS; i++){
    cfg.outCfgs[i].lightType = GetLightTypeFromString(doc["out_"+String(i+1)+"_type"]);
    cfg.outCfgs[i].flashGroup = GetFlashGroupFromString(doc["out_"+String(i+1)+"_flash_group"]);
  }

  Serial.println("parsing strips");
  for(int i=0; i<NUM_STRIPS; i++){
    cfg.stripCfgs[i].stripType = GetStripTypeFromString(doc["strip_"+String(i+1)+"_type"]);
    cfg.stripCfgs[i].color = GetColorFromHexString(doc["strip_"+String(i+1)+"_color"]);
    cfg.stripCfgs[i].numLeds = doc["strip_"+String(i+1)+"_num_leds"];
    if(cfg.stripCfgs[i].numLeds > NUM_STRIP_LEDS){
      cfg.stripCfgs[i].numLeds = NUM_STRIP_LEDS;
    }
    cfg.stripCfgs[i].driftLightType = GetDriftLightTypeFromString(doc["strip_"+String(i+1)+"_drift_type"]);
  }

  Serial.println("Parsed config: ");
  PrintConfig(cfg);
  return cfg;
}

/*
Form Submit:
{
    "signal_type": "crsf",
    "trigger_channel": "10",
    "level_channel": "11",
    "invert_steer": "on",
    "enable_turnsignals": "on",
    "turnsignals_as_head": "on",
    "turnsignals_as_brake": "on",
    "enable_hazards": "on",
    "level_1_hazards": "on",
    "level_1_turn": "on",
    "level_1_brake": "on",
    "level_1_exhaust": "on",
    "level_2_hazards": "on",
    "level_2_turn": "on",
    "level_2_brake": "on",
    "level_2_head": "on",
    "level_2_exhaust": "on",
    "level_3_hazards": "on",
    "level_3_turn": "on",
    "level_3_brake": "on",
    "level_3_head": "on",
    "level_3_drift": "on",
    "level_3_underglow": "on",
    "level_3_aux": "on",
    "level_3_exhaust": "on",
    "out_1_type": "right_front_turn",
    "out_1_flash_group": "0",
    "out_2_type": "right_head",
    "out_2_flash_group": "2",
    "out_3_type": "left_head",
    "out_3_flash_group": "1",
    "out_4_type": "left_front_turn",
    "out_4_flash_group": "0",
    "out_5_type": "left_rear_turn",
    "out_5_flash_group": "0",
    "out_6_type": "left_brake",
    "out_6_flash_group": "1",
    "out_7_type": "right_brake",
    "out_7_flash_group": "2",
    "out_8_type": "right_rear_turn",
    "out_8_flash_group": "0",
    "strip_1_type": "drift_light",
    "strip_1_drift_led": "13",
    "strip_1_drift_type": "middle_out",
    "strip_1_color": "#ff0000",
    "strip_2_type": "exhaust",
    "strip_2_drift_led": "50",
    "strip_2_drift_type": "back_to_front",
    "strip_2_color": "#0000ff",
    "strip_3_type": "underglow",
    "strip_3_drift_led": "50",
    "strip_3_drift_type": "front_to_back",
    "strip_3_color": "#008000"
}
*/