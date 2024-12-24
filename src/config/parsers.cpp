#include "config.h"

bool GetBoolFromString(const std::string& value) {
  std::string lowercaseValue = value;
  std::transform(lowercaseValue.begin(), lowercaseValue.end(), lowercaseValue.begin(), ::tolower);
  
  if (lowercaseValue == "on" || lowercaseValue == "true" || lowercaseValue == "1") {
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

UnderGlowType GetUnderGlowTypeFromString(const std::string& value) {
  std::string lowercaseValue = value;
  std::transform(lowercaseValue.begin(), lowercaseValue.end(), lowercaseValue.begin(), ::tolower);
  
  if (lowercaseValue == "breathe") {
    return UNDERGLOW_BREATHE;
  } else if (lowercaseValue == "palette") {
    return UNDERGLOW_PALETTE;
  } else {
    return UNDERGLOW_SOLID; //default value
  }
}

ThrottleBrakeType GetThrottleBrakeTypeFromString(const std::string& value) {
  std::string lowercaseValue = value;
  std::transform(lowercaseValue.begin(), lowercaseValue.end(), lowercaseValue.begin(), ::tolower);
  
  if (lowercaseValue == "top") {
    return TB_TOP;
  } else if (lowercaseValue == "mid") {
    return TB_MID;
  } else {
    return TB_BOTTOM; //default value
  }
}

EmergencyType GetEmergencyTypeFromString(const std::string& value) {
  std::string lowercaseValue = value;
  std::transform(lowercaseValue.begin(), lowercaseValue.end(), lowercaseValue.begin(), ::tolower);
  
  if (lowercaseValue == "wrap") {
    return EMERGENCY_WRAP;
  } else {
    return EMERGENCY_SOLID; //default value
  }
}

ExhaustPalette GetExhaustPaletteFromString(const std::string& value) {
  std::string lowercaseValue = value;
  std::transform(lowercaseValue.begin(), lowercaseValue.end(), lowercaseValue.begin(), ::tolower);
  
  if (lowercaseValue == "blue") {
    return BLUE_EXHAUST_PALETTE;
  } else if (lowercaseValue == "green") {
    return GREEN_EXHAUST_PALETTE;
  } else if (lowercaseValue == "purple") {
    return PURPLE_EXHAUST_PALETTE;
  } else if (lowercaseValue == "cyan") {
    return CYAN_EXHAUST_PALETTE;
  } else if (lowercaseValue == "rainbow") {
    return RAINBOW_EXHAUST_PALETTE;
  } else {
    return DEFAULT_EXHAUST_PALETTE; //default value
  }
}

UnderGlowPalette GetUnderGlowPaletteFromString(const std::string& value) {
  std::string lowercaseValue = value;
  std::transform(lowercaseValue.begin(), lowercaseValue.end(), lowercaseValue.begin(), ::tolower);
  
  if (lowercaseValue == "cloud") {
    return UNDERGLOW_CLOUD;
  } else if (lowercaseValue == "lava") {
    return UNDERGLOW_LAVA;
  } else if (lowercaseValue == "ocean") {
    return UNDERGLOW_OCEAN;
  } else if (lowercaseValue == "forest") {
    return UNDERGLOW_FOREST;
  } else if (lowercaseValue == "party") {
    return UNDERGLOW_PARTY;
  } else if (lowercaseValue == "heat") {
    return UNDERGLOW_HEAT;
  } else {
    return UNDERGLOW_RAINBOW; //default value
  }
}

StripAnimation GetStripAnimationFromString(const std::string& value) {
  std::string lowercaseValue = value;
  std::transform(lowercaseValue.begin(), lowercaseValue.end(), lowercaseValue.begin(), ::tolower);
  
  if (lowercaseValue == "underglow") {
    return UNDERGLOW;
  } else if (lowercaseValue == "throttle_brake") {
    return THROTTLE_BRAKE;
  } else if (lowercaseValue == "exhaust") {
    return EXHAUST;
  } else if (lowercaseValue == "emergency") {
    return EMERGENCY;
  } else {
    return NONE; //default value
  }
}

EOrder GetColorOrderFromString(const std::string& value) {
  std::string lowercaseValue = value;
  std::transform(lowercaseValue.begin(), lowercaseValue.end(), lowercaseValue.begin(), ::tolower);
  
  if (lowercaseValue == "rgb") {
    return RGB;
  } else if (lowercaseValue == "grb") {
    return GRB;
  } else if (lowercaseValue == "brg") {
    return BRG;
  } else if (lowercaseValue == "rbg") {
    return RBG;
  } else if (lowercaseValue == "bgr") {
    return BGR;
  } else {
    return GBR; //default value
  }
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
    parseOutConfig(&cfg, outCfgs[i], false);
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
  "leftTurn": "0",
  "rightTurn": "0",
  "brake": "0",
  "tail": "0",
  "head": "0",
  "reverse": "0",
  "hazard": "0",
  "running": "0",
  "aux1": "0",
  "aux2": "0",
  "strobe1": "0",
  "strobe2": "0"
}
*/

void parseRoleConfig(Config *cfg, JsonVariant doc, int i){
  if (i < 0 || i >= MAX_CHANNELS) {
    return;
  }

  if(cfg->outputConfig.channelConfigs[i].type != SINGLE_LED){
    return;
  }

  cfg->outputConfig.channelConfigs[i].roles.leftTurn = GetBoolFromString(doc["leftTurn"]);
  cfg->outputConfig.channelConfigs[i].roles.rightTurn = GetBoolFromString(doc["rightTurn"]);
  cfg->outputConfig.channelConfigs[i].roles.brake = GetBoolFromString(doc["brake"]);
  cfg->outputConfig.channelConfigs[i].roles.tail = GetBoolFromString(doc["tail"]);
  cfg->outputConfig.channelConfigs[i].roles.head = GetBoolFromString(doc["head"]);
  cfg->outputConfig.channelConfigs[i].roles.reverse = GetBoolFromString(doc["reverse"]);
  cfg->outputConfig.channelConfigs[i].roles.hazard = GetBoolFromString(doc["hazard"]);
  cfg->outputConfig.channelConfigs[i].roles.running = GetBoolFromString(doc["running"]);
  cfg->outputConfig.channelConfigs[i].roles.aux1 = GetBoolFromString(doc["aux1"]);
  cfg->outputConfig.channelConfigs[i].roles.aux2 = GetBoolFromString(doc["aux2"]);
  cfg->outputConfig.channelConfigs[i].roles.strobe1 = GetBoolFromString(doc["strobe1"]);
  cfg->outputConfig.channelConfigs[i].roles.strobe2 = GetBoolFromString(doc["strobe2"]);
}

/*
{
  "primary_color": "#FF0000",
  "secondary_color": "#00FF00",
  "ug_type": "cycle"
}
*/

void parseUnderglowConfig(Config *cfg, JsonVariant doc, int i){
  if (i < 0 || i >= MAX_CHANNELS) {
    return;
  }

  if(cfg->outputConfig.channelConfigs[i].type != LED_STRIP || cfg->outputConfig.channelConfigs[i].stripAnimation != UNDERGLOW){
    return;
  }

  cfg->outputConfig.channelConfigs[i].underglowConfig.primaryColor = GetColorFromHexString(doc["primary_color"]);
  cfg->outputConfig.channelConfigs[i].underglowConfig.secondaryColor = GetColorFromHexString(doc["secondary_color"]);
  cfg->outputConfig.channelConfigs[i].underglowConfig.type = GetUnderGlowTypeFromString(doc["ug_type"]);
  cfg->outputConfig.channelConfigs[i].underglowConfig.palette = GetUnderGlowPaletteFromString(doc["ug_palette"]);
}

/*
{
  "throttle_color": "#FF0000",
  "brake_color": "#00FF00",
  "tb_type": "top"
}
*/
void parseThrottleBrakeConfig(Config *cfg, JsonVariant doc, int i){
  if (i < 0 || i >= MAX_CHANNELS) {
    return;
  }

  if(cfg->outputConfig.channelConfigs[i].type != LED_STRIP || cfg->outputConfig.channelConfigs[i].stripAnimation != THROTTLE_BRAKE){
    return;
  }

  cfg->outputConfig.channelConfigs[i].throttleBrakeConfig.throttleColor = GetColorFromHexString(doc["throttle_color"]);
  cfg->outputConfig.channelConfigs[i].throttleBrakeConfig.brakeColor = GetColorFromHexString(doc["brake_color"]);
  cfg->outputConfig.channelConfigs[i].throttleBrakeConfig.type = GetThrottleBrakeTypeFromString(doc["tb_type"]);
}

/*
{
  "dim_threshold": "50",
  "bright_threshold": "80",
  "pop_threshold": "95",
  "flame_palette": "blue"
}
*/
void parseExhaustConfig(Config *cfg, JsonVariant doc, int i){
  if (i < 0 || i >= MAX_CHANNELS) {
    return;
  }

  if(cfg->outputConfig.channelConfigs[i].type != LED_STRIP || cfg->outputConfig.channelConfigs[i].stripAnimation != EXHAUST){
    return;
  }
  
  cfg->outputConfig.channelConfigs[i].exhaustConfig.palette = GetExhaustPaletteFromString(doc["exhaust_palette"]);
}

void parseEmergencyConfig(Config *cfg, JsonVariant doc, int i){
  if (i < 0 || i >= MAX_CHANNELS) {
    return;
  }

  if(cfg->outputConfig.channelConfigs[i].type != LED_STRIP || cfg->outputConfig.channelConfigs[i].stripAnimation != EMERGENCY){
    return;
  }

  cfg->outputConfig.channelConfigs[i].emergencyConfig.primaryColor = GetColorFromHexString(doc["primary_color"]);
  cfg->outputConfig.channelConfigs[i].emergencyConfig.secondaryColor = GetColorFromHexString(doc["secondary_color"]);
  cfg->outputConfig.channelConfigs[i].emergencyConfig.type = GetEmergencyTypeFromString(doc["em_type"]);
}

/*
{
  "out_num": "16",
  "out_type": "single",
  "out_order": "RGB",
  "out_num_leds": "2",
  "out_animation": "0",
  "out_roles": null,
  "out_exhaust": null,
  "out_throttle_brake": null,
  "out_underglow": null
}
*/
void parseOutConfig(Config *cfg, JsonVariant doc, bool web){
  int i = doc["out_num"];
  if (i < 1 || i > MAX_CHANNELS) {
      return;
  }
  
  i--; // 0 based index

  //Serial.println("Parsing out config for channel " + String(i+1));
      
  cfg->outputConfig.channelConfigs[i].type = doc["out_type"] == "single" ? SINGLE_LED : LED_STRIP;
  cfg->outputConfig.channelConfigs[i].colorOrder = GetColorOrderFromString(doc["out_order"]);
  cfg->outputConfig.channelConfigs[i].stripAnimation = GetStripAnimationFromString(doc["out_animation"]);
  
  int numLeds = doc["out_num_leds"];
  if(numLeds < 0 || numLeds >= NUM_STRIP_LEDS){
    numLeds = NUM_STRIP_LEDS;
  }
  cfg->outputConfig.channelConfigs[i].stripLedCount = numLeds;
  

  if(web){
    parseRoleConfig(cfg, doc, i);
    parseUnderglowConfig(cfg, doc, i);
    parseThrottleBrakeConfig(cfg, doc, i);
    parseExhaustConfig(cfg, doc, i);
    parseEmergencyConfig(cfg, doc, i);
  }else{
    parseRoleConfig(cfg, doc["out_roles"], i);
    parseUnderglowConfig(cfg, doc["out_underglow"], i);
    parseThrottleBrakeConfig(cfg, doc["out_throttle_brake"], i);
    parseExhaustConfig(cfg, doc["out_exhaust"], i);
    parseEmergencyConfig(cfg, doc["out_emergency"], i);
  }

  return;
}