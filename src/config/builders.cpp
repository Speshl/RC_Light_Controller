#include "config.h"

const char* ColorOrderToString(EOrder order) {
    switch (order) {
        case RGB: return "RGB";
        case RBG: return "RBG";
        case GRB: return "GRB";
        case GBR: return "GBR";
        case BRG: return "BRG";
        case BGR: return "BGR";
        default: return "RGB";
    }
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
  levelCfg["level_emergency"] = cfg->levelConfigs[levelNum].animations.emergencyLights ? "on" : "off";

  return levelCfg;
}

JsonDocument OutConfigToJson(Config *cfg, int outNum){
  JsonDocument outCfg;

  outCfg["out_num"] = String(outNum+1);
  outCfg["out_type"] = cfg->outputConfig.channelConfigs[outNum].type == SINGLE_LED ? "single" : "strip";
  outCfg["out_order"] = String(ColorOrderToString(cfg->outputConfig.channelConfigs[outNum].colorOrder));
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