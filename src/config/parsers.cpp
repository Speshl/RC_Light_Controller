#include "config.h"

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
  Config cfg = GetBaseConfig();

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
  "level_emergency": "on",
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
    cfg->levelConfigs[i].animations.emergencyLights = GetBoolFromString(doc["level_emergency"]);

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

    //Serial.println("Parsing out config for channel " + String(i+1));
        
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
    cfg->outputConfig.channelConfigs[i].colorOrder = doc["out_order"] == "RGB" ? RGB : doc["out_order"] == "GRB" ? GRB : doc["out_order"] == "BRG" ? BRG : doc["out_order"] == "RBG" ? RBG : doc["out_order"] == "BGR" ? BGR : GBR;
    cfg->outputConfig.channelConfigs[i].stripAnimation = doc["out_animation"] == "1" ? UNDERGLOW_SOLID : doc["out_animation"] == "2" ? UNDERGLOW_BREATHE : doc["out_animation"] == "3" ? UNDERGLOW_CYCLE : doc["out_animation"] == "4" ? THROTTLE_BRAKE_LIGHT_BOTTOM : doc["out_animation"] == "5" ? THROTTLE_BRAKE_LIGHT_TOP : doc["out_animation"] == "6" ? THROTTLE_BRAKE_LIGHT_MIDDLE : doc["out_animation"] == "7" ? EXHAUST_FLAME : doc["out_animation"] == "8" ? EMERGENCY_LIGHTS_SOLID : EMERGENCY_LIGHTS_WRAP;
    cfg->outputConfig.channelConfigs[i].color = GetColorFromHexString(doc["out_color"]);

    int numLeds = doc["out_num_leds"];
    if(numLeds < 0 || numLeds >= NUM_STRIP_LEDS){
      cfg->outputConfig.channelConfigs[i].stripLedCount = NUM_STRIP_LEDS;
    }else{
      cfg->outputConfig.channelConfigs[i].stripLedCount = numLeds;
    }

    //cfg->outputConfig.channelConfigs[i].colorOrder = doc["out_order"];

    return;
}