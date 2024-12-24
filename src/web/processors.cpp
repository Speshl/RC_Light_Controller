#include "web.h"

std::map<String, String> inputMap;
std::array<std::map<String, String>, NUM_LEVELS> levelsMap;
std::array<std::map<String, String>, MAX_CHANNELS> outputsBaseMap;
std::array<std::map<String, String>, MAX_CHANNELS> outputsRoleMap;
std::array<std::map<String, String>, MAX_CHANNELS> outputsStripMap;
std::array<std::map<String, String>, MAX_CHANNELS> outputsUnderglowMap;
std::array<std::map<String, String>, MAX_CHANNELS> outputsThrottleBrakeMap;
std::array<std::map<String, String>, MAX_CHANNELS> outputsExhaustMap;
std::array<std::map<String, String>, MAX_CHANNELS> outputsEmergencyMap;

String genericProcessor(const String& var, const std::map<String, String>& dataMap) {
  if (dataMap.count(var.c_str()) > 0) {
    return dataMap.at(var.c_str());
  } else {
    Serial.println("no match: " + var);
    return String("");
  }
}

String isSelected(bool selected) {
  return selected ? "selected" : "";
}

String isChecked(bool checked) {
  return checked ? "checked" : "";
}

std::function<String(const String&)> createProcessor(int index, ProcessorType type) {
  return [index, type](const String& var) -> String {
    if (index < 0 || index >= MAX_CHANNELS) {
        Serial.println("invalid index: " + String(index));
        return String("");
    }

    const std::map<String, String>* map = nullptr;

    switch (type) {
      case LEVEL_PROCESSOR:
        if (index >= NUM_LEVELS) {
          Serial.println("invalid level: " + String(index));
          return String("");
        }
        map = &levelsMap[index];
        break;
      case OUTPUT_BASE_PROCESSOR:
        map = &outputsBaseMap[index];
        break;
      case OUTPUT_ROLE_PROCESSOR:
        map = &outputsRoleMap[index];
        break;
      case OUTPUT_STRIP_PROCESSOR:
        map = &outputsStripMap[index];
        break;
      case OUTPUT_UNDERGLOW_PROCESSOR:
        map = &outputsUnderglowMap[index];
        break;
      case OUTPUT_THROTTLE_BRAKE_PROCESSOR:
        map = &outputsThrottleBrakeMap[index];
        break;
      case OUTPUT_EXHAUST_PROCESSOR:
        map = &outputsExhaustMap[index];
        break;
      case OUTPUT_EMERGENCY_PROCESSOR:
        map = &outputsEmergencyMap[index];
        break;
      case INPUT_PROCESSOR:
      default:
        map = &inputMap;
        break;
    }

    return genericProcessor(var, *map);
  };
}

std::function<String(const String&)> createDefaultProcessor() {
  return createProcessor(0, INPUT_PROCESSOR);
}

void buildInputMap(Config* webConfig){
  inputMap["INPUT_CRSF"] = isSelected(webConfig->inputConfig.type == CRSF);
  inputMap["INPUT_SBUS"] = isSelected(webConfig->inputConfig.type == SBUS);

  for(int i=1;i<9;i++){
    inputMap["INPUT_STEER_CHANNEL_" + String(i)] = isSelected(webConfig->inputConfig.steerChannel == i);
    inputMap["INPUT_ESC_CHANNEL_" + String(i)] = isSelected(webConfig->inputConfig.escChannel == i);
  }

  for(int i=10;i<17;i++){
    inputMap["INPUT_TRIGGER_CHANNEL_" + String(i)] = isSelected(webConfig->inputConfig.enableChannel == i);
    inputMap["INPUT_LEVEL_CHANNEL_" + String(i)] = isSelected(webConfig->inputConfig.levelChannel == i);
  }

  inputMap["INPUT_INVERT_STEER"] = isChecked(webConfig->inputConfig.steerInverted);
  inputMap["INPUT_INVERT_ESC"] = isChecked(webConfig->inputConfig.escInverted);
}

void buildLevelMaps(Config* webConfig){
  for(int i=0;i<3;i++){
    levelsMap[i]["LEVEL_NAME"] = "Level " + String(i+1);
    levelsMap[i]["LEVEL_NUM"] = "level_"+String(i+1)+"_tab";
    levelsMap[i]["LEVEL_IDX"] = String(i+1);

    levelsMap[i]["LEVEL_LEFTTURN"] = isChecked(webConfig->levelConfigs[i].roles.leftTurn);
    levelsMap[i]["LEVEL_RIGHTTURN"] = isChecked(webConfig->levelConfigs[i].roles.rightTurn);
    levelsMap[i]["LEVEL_BRAKE"] = isChecked(webConfig->levelConfigs[i].roles.brake);
    levelsMap[i]["LEVEL_TAIL"] = isChecked(webConfig->levelConfigs[i].roles.tail);
    levelsMap[i]["LEVEL_HEAD"] = isChecked(webConfig->levelConfigs[i].roles.head);
    levelsMap[i]["LEVEL_REVERSE"] = isChecked(webConfig->levelConfigs[i].roles.reverse);
    levelsMap[i]["LEVEL_HAZARD"] = isChecked(webConfig->levelConfigs[i].roles.hazard);
    levelsMap[i]["LEVEL_RUNNING"] = isChecked(webConfig->levelConfigs[i].roles.running);
    levelsMap[i]["LEVEL_AUX1"] = isChecked(webConfig->levelConfigs[i].roles.aux1);
    levelsMap[i]["LEVEL_AUX2"] = isChecked(webConfig->levelConfigs[i].roles.aux2);
    levelsMap[i]["LEVEL_STROBE1"] = isChecked(webConfig->levelConfigs[i].roles.strobe1);
    levelsMap[i]["LEVEL_STROBE2"] = isChecked(webConfig->levelConfigs[i].roles.strobe2);
    levelsMap[i]["LEVEL_UNDERGLOW"] = isChecked(webConfig->levelConfigs[i].animations.underglow);
    levelsMap[i]["LEVEL_THROTTLE_LIGHT"] = isChecked(webConfig->levelConfigs[i].animations.throttleBrakeLight);
    levelsMap[i]["LEVEL_EXHAUST"] = isChecked(webConfig->levelConfigs[i].animations.exhaustFlame);
    levelsMap[i]["LEVEL_EMERGENCY"] = isChecked(webConfig->levelConfigs[i].animations.emergencyLights);
  }
}

void buildOutputBaseMaps(Config * webConfig){
  for(int i=0;i<MAX_CHANNELS;i++){
    outputsBaseMap[i]["OUT_NAME"] = "Output " + String(i+1);
    outputsBaseMap[i]["OUT_NUM"] = "out_"+String(i+1)+"_tab";
    outputsBaseMap[i]["OUT_IDX"] = String(i+1);
    outputsBaseMap[i]["OUT_TYPE_FIELDS"] = "outputType" + String(i+1) + ".htm";

    outputsBaseMap[i]["OUT_TYPE_SINGLE"] = isSelected(webConfig->outputConfig.channelConfigs[i].type == SINGLE_LED);
    outputsBaseMap[i]["OUT_TYPE_STRIP"] = isSelected(webConfig->outputConfig.channelConfigs[i].type == LED_STRIP);
  }
}

void buildOutputRoleMaps(Config* webConfig){
  for(int i=0;i<MAX_CHANNELS;i++){
    outputsRoleMap[i]["OUT_ROLE_LEFTTURN"] = isChecked(webConfig->outputConfig.channelConfigs[i].roles.leftTurn);
    outputsRoleMap[i]["OUT_ROLE_RIGHTTURN"] = isChecked(webConfig->outputConfig.channelConfigs[i].roles.rightTurn);
    outputsRoleMap[i]["OUT_ROLE_BRAKE"] = isChecked(webConfig->outputConfig.channelConfigs[i].roles.brake);
    outputsRoleMap[i]["OUT_ROLE_TAIL"] = isChecked(webConfig->outputConfig.channelConfigs[i].roles.tail);
    outputsRoleMap[i]["OUT_ROLE_HEAD"] = isChecked(webConfig->outputConfig.channelConfigs[i].roles.head);
    outputsRoleMap[i]["OUT_ROLE_REVERSE"] = isChecked(webConfig->outputConfig.channelConfigs[i].roles.reverse);
    outputsRoleMap[i]["OUT_ROLE_HAZARD"] = isChecked(webConfig->outputConfig.channelConfigs[i].roles.hazard);
    outputsRoleMap[i]["OUT_ROLE_RUNNING"] = isChecked(webConfig->outputConfig.channelConfigs[i].roles.running);
    outputsRoleMap[i]["OUT_ROLE_AUX1"] = isChecked(webConfig->outputConfig.channelConfigs[i].roles.aux1);
    outputsRoleMap[i]["OUT_ROLE_AUX2"] = isChecked(webConfig->outputConfig.channelConfigs[i].roles.aux2);
    outputsRoleMap[i]["OUT_ROLE_STROBE1"] = isChecked(webConfig->outputConfig.channelConfigs[i].roles.strobe1);
    outputsRoleMap[i]["OUT_ROLE_STROBE2"] = isChecked(webConfig->outputConfig.channelConfigs[i].roles.strobe2);
  }
}

void buildOutputStripMaps(Config* webConfig){
  for(int i=0;i<MAX_CHANNELS;i++){
    outputsStripMap[i]["OUT_UNDERGLOW"] = isSelected(webConfig->outputConfig.channelConfigs[i].stripAnimation == UNDERGLOW);
    outputsStripMap[i]["OUT_THROTTLE_BRAKE"] = isSelected(webConfig->outputConfig.channelConfigs[i].stripAnimation == THROTTLE_BRAKE);
    outputsStripMap[i]["OUT_EXHAUST"] = isSelected(webConfig->outputConfig.channelConfigs[i].stripAnimation == EXHAUST);
    outputsStripMap[i]["OUT_EMERGENCY"] = isSelected(webConfig->outputConfig.channelConfigs[i].stripAnimation == EMERGENCY);

    outputsStripMap[i]["OUT_NUM_LEDS"] = String(webConfig->outputConfig.channelConfigs[i].stripLedCount);

    outputsStripMap[i]["OUT_RGB"] = isSelected(webConfig->outputConfig.channelConfigs[i].colorOrder == RGB);
    outputsStripMap[i]["OUT_GRB"] = isSelected(webConfig->outputConfig.channelConfigs[i].colorOrder == GRB);
    outputsStripMap[i]["OUT_BRG"] = isSelected(webConfig->outputConfig.channelConfigs[i].colorOrder == BRG);
    outputsStripMap[i]["OUT_RBG"] = isSelected(webConfig->outputConfig.channelConfigs[i].colorOrder == RBG);
    outputsStripMap[i]["OUT_BGR"] = isSelected(webConfig->outputConfig.channelConfigs[i].colorOrder == BGR);
    outputsStripMap[i]["OUT_GBR"] = isSelected(webConfig->outputConfig.channelConfigs[i].colorOrder == GBR);

    outputsStripMap[i]["OUT_UNDERGLOW"] = isSelected(webConfig->outputConfig.channelConfigs[i].stripAnimation == UNDERGLOW);
    outputsStripMap[i]["OUT_THROTTLE_BRAKE"] = isSelected(webConfig->outputConfig.channelConfigs[i].stripAnimation == THROTTLE_BRAKE);
    outputsStripMap[i]["OUT_EXHAUST"] = isSelected(webConfig->outputConfig.channelConfigs[i].stripAnimation == EXHAUST);
    outputsStripMap[i]["OUT_EMERGENCY"] = isSelected(webConfig->outputConfig.channelConfigs[i].stripAnimation == EMERGENCY);

    outputsStripMap[i]["OUT_ANIMATION_FIELDS"] = "outputAnimation" + String(i+1) + ".htm";
  }
}

void buildOutputUnderglowMap(Config * webConfig){
  for(int i=0;i<MAX_CHANNELS;i++){
    outputsUnderglowMap[i]["UNDERGLOW_SOLID"] = isSelected(webConfig->outputConfig.channelConfigs[i].underglowConfig.type == UNDERGLOW_SOLID);
    outputsUnderglowMap[i]["UNDERGLOW_BREATH"] = isSelected(webConfig->outputConfig.channelConfigs[i].underglowConfig.type == UNDERGLOW_BREATHE);
    outputsUnderglowMap[i]["UNDERGLOW_PALETTE"] = isSelected(webConfig->outputConfig.channelConfigs[i].underglowConfig.type == UNDERGLOW_PALETTE);

    char primary[8];
    sprintf(primary, "#%02X%02X%02X",
      webConfig->outputConfig.channelConfigs[i].underglowConfig.primaryColor.r,
      webConfig->outputConfig.channelConfigs[i].underglowConfig.primaryColor.g,
      webConfig->outputConfig.channelConfigs[i].underglowConfig.primaryColor.b
    );
    outputsUnderglowMap[i]["PRIMARY_COLOR"] = String(primary);

    char secondary[8];
    sprintf(secondary, "#%02X%02X%02X",
      webConfig->outputConfig.channelConfigs[i].underglowConfig.secondaryColor.r,
      webConfig->outputConfig.channelConfigs[i].underglowConfig.secondaryColor.g,
      webConfig->outputConfig.channelConfigs[i].underglowConfig.secondaryColor.b
    );
    outputsUnderglowMap[i]["SECONDARY_COLOR"] = String(secondary);

    outputsUnderglowMap[i]["UNDERGLOW_PALETTE_RAINBOW"] = isSelected(webConfig->outputConfig.channelConfigs[i].underglowConfig.palette == UNDERGLOW_RAINBOW);
    outputsUnderglowMap[i]["UNDERGLOW_PALETTE_CLOUD"] = isSelected(webConfig->outputConfig.channelConfigs[i].underglowConfig.palette == UNDERGLOW_CLOUD);
    outputsUnderglowMap[i]["UNDERGLOW_PALETTE_LAVA"] = isSelected(webConfig->outputConfig.channelConfigs[i].underglowConfig.palette == UNDERGLOW_LAVA);
    outputsUnderglowMap[i]["UNDERGLOW_PALETTE_OCEAN"] = isSelected(webConfig->outputConfig.channelConfigs[i].underglowConfig.palette == UNDERGLOW_OCEAN);
    outputsUnderglowMap[i]["UNDERGLOW_PALETTE_FOREST"] = isSelected(webConfig->outputConfig.channelConfigs[i].underglowConfig.palette == UNDERGLOW_FOREST);
    outputsUnderglowMap[i]["UNDERGLOW_PALETTE_PARTY"] = isSelected(webConfig->outputConfig.channelConfigs[i].underglowConfig.palette == UNDERGLOW_PARTY);
    outputsUnderglowMap[i]["UNDERGLOW_PALETTE_HEAT"] = isSelected(webConfig->outputConfig.channelConfigs[i].underglowConfig.palette == UNDERGLOW_HEAT);
  }
}

void buildOutputThrottleBrakeMap(Config * webConfig){
  for(int i=0;i<MAX_CHANNELS;i++){
    outputsThrottleBrakeMap[i]["TB_TOP"] = isSelected(webConfig->outputConfig.channelConfigs[i].throttleBrakeConfig.type == TB_TOP);
    outputsThrottleBrakeMap[i]["TB_MID"] = isSelected(webConfig->outputConfig.channelConfigs[i].throttleBrakeConfig.type == TB_MID);
    outputsThrottleBrakeMap[i]["TB_BOTTOM"] = isSelected(webConfig->outputConfig.channelConfigs[i].throttleBrakeConfig.type == TB_BOTTOM);

    char throttle[8];
    sprintf(throttle, "#%02X%02X%02X",
      webConfig->outputConfig.channelConfigs[i].throttleBrakeConfig.throttleColor.r,
      webConfig->outputConfig.channelConfigs[i].throttleBrakeConfig.throttleColor.g,
      webConfig->outputConfig.channelConfigs[i].throttleBrakeConfig.throttleColor.b
    );
    outputsThrottleBrakeMap[i]["THROTTLE_COLOR"] = String(throttle);

    char brake[8];
    sprintf(brake, "#%02X%02X%02X",
      webConfig->outputConfig.channelConfigs[i].throttleBrakeConfig.brakeColor.r,
      webConfig->outputConfig.channelConfigs[i].throttleBrakeConfig.brakeColor.g,
      webConfig->outputConfig.channelConfigs[i].throttleBrakeConfig.brakeColor.b
    );
    outputsThrottleBrakeMap[i]["BRAKE_COLOR"] = String(brake);
  }
}

void buildOutputExhaustMap(Config * webConfig){
  for(int i=0;i<MAX_CHANNELS;i++){
    outputsExhaustMap[i]["FLAME_COLOR_PALETTE_DEFAULT"] = isSelected(webConfig->outputConfig.channelConfigs[i].exhaustConfig.palette == DEFAULT_EXHAUST_PALETTE);
    outputsExhaustMap[i]["FLAME_COLOR_PALETTE_BLUE"] = isSelected(webConfig->outputConfig.channelConfigs[i].exhaustConfig.palette == BLUE_EXHAUST_PALETTE);
    outputsExhaustMap[i]["FLAME_COLOR_PALETTE_GREEN"] = isSelected(webConfig->outputConfig.channelConfigs[i].exhaustConfig.palette == GREEN_EXHAUST_PALETTE);  
    outputsExhaustMap[i]["FLAME_COLOR_PALETTE_PURPLE"] = isSelected(webConfig->outputConfig.channelConfigs[i].exhaustConfig.palette == PURPLE_EXHAUST_PALETTE);
    outputsExhaustMap[i]["FLAME_COLOR_PALETTE_CYAN"] = isSelected(webConfig->outputConfig.channelConfigs[i].exhaustConfig.palette == CYAN_EXHAUST_PALETTE);
    outputsExhaustMap[i]["FLAME_COLOR_PALETTE_RAINBOW"] = isSelected(webConfig->outputConfig.channelConfigs[i].exhaustConfig.palette == RAINBOW_EXHAUST_PALETTE);
  }
}

void buildOutputEmergencyMap(Config * webConfig){
  for(int i=0;i<MAX_CHANNELS;i++){
    outputsEmergencyMap[i]["EMERGENCY_SOLID"] = isSelected(webConfig->outputConfig.channelConfigs[i].emergencyConfig.type == EMERGENCY_SOLID);
    outputsEmergencyMap[i]["EMERGENCY_WRAP"] = isSelected(webConfig->outputConfig.channelConfigs[i].emergencyConfig.type == EMERGENCY_WRAP);
    
    char primary[8];
    sprintf(primary, "#%02X%02X%02X",
      webConfig->outputConfig.channelConfigs[i].emergencyConfig.primaryColor.r,
      webConfig->outputConfig.channelConfigs[i].emergencyConfig.primaryColor.g,
      webConfig->outputConfig.channelConfigs[i].emergencyConfig.primaryColor.b
    );
    outputsEmergencyMap[i]["PRIMARY_COLOR"] = String(primary);

    char secondary[8];
    sprintf(secondary, "#%02X%02X%02X",
      webConfig->outputConfig.channelConfigs[i].emergencyConfig.secondaryColor.r,
      webConfig->outputConfig.channelConfigs[i].emergencyConfig.secondaryColor.g,
      webConfig->outputConfig.channelConfigs[i].emergencyConfig.secondaryColor.b
    );
    outputsEmergencyMap[i]["SECONDARY_COLOR"] = String(secondary);
  }
}

void buildMaps(Config* webConfig){
  buildInputMap(webConfig);
  buildLevelMaps(webConfig);

  buildOutputBaseMaps(webConfig);
  buildOutputRoleMaps(webConfig);
  buildOutputStripMaps(webConfig);

  buildOutputUnderglowMap(webConfig);
  buildOutputThrottleBrakeMap(webConfig);
  buildOutputExhaustMap(webConfig);
  buildOutputEmergencyMap(webConfig);
}