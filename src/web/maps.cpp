#include "web.h"

extern Config webConfig;

extern std::map<String, String> inputMap;
extern std::array<std::map<String, String>, NUM_LEVELS> levelsMap;
extern std::array<std::map<String, String>, MAX_CHANNELS> outputsMap;

void buildMaps(){
  buildInputMap();
  buildLevelMaps();
  buildOutputMaps();
}

void buildInputMap(){
  if(webConfig.inputConfig.type == CRSF){
      inputMap["INPUT_CRSF"] = "selected";
  }else{
      inputMap["INPUT_CRSF"] = "";
  }

  if(webConfig.inputConfig.type == SBUS){
      inputMap["INPUT_SBUS"] = "selected";
  }else{
      inputMap["INPUT_SBUS"] = "";
  }

  for(int i=1;i<9;i++){
    if(webConfig.inputConfig.steerChannel == i){
      inputMap["INPUT_STEER_CHANNEL_" + String(i)] = "selected";
    }else{
      inputMap["INPUT_STEER_CHANNEL_" + String(i)] = "";
    }

    if(webConfig.inputConfig.escChannel == i){
      inputMap["INPUT_ESC_CHANNEL_" + String(i)] = "selected";
    }else{
      inputMap["INPUT_ESC_CHANNEL_" + String(i)] = "";
    }
  }

  for(int i=10;i<17;i++){
    if(webConfig.inputConfig.enableChannel == i){
      inputMap["INPUT_TRIGGER_CHANNEL_" + String(i)] = "selected";
    }else{
      inputMap["INPUT_TRIGGER_CHANNEL_" + String(i)] = "";
    }

    if(webConfig.inputConfig.levelChannel == i){
      inputMap["INPUT_LEVEL_CHANNEL_" + String(i)] = "selected";
    }else{
      inputMap["INPUT_LEVEL_CHANNEL_" + String(i)] = "";
    }
  }

  if(webConfig.inputConfig.steerInverted){
    inputMap["INPUT_INVERT_STEER"] = "checked";
  }else{  
    inputMap["INPUT_INVERT_STEER"] = "";
  }

  if(webConfig.inputConfig.escInverted){
    inputMap["INPUT_INVERT_ESC"] = "checked";
  }else{
    inputMap["INPUT_INVERT_ESC"] = "";
  }
}

void buildLevelMaps(){
  for(int i=0;i<3;i++){
    levelsMap[i]["LEVEL_NAME"] = "Level " + String(i+1);
    levelsMap[i]["LEVEL_NUM"] = "level_"+String(i+1)+"_tab";
    levelsMap[i]["LEVEL_IDX"] = String(i+1);

    if(webConfig.levelConfigs[i].roles.leftTurn){
      levelsMap[i]["LEVEL_LEFTTURN"] = "checked";
    }else{
      levelsMap[i]["LEVEL_LEFTTURN"] = "";
    }

    if(webConfig.levelConfigs[i].roles.rightTurn){
      levelsMap[i]["LEVEL_RIGHTTURN"] = "checked";
    }else{
      levelsMap[i]["LEVEL_RIGHTTURN"] = "";
    }

    if(webConfig.levelConfigs[i].roles.brake){
      levelsMap[i]["LEVEL_BRAKE"] = "checked";
    }else{
      levelsMap[i]["LEVEL_BRAKE"] = "";
    }

    if(webConfig.levelConfigs[i].roles.tail){
      levelsMap[i]["LEVEL_TAIL"] = "checked";
    }else{
      levelsMap[i]["LEVEL_TAIL"] = "";
    }

    if(webConfig.levelConfigs[i].roles.head){
      levelsMap[i]["LEVEL_HEAD"] = "checked";
    }else{
      levelsMap[i]["LEVEL_HEAD"] = "";
    }

    if(webConfig.levelConfigs[i].roles.reverse){
      levelsMap[i]["LEVEL_REVERSE"] = "checked";
    }else{
      levelsMap[i]["LEVEL_REVERSE"] = "";
    }

    if(webConfig.levelConfigs[i].roles.hazard){
      levelsMap[i]["LEVEL_HAZARD"] = "checked";
    }else{
      levelsMap[i]["LEVEL_HAZARD"] = "";
    }

    if(webConfig.levelConfigs[i].roles.running){
      levelsMap[i]["LEVEL_RUNNING"] = "checked";
    }else{
      levelsMap[i]["LEVEL_RUNNING"] = "";
    }

    if(webConfig.levelConfigs[i].roles.aux1){
      levelsMap[i]["LEVEL_AUX1"] = "checked";
    }else{
      levelsMap[i]["LEVEL_AUX1"] = "";
    }

    if(webConfig.levelConfigs[i].roles.aux2){
      levelsMap[i]["LEVEL_AUX2"] = "checked";
    }else{
      levelsMap[i]["LEVEL_AUX2"] = "";
    }

    if(webConfig.levelConfigs[i].roles.strobe1){
      levelsMap[i]["LEVEL_STROBE1"] = "checked";
    }else{
      levelsMap[i]["LEVEL_STROBE1"] = "";
    }

    if(webConfig.levelConfigs[i].roles.strobe2){
      levelsMap[i]["LEVEL_STROBE2"] = "checked";
    }else{
      levelsMap[i]["LEVEL_STROBE2"] = "";
    }

    if(webConfig.levelConfigs[i].animations.underglow){
      levelsMap[i]["LEVEL_UNDERGLOW"] = "checked";
    }else{
      levelsMap[i]["LEVEL_UNDERGLOW"] = "";
    }

    if(webConfig.levelConfigs[i].animations.throttleBrakeLight){
      levelsMap[i]["LEVEL_THROTTLE_LIGHT"] = "checked";
    }else{
      levelsMap[i]["LEVEL_THROTTLE_LIGHT"] = "";
    }

    if(webConfig.levelConfigs[i].animations.exhaustFlame){
      levelsMap[i]["LEVEL_EXHAUST"] = "checked";
    }else{
      levelsMap[i]["LEVEL_EXHAUST"] = "";
    }

    if(webConfig.levelConfigs[i].animations.policeLights){
      levelsMap[i]["LEVEL_POLICE"] = "checked";
    }else{
      levelsMap[i]["LEVEL_POLICE"] = "";
    }

    if(webConfig.levelConfigs[i].animations.cautionLights){
      levelsMap[i]["LEVEL_CAUTION"] = "checked";
    }else{
      levelsMap[i]["LEVEL_CAUTION"] = "";
    }
  }
}

void buildOutputMaps(){
  for(int i=0;i<12;i++){
    outputsMap[i]["OUT_NAME"] = "Output " + String(i+1);
    outputsMap[i]["OUT_NUM"] = "out_"+String(i+1)+"_tab";
    outputsMap[i]["OUT_IDX"] = String(i+1);
    
    if(webConfig.outputConfig.channelConfigs[i].type == SINGLE_LED){
      outputsMap[i]["OUT_TYPE_SINGLE"] = "selected";
    }else{
      outputsMap[i]["OUT_TYPE_SINGLE"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].type == LED_STRIP){
      outputsMap[i]["OUT_TYPE_STRIP"] = "selected";
    }else{
      outputsMap[i]["OUT_TYPE_STRIP"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].roles.leftTurn){
      outputsMap[i]["OUT_ROLE_LEFTTURN"] = "checked";
    }else{
      outputsMap[i]["OUT_ROLE_LEFTTURN"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].roles.rightTurn){
      outputsMap[i]["OUT_ROLE_RIGHTTURN"] = "checked";
    }else{
      outputsMap[i]["OUT_ROLE_RIGHTTURN"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].roles.brake){
      outputsMap[i]["OUT_ROLE_BRAKE"] = "checked";
    }else{
      outputsMap[i]["OUT_ROLE_BRAKE"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].roles.tail){
      outputsMap[i]["OUT_ROLE_TAIL"] = "checked";
    }else{
      outputsMap[i]["OUT_ROLE_TAIL"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].roles.head){
      outputsMap[i]["OUT_ROLE_HEAD"] = "checked";
    }else{
      outputsMap[i]["OUT_ROLE_HEAD"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].roles.reverse){
      outputsMap[i]["OUT_ROLE_REVERSE"] = "checked";
    }else{
      outputsMap[i]["OUT_ROLE_REVERSE"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].roles.hazard){
      outputsMap[i]["OUT_ROLE_HAZARD"] = "checked";
    }else{
      outputsMap[i]["OUT_ROLE_HAZARD"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].roles.running){
      outputsMap[i]["OUT_ROLE_RUNNING"] = "checked";
    }else{
      outputsMap[i]["OUT_ROLE_RUNNING"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].roles.aux1){
      outputsMap[i]["OUT_ROLE_AUX1"] = "checked";
    }else{
      outputsMap[i]["OUT_ROLE_AUX1"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].roles.aux2){
      outputsMap[i]["OUT_ROLE_AUX2"] = "checked";
    }else{
      outputsMap[i]["OUT_ROLE_AUX2"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].roles.strobe1){
      outputsMap[i]["OUT_ROLE_STROBE1"] = "checked";
    }else{
      outputsMap[i]["OUT_ROLE_STROBE1"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].roles.strobe2){
      outputsMap[i]["OUT_ROLE_STROBE2"] = "checked";
    }else{
      outputsMap[i]["OUT_ROLE_STROBE2"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].stripAnimation == UNDERGLOW_SOLID){
      outputsMap[i]["OUT_UNDERGLOW_SOLID"] = "selected";
    }else{
      outputsMap[i]["OUT_UNDERGLOW_SOLID"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].stripAnimation == UNDERGLOW_BREATHE){
      outputsMap[i]["OUT_UNDERGLOW_BREATHE"] = "selected";
    }else{
      outputsMap[i]["OUT_UNDERGLOW_BREATHE"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].stripAnimation == UNDERGLOW_CYCLE){
      outputsMap[i]["OUT_UNDERGLOW_CYCLE"] = "selected";
    }else{
      outputsMap[i]["OUT_UNDERGLOW_CYCLE"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].stripAnimation == THROTTLE_BRAKE_LIGHT_BOTTOM){
      outputsMap[i]["OUT_THROTTLE_LIGHT_BOTTOM"] = "selected";
    }else{
      outputsMap[i]["OUT_THROTTLE_LIGHT_BOTTOM"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].stripAnimation == THROTTLE_BRAKE_LIGHT_TOP){
      outputsMap[i]["OUT_THROTTLE_LIGHT_TOP"] = "selected";
    }else{
      outputsMap[i]["OUT_THROTTLE_LIGHT_TOP"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].stripAnimation == THROTTLE_BRAKE_LIGHT_MIDDLE){
      outputsMap[i]["OUT_THROTTLE_LIGHT_MID"] = "selected";
    }else{
      outputsMap[i]["OUT_THROTTLE_LIGHT_MID"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].stripAnimation == EXHAUST_FLAME){
      outputsMap[i]["OUT_EXHAUST_FLAME"] = "selected";
    }else{
      outputsMap[i]["OUT_EXHAUST_FLAME"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].stripAnimation == POLICE_LIGHTS_SOLID){
      outputsMap[i]["OUT_POLICE_LIGHTS_SOLID"] = "selected";
    }else{
      outputsMap[i]["OUT_POLICE_LIGHTS_SOLID"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].stripAnimation == POLICE_LIGHTS_WRAP){
      outputsMap[i]["OUT_POLICE_LIGHTS_WRAP"] = "selected";
    }else{
      outputsMap[i]["OUT_POLICE_LIGHTS_WRAP"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].stripAnimation == CAUTION_LIGHTS_SOLID){
      outputsMap[i]["OUT_CAUTION_LIGHTS_SOLID"] = "selected";
    }else{
      outputsMap[i]["OUT_CAUTION_LIGHTS_SOLID"] = "";
    }

    if(webConfig.outputConfig.channelConfigs[i].stripAnimation == CAUTION_LIGHTS_WRAP){
      outputsMap[i]["OUT_CAUTION_LIGHTS_WRAP"] = "selected";
    }else{
      outputsMap[i]["OUT_CAUTION_LIGHTS_WRAP"] = "";
    }

    char hexColor[8];
    sprintf(hexColor, "#%02X%02X%02X", webConfig.outputConfig.channelConfigs[i].color.r, webConfig.outputConfig.channelConfigs[i].color.g, webConfig.outputConfig.channelConfigs[i].color.b);
    outputsMap[i]["OUT_COLOR"] = String(hexColor);

    outputsMap[i]["OUT_NUM_LEDS"] = String(webConfig.outputConfig.channelConfigs[i].stripLedCount);

    outputsMap[i]["OUT_RGB"] = webConfig.outputConfig.channelConfigs[i].colorOrder == RGB ? "selected" : "";
    outputsMap[i]["OUT_GRB"] = webConfig.outputConfig.channelConfigs[i].colorOrder == GRB ? "selected" : "";
    outputsMap[i]["OUT_BRG"] = webConfig.outputConfig.channelConfigs[i].colorOrder == BRG ? "selected" : "";
    outputsMap[i]["OUT_RBG"] = webConfig.outputConfig.channelConfigs[i].colorOrder == RBG ? "selected" : "";
    outputsMap[i]["OUT_BGR"] = webConfig.outputConfig.channelConfigs[i].colorOrder == BGR ? "selected" : "";
    outputsMap[i]["OUT_GBR"] = webConfig.outputConfig.channelConfigs[i].colorOrder == GBR ? "selected" : "";
  }
}
