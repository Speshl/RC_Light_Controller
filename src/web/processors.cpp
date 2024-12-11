#include "web.h"

std::map<String, String> inputMap;
std::array<std::map<String, String>, NUM_LEVELS> levelsMap;
std::array<std::map<String, String>, MAX_CHANNELS> outputsMap;

String genericProcessor(const String& var, const std::map<String, String>& dataMap) {
  if (dataMap.count(var.c_str()) > 0) {
    return dataMap.at(var.c_str());
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String inputProcessor(const String& var) {
  return genericProcessor(var, inputMap);
}

std::function<String(const String&)> createLevelProcessor(int level) {
  return [level](const String& var) -> String {
    if (level < 0 || level >= NUM_LEVELS) {
      Serial.println("invalid level: " + String(level));
      return String("");
    }
    return genericProcessor(var, levelsMap[level]);
  };
}

std::function<String(const String&)> createOutputProcessor(int output) {
  return [output](const String& var) -> String {
    if (output < 0 || output >= MAX_CHANNELS) {
      Serial.println("invalid output: " + String(output));
      return String("");
    }
    return genericProcessor(var, outputsMap[output]);
  };
}

void buildInputMap(Config* webConfig){
  inputMap["INPUT_CRSF"] = webConfig->inputConfig.type == CRSF ? "selected" : "";
  inputMap["INPUT_SBUS"] = webConfig->inputConfig.type == SBUS ? "selected" : "";

  for(int i=1;i<9;i++){
    inputMap["INPUT_STEER_CHANNEL_" + String(i)] = webConfig->inputConfig.steerChannel == i ? "selected" : "";
    inputMap["INPUT_ESC_CHANNEL_" + String(i)] = webConfig->inputConfig.escChannel == i ? "selected" : "";
  }

  for(int i=10;i<17;i++){
    inputMap["INPUT_TRIGGER_CHANNEL_" + String(i)] = webConfig->inputConfig.enableChannel == i ? "selected" : "";
    inputMap["INPUT_LEVEL_CHANNEL_" + String(i)] = webConfig->inputConfig.levelChannel == i ? "selected" : "";
  }

  inputMap["INPUT_INVERT_STEER"] = webConfig->inputConfig.steerInverted ? "checked" : "";
  inputMap["INPUT_INVERT_ESC"] = webConfig->inputConfig.escInverted ? "checked" : "";
}

void buildLevelMaps(Config* webConfig){
  for(int i=0;i<3;i++){
    levelsMap[i]["LEVEL_NAME"] = "Level " + String(i+1);
    levelsMap[i]["LEVEL_NUM"] = "level_"+String(i+1)+"_tab";
    levelsMap[i]["LEVEL_IDX"] = String(i+1);

    levelsMap[i]["LEVEL_LEFTTURN"] = webConfig->levelConfigs[i].roles.leftTurn ? "checked" : "";
    levelsMap[i]["LEVEL_RIGHTTURN"] = webConfig->levelConfigs[i].roles.rightTurn ? "checked" : "";
    levelsMap[i]["LEVEL_BRAKE"] = webConfig->levelConfigs[i].roles.brake ? "checked" : "";
    levelsMap[i]["LEVEL_TAIL"] = webConfig->levelConfigs[i].roles.tail ? "checked" : "";
    levelsMap[i]["LEVEL_HEAD"] = webConfig->levelConfigs[i].roles.head ? "checked" : "";
    levelsMap[i]["LEVEL_REVERSE"] = webConfig->levelConfigs[i].roles.reverse ? "checked" : "";
    levelsMap[i]["LEVEL_HAZARD"] = webConfig->levelConfigs[i].roles.hazard ? "checked" : "";
    levelsMap[i]["LEVEL_RUNNING"] = webConfig->levelConfigs[i].roles.running ? "checked" : "";
    levelsMap[i]["LEVEL_AUX1"] = webConfig->levelConfigs[i].roles.aux1 ? "checked" : "";
    levelsMap[i]["LEVEL_AUX2"] = webConfig->levelConfigs[i].roles.aux2 ? "checked" : "";
    levelsMap[i]["LEVEL_STROBE1"] = webConfig->levelConfigs[i].roles.strobe1 ? "checked" : "";
    levelsMap[i]["LEVEL_STROBE2"] = webConfig->levelConfigs[i].roles.strobe2 ? "checked" : "";
    levelsMap[i]["LEVEL_UNDERGLOW"] = webConfig->levelConfigs[i].animations.underglow ? "checked" : "";
    levelsMap[i]["LEVEL_THROTTLE_LIGHT"] = webConfig->levelConfigs[i].animations.throttleBrakeLight ? "checked" : "";
    levelsMap[i]["LEVEL_EXHAUST"] = webConfig->levelConfigs[i].animations.exhaustFlame ? "checked" : "";
    levelsMap[i]["LEVEL_POLICE"] = webConfig->levelConfigs[i].animations.policeLights ? "checked" : "";
    levelsMap[i]["LEVEL_CAUTION"] = webConfig->levelConfigs[i].animations.cautionLights ? "checked" : "";
  }
}

void buildOutputMaps(Config* webConfig){
  for(int i=0;i<MAX_CHANNELS;i++){
    outputsMap[i]["OUT_NAME"] = "Output " + String(i+1);
    outputsMap[i]["OUT_NUM"] = "out_"+String(i+1)+"_tab";
    outputsMap[i]["OUT_IDX"] = String(i+1);

    outputsMap[i]["OUT_TYPE_SINGLE"] = (webConfig->outputConfig.channelConfigs[i].type == SINGLE_LED) ? "selected" : "";
    outputsMap[i]["OUT_TYPE_STRIP"] = (webConfig->outputConfig.channelConfigs[i].type == LED_STRIP) ? "selected" : "";

    outputsMap[i]["OUT_ROLE_LEFTTURN"] = webConfig->outputConfig.channelConfigs[i].roles.leftTurn ? "checked" : "";
    outputsMap[i]["OUT_ROLE_RIGHTTURN"] = webConfig->outputConfig.channelConfigs[i].roles.rightTurn ? "checked" : "";
    outputsMap[i]["OUT_ROLE_BRAKE"] = webConfig->outputConfig.channelConfigs[i].roles.brake ? "checked" : "";
    outputsMap[i]["OUT_ROLE_TAIL"] = webConfig->outputConfig.channelConfigs[i].roles.tail ? "checked" : "";
    outputsMap[i]["OUT_ROLE_HEAD"] = webConfig->outputConfig.channelConfigs[i].roles.head ? "checked" : "";
    outputsMap[i]["OUT_ROLE_REVERSE"] = webConfig->outputConfig.channelConfigs[i].roles.reverse ? "checked" : "";
    outputsMap[i]["OUT_ROLE_HAZARD"] = webConfig->outputConfig.channelConfigs[i].roles.hazard ? "checked" : "";
    outputsMap[i]["OUT_ROLE_RUNNING"] = webConfig->outputConfig.channelConfigs[i].roles.running ? "checked" : "";
    outputsMap[i]["OUT_ROLE_AUX1"] = webConfig->outputConfig.channelConfigs[i].roles.aux1 ? "checked" : "";
    outputsMap[i]["OUT_ROLE_AUX2"] = webConfig->outputConfig.channelConfigs[i].roles.aux2 ? "checked" : "";
    outputsMap[i]["OUT_ROLE_STROBE1"] = webConfig->outputConfig.channelConfigs[i].roles.strobe1 ? "checked" : "";
    outputsMap[i]["OUT_ROLE_STROBE2"] = webConfig->outputConfig.channelConfigs[i].roles.strobe2 ? "checked" : "";

    outputsMap[i]["OUT_UNDERGLOW_SOLID"] = (webConfig->outputConfig.channelConfigs[i].stripAnimation == UNDERGLOW_SOLID) ? "selected" : "";
    outputsMap[i]["OUT_UNDERGLOW_BREATHE"] = (webConfig->outputConfig.channelConfigs[i].stripAnimation == UNDERGLOW_BREATHE) ? "selected" : "";
    outputsMap[i]["OUT_UNDERGLOW_CYCLE"] = (webConfig->outputConfig.channelConfigs[i].stripAnimation == UNDERGLOW_CYCLE) ? "selected" : "";
    outputsMap[i]["OUT_THROTTLE_LIGHT_BOTTOM"] = (webConfig->outputConfig.channelConfigs[i].stripAnimation == THROTTLE_BRAKE_LIGHT_BOTTOM) ? "selected" : "";
    outputsMap[i]["OUT_THROTTLE_LIGHT_TOP"] = (webConfig->outputConfig.channelConfigs[i].stripAnimation == THROTTLE_BRAKE_LIGHT_TOP) ? "selected" : "";
    outputsMap[i]["OUT_THROTTLE_LIGHT_MID"] = (webConfig->outputConfig.channelConfigs[i].stripAnimation == THROTTLE_BRAKE_LIGHT_MIDDLE) ? "selected" : "";
    outputsMap[i]["OUT_EXHAUST_FLAME"] = (webConfig->outputConfig.channelConfigs[i].stripAnimation == EXHAUST_FLAME) ? "selected" : "";
    outputsMap[i]["OUT_POLICE_LIGHTS_SOLID"] = (webConfig->outputConfig.channelConfigs[i].stripAnimation == POLICE_LIGHTS_SOLID) ? "selected" : "";
    outputsMap[i]["OUT_POLICE_LIGHTS_WRAP"] = (webConfig->outputConfig.channelConfigs[i].stripAnimation == POLICE_LIGHTS_WRAP) ? "selected" : "";
    outputsMap[i]["OUT_CAUTION_LIGHTS_SOLID"] = (webConfig->outputConfig.channelConfigs[i].stripAnimation == CAUTION_LIGHTS_SOLID) ? "selected" : "";
    outputsMap[i]["OUT_CAUTION_LIGHTS_WRAP"] = (webConfig->outputConfig.channelConfigs[i].stripAnimation == CAUTION_LIGHTS_WRAP) ? "selected" : "";

    char hexColor[8];
    sprintf(hexColor, "#%02X%02X%02X", webConfig->outputConfig.channelConfigs[i].color.r, webConfig->outputConfig.channelConfigs[i].color.g, webConfig->outputConfig.channelConfigs[i].color.b);
    outputsMap[i]["OUT_COLOR"] = String(hexColor);

    outputsMap[i]["OUT_NUM_LEDS"] = String(webConfig->outputConfig.channelConfigs[i].stripLedCount);

    outputsMap[i]["OUT_RGB"] = webConfig->outputConfig.channelConfigs[i].colorOrder == RGB ? "selected" : "";
    outputsMap[i]["OUT_GRB"] = webConfig->outputConfig.channelConfigs[i].colorOrder == GRB ? "selected" : "";
    outputsMap[i]["OUT_BRG"] = webConfig->outputConfig.channelConfigs[i].colorOrder == BRG ? "selected" : "";
    outputsMap[i]["OUT_RBG"] = webConfig->outputConfig.channelConfigs[i].colorOrder == RBG ? "selected" : "";
    outputsMap[i]["OUT_BGR"] = webConfig->outputConfig.channelConfigs[i].colorOrder == BGR ? "selected" : "";
    outputsMap[i]["OUT_GBR"] = webConfig->outputConfig.channelConfigs[i].colorOrder == GBR ? "selected" : "";
  }
}

void buildMaps(Config* webConfig){
  buildInputMap(webConfig);
  buildLevelMaps(webConfig);
  buildOutputMaps(webConfig);
}