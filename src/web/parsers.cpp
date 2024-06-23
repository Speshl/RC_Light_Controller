#include "web.h"

extern Config webConfig;

bool GetBoolFromString(const std::string& value) {
  std::string lowercaseValue = value;
  std::transform(lowercaseValue.begin(), lowercaseValue.end(), lowercaseValue.begin(), ::tolower);
  
  if (lowercaseValue == "on") {
    return true;
  } else {
    return false; //default value
  }
}

CRGB GetColorFromHexString(const String& hexString) {
  unsigned long rgb = strtoul(hexString.substring(1).c_str(), NULL, 16);  // Skip the first character (#)
  uint8_t r = rgb >> 16;
  uint8_t g = rgb >> 8 & 0xFF;
  uint8_t b = rgb & 0xFF;
  return CRGB(r, g, b);
}

Config parseConfig(JsonDocument doc){
  Config cfg = webConfig;

  parseInputConfig(&cfg, doc["input_config"]);

  JsonArray levelCfgs = doc["level_configs"];
  //Serial.println("Parsing " + String(levelCfgs.size()) + " level configs");
  for(int i=0; i<levelCfgs.size(); i++){
    parseLevelConfig(&cfg, levelCfgs[i]);
  }

  JsonArray outCfgs = doc["out_configs"];
  //Serial.println("Parsing " + String(outCfgs.size()) + " out configs");
  for(int i=0; i<outCfgs.size(); i++){
    //Serial.println("Parsing out config " + String(i));
    parseOutConfig(&cfg, outCfgs[i]);
  }

  return cfg;
}

/*
{signal_type: "CRSF", steer_channel: "1", esc_channel: "2", trigger_channel: "10", level_channel: "11"}
*/
void parseInputConfig(Config *cfg, JsonVariant doc){
    cfg->inputConfig.type = doc["signal_type"] == "SBUS" ? SBUS : CRSF;

    int steerChannel = doc["steer_channel"];
    if(steerChannel < 1 || steerChannel > 8){
        cfg->inputConfig.steerChannel = STEER_CHANNEL;
    }else{
        cfg->inputConfig.steerChannel = steerChannel;
    }

    cfg->inputConfig.steerInverted = GetBoolFromString(doc["invert_steer"]);

    int escChannel = doc["esc_channel"];
    if(escChannel < 1 || escChannel > 8){
        cfg->inputConfig.escChannel = ESC_CHANNEL;
    }else{
        cfg->inputConfig.escChannel = escChannel;
    }

    cfg->inputConfig.escInverted = GetBoolFromString(doc["invert_esc"]);

    int triggerChannel = doc["trigger_channel"];
    if(triggerChannel < 10 || triggerChannel > 16){
        cfg->inputConfig.enableChannel = SYSTEM_ENABLE_CHANNEL;
    }else{
        cfg->inputConfig.enableChannel = triggerChannel;
    }

    int levelChannel = doc["level_channel"];
    if(levelChannel < 10 || levelChannel > 16){
        cfg->inputConfig.levelChannel = LIGHT_LEVEL_CHANNEL;
    }else{
        cfg->inputConfig.levelChannel = levelChannel;
    }
}

/*
{
  "level_num": "3",
  "level_leftTurn": "on",
  "level_rightTurn": "on",
  "level_brake": "on",
  "level_tail": "on",
  "level_head": "on",
  "level_reverse": "on",
  "level_hazard": "on",
  "level_running": "on",
  "level_aux1": "on",
  "level_aux2": "on",
  "level_strobe1": "on",
  "level_strobe2": "on",
  "level_underglow": "on",
  "level_throttle_light": "on",
  "level_exhaust": "on",
  "level_police": "on",
  "level_caution": "on"
}
*/
void parseLevelConfig(Config *cfg, JsonVariant doc){
    int i = doc["level_num"];
    if(i < 1 || i > NUM_LEVELS){
        return;
    }

    i--; // 0 based index
    
    cfg->levelConfigs[i].roles.leftTurn = GetBoolFromString(doc["level_leftTurn"]);
    cfg->levelConfigs[i].roles.rightTurn = GetBoolFromString(doc["level_rightTurn"]);
    cfg->levelConfigs[i].roles.brake = GetBoolFromString(doc["level_brake"]);
    cfg->levelConfigs[i].roles.tail = GetBoolFromString(doc["level_tail"]);
    cfg->levelConfigs[i].roles.head = GetBoolFromString(doc["level_head"]);
    cfg->levelConfigs[i].roles.reverse = GetBoolFromString(doc["level_reverse"]);
    cfg->levelConfigs[i].roles.hazard = GetBoolFromString(doc["level_hazard"]);
    cfg->levelConfigs[i].roles.running = GetBoolFromString(doc["level_running"]);
    cfg->levelConfigs[i].roles.aux1 = GetBoolFromString(doc["level_aux1"]);
    cfg->levelConfigs[i].roles.aux2 = GetBoolFromString(doc["level_aux2"]);
    cfg->levelConfigs[i].roles.strobe1 = GetBoolFromString(doc["level_strobe1"]);
    cfg->levelConfigs[i].roles.strobe2 = GetBoolFromString(doc["level_strobe2"]);
    cfg->levelConfigs[i].animations.underglow = GetBoolFromString(doc["level_underglow"]);
    cfg->levelConfigs[i].animations.throttleBrakeLight = GetBoolFromString(doc["level_throttle_light"]);
    cfg->levelConfigs[i].animations.exhaustFlame = GetBoolFromString(doc["level_exhaust"]);
    cfg->levelConfigs[i].animations.policeLights = GetBoolFromString(doc["level_police"]);
    cfg->levelConfigs[i].animations.cautionLights = GetBoolFromString(doc["level_caution"]);

    return;
}

/*
{
  "out_num": "1",
  "out_type": "strip",
  "out_role_leftTurn": "on",
  "out_role_rightTurn": "on",
  "out_role_brake": "on",
  "out_role_tail": "on",
  "out_role_head": "on",
  "out_role_reverse": "on",
  "out_role_hazard": "on",
  "out_role_running": "on",
  "out_role_aux1": "on",
  "out_role_aux2": "on",
  "out_role_strobe1": "on",
  "out_role_strobe2": "on",
  "out_order": "17",
  "out_num_leds": "1",
  "out_animation": "2",
  "out_color": "#ff0000"
}
*/
void parseOutConfig(Config *cfg, JsonVariant doc){
    int i = doc["out_num"];
    if (i < 1 || i > MAX_CHANNELS) {
        return;
    }
    
    i--; // 0 based index

    Serial.println("Parsing out config for channel " + String(i+1));
        
    cfg->outputConfig.channelConfigs[i].type = doc["out_type"] == "single" ? SINGLE_LED : LED_STRIP;

    cfg->outputConfig.channelConfigs[i].roles.leftTurn = GetBoolFromString(doc["out_role_leftTurn"]);
    cfg->outputConfig.channelConfigs[i].roles.rightTurn = GetBoolFromString(doc["out_role_rightTurn"]);
    cfg->outputConfig.channelConfigs[i].roles.brake = GetBoolFromString(doc["out_role_brake"]);
    cfg->outputConfig.channelConfigs[i].roles.tail = GetBoolFromString(doc["out_role_tail"]);
    cfg->outputConfig.channelConfigs[i].roles.head = GetBoolFromString(doc["out_role_head"]);
    cfg->outputConfig.channelConfigs[i].roles.reverse = GetBoolFromString(doc["out_role_reverse"]);
    cfg->outputConfig.channelConfigs[i].roles.hazard = GetBoolFromString(doc["out_role_hazard"]);
    cfg->outputConfig.channelConfigs[i].roles.running = GetBoolFromString(doc["out_role_running"]);
    cfg->outputConfig.channelConfigs[i].roles.aux1 = GetBoolFromString(doc["out_role_aux1"]);
    cfg->outputConfig.channelConfigs[i].roles.aux2 = GetBoolFromString(doc["out_role_aux2"]);
    cfg->outputConfig.channelConfigs[i].roles.strobe1 = GetBoolFromString(doc["out_role_strobe1"]);
    cfg->outputConfig.channelConfigs[i].roles.strobe2 = GetBoolFromString(doc["out_role_strobe2"]);
    cfg->outputConfig.channelConfigs[i].colorOrder = doc["out_color"] == "RGB" ? RGB : doc["out_color"] == "GRB" ? GRB : doc["out_color"] == "BRG" ? BRG : doc["out_color"] == "RBG" ? RBG : doc["out_color"] == "BGR" ? BGR : GBR;
    cfg->outputConfig.channelConfigs[i].stripAnimation = doc["out_animation"] == "1" ? UNDERGLOW_SOLID : doc["out_animation"] == "2" ? UNDERGLOW_BREATHE : doc["out_animation"] == "3" ? UNDERGLOW_CYCLE : doc["out_animation"] == "4" ? THROTTLE_BRAKE_LIGHT_BOTTOM : doc["out_animation"] == "5" ? THROTTLE_BRAKE_LIGHT_TOP : doc["out_animation"] == "6" ? THROTTLE_BRAKE_LIGHT_MIDDLE : doc["out_animation"] == "7" ? EXHAUST_FLAME : doc["out_animation"] == "8" ? POLICE_LIGHTS_SOLID : doc["out_animation"] == "9" ? POLICE_LIGHTS_WRAP : doc["out_animation"] == "10" ? CAUTION_LIGHTS_SOLID : CAUTION_LIGHTS_WRAP;
    cfg->outputConfig.channelConfigs[i].color = GetColorFromHexString(doc["out_color"]);

    int numLeds = doc["out_num_leds"];
    if(numLeds < 0 || numLeds >= NUM_STRIP_LEDS){
      cfg->outputConfig.channelConfigs[i].stripLedCount = NUM_STRIP_LEDS;
    }else{
      cfg->outputConfig.channelConfigs[i].stripLedCount = numLeds;
    }

    cfg->outputConfig.channelConfigs[i].colorOrder = doc["out_order"];

    return;
}

JsonDocument ConfigToJson(Config *cfg){
  JsonDocument jsonCfg;

  jsonCfg["input_config"] = InputConfigToJson(cfg);
  //JsonArray levelCfgs = jsonCfg.createNestedArray("level_configs");
  JsonArray levelCfgs = jsonCfg["level_configs"].to<JsonArray>();
  //JsonArray outCfgs = jsonCfg.createNestedArray("out_configs");
  JsonArray outCfgs = jsonCfg["out_configs"].to<JsonArray>();

  for(int i=0; i<NUM_LEVELS; i++){
    levelCfgs.add(LevelConfigToJson(cfg, i));
  }

  for(int i=0; i<MAX_CHANNELS; i++){
    outCfgs.add(OutConfigToJson(cfg, i));
  }
  
  return jsonCfg;
}

JsonDocument InputConfigToJson(Config *cfg){
  JsonDocument inputCfg;
  inputCfg["signal_type"] = cfg->inputConfig.type == SBUS ? "SBUS" : "CRSF";
  inputCfg["steer_channel"] = cfg->inputConfig.steerChannel;
  inputCfg["invert_steer"] =  cfg->inputConfig.steerInverted ? "on" : "off";
  inputCfg["esc_channel"] = cfg->inputConfig.escChannel;
  inputCfg["invert_esc"] = cfg->inputConfig.escInverted ? "on" : "off";
  inputCfg["trigger_channel"] = cfg->inputConfig.enableChannel;
  inputCfg["level_channel"] = cfg->inputConfig.levelChannel;
  return inputCfg;
}

JsonDocument LevelConfigToJson(Config *cfg, int levelNum){
  JsonDocument levelCfg;

  levelCfg["level_num"] = String(levelNum+1);
  levelCfg["level_leftTurn"] = cfg->levelConfigs[levelNum].roles.leftTurn ? "on" : "off";
  levelCfg["level_rightTurn"] = cfg->levelConfigs[levelNum].roles.rightTurn ? "on" : "off";
  levelCfg["level_brake"] = cfg->levelConfigs[levelNum].roles.brake ? "on" : "off";
  levelCfg["level_tail"] = cfg->levelConfigs[levelNum].roles.tail ? "on" : "off";
  levelCfg["level_head"] = cfg->levelConfigs[levelNum].roles.head ? "on" : "off";
  levelCfg["level_reverse"] = cfg->levelConfigs[levelNum].roles.reverse ? "on" : "off";
  levelCfg["level_hazard"] = cfg->levelConfigs[levelNum].roles.hazard ? "on" : "off";
  levelCfg["level_running"] = cfg->levelConfigs[levelNum].roles.running ? "on" : "off";
  levelCfg["level_aux1"] = cfg->levelConfigs[levelNum].roles.aux1 ? "on" : "off";
  levelCfg["level_aux2"] = cfg->levelConfigs[levelNum].roles.aux2 ? "on" : "off";
  levelCfg["level_strobe1"] = cfg->levelConfigs[levelNum].roles.strobe1 ? "on" : "off";
  levelCfg["level_strobe2"] = cfg->levelConfigs[levelNum].roles.strobe2 ? "on" : "off";
  levelCfg["level_underglow"] = cfg->levelConfigs[levelNum].animations.underglow ? "on" : "off";
  levelCfg["level_throttle_light"] = cfg->levelConfigs[levelNum].animations.throttleBrakeLight ? "on" : "off";
  levelCfg["level_exhaust"] = cfg->levelConfigs[levelNum].animations.exhaustFlame ? "on" : "off";
  levelCfg["level_police"] = cfg->levelConfigs[levelNum].animations.policeLights ? "on" : "off";
  levelCfg["level_caution"] = cfg->levelConfigs[levelNum].animations.cautionLights ? "on" : "off";

  return levelCfg;
}

JsonDocument OutConfigToJson(Config *cfg, int outNum){
  JsonDocument outCfg;

  outCfg["out_num"] = String(outNum+1);
  outCfg["out_type"] = cfg->outputConfig.channelConfigs[outNum].type == SINGLE_LED ? "single" : "strip";
  outCfg["out_order"] = String(cfg->outputConfig.channelConfigs[outNum].stripAnimation);
  outCfg["out_num_leds"] = String(cfg->outputConfig.channelConfigs[outNum].stripLedCount);
  outCfg["out_animation"] = String(cfg->outputConfig.channelConfigs[outNum].stripAnimation);

  CRGB color = cfg->outputConfig.channelConfigs[outNum].color;
  char hexColor[8]; // Buffer to hold the resulting hex string
  sprintf(hexColor, "#%02X%02X%02X", color.r, color.g, color.b);
  outCfg["out_color"] = hexColor;

  outCfg["out_role_leftTurn"] = cfg->outputConfig.channelConfigs[outNum].roles.leftTurn ? "on" : "off";
  outCfg["out_role_rightTurn"] = cfg->outputConfig.channelConfigs[outNum].roles.rightTurn ? "on" : "off";
  outCfg["out_role_brake"] = cfg->outputConfig.channelConfigs[outNum].roles.brake ? "on" : "off";
  outCfg["out_role_tail"] = cfg->outputConfig.channelConfigs[outNum].roles.tail ? "on" : "off";
  outCfg["out_role_head"] = cfg->outputConfig.channelConfigs[outNum].roles.head ? "on" : "off";
  outCfg["out_role_reverse"] = cfg->outputConfig.channelConfigs[outNum].roles.reverse ? "on" : "off";
  outCfg["out_role_hazard"] = cfg->outputConfig.channelConfigs[outNum].roles.hazard ? "on" : "off";
  outCfg["out_role_running"] = cfg->outputConfig.channelConfigs[outNum].roles.running ? "on" : "off";
  outCfg["out_role_aux1"] = cfg->outputConfig.channelConfigs[outNum].roles.aux1 ? "on" : "off";
  outCfg["out_role_aux2"] = cfg->outputConfig.channelConfigs[outNum].roles.aux2 ? "on" : "off";
  outCfg["out_role_strobe1"] = cfg->outputConfig.channelConfigs[outNum].roles.strobe1 ? "on" : "off";
  outCfg["out_role_strobe2"] = cfg->outputConfig.channelConfigs[outNum].roles.strobe2 ? "on" : "off";

  return outCfg;
}