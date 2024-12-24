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

String BoolToString(bool value) {
  return value ? "on" : "off";
}

String ColorToHexString(const CRGB& color) {
  char hex[8];
  snprintf(hex, sizeof(hex), "#%02X%02X%02X", color.r, color.g, color.b);
  return String(hex);
}

const char* FlamePaletteToString(ExhaustPalette palette) {
  switch (palette) {
    case BLUE_EXHAUST_PALETTE: return "blue";
    case GREEN_EXHAUST_PALETTE: return "green";
    case PURPLE_EXHAUST_PALETTE: return "purple";
    case CYAN_EXHAUST_PALETTE: return "cyan";
    case RAINBOW_EXHAUST_PALETTE: return "rainbow";
    default: return "default";
  }
}

const char* StripAnimationToString(StripAnimation animation) {
  switch (animation) {
    case UNDERGLOW: return "underglow";
    case THROTTLE_BRAKE: return "throttle_brake";
    case EXHAUST: return "exhaust";
    case EMERGENCY: return "emergency";
    default: return "none";
  }
}

const char* UnderGlowTypeToString(UnderGlowType type) {
  switch (type) {
    case UNDERGLOW_BREATHE: return "breathe";
    case UNDERGLOW_PALETTE: return "palette";
    default: return "solid";
  }
}

const char* UnderGlowPaletteToString(UnderGlowPalette palette) {
  switch (palette) {
    case UNDERGLOW_RAINBOW: return "rainbow";
    case UNDERGLOW_CLOUD: return "cloud";
    case UNDERGLOW_LAVA: return "lava";
    case UNDERGLOW_OCEAN: return "ocean";
    case UNDERGLOW_FOREST: return "forest";
    case UNDERGLOW_PARTY: return "party";
    case UNDERGLOW_HEAT: return "heat";
    default: return "rainbow";
  }
}

const char* ThrottleBrakeTypeToString(ThrottleBrakeType type) {
  switch (type) {
    case TB_TOP: return "top";
    case TB_MID: return "mid";
    default: return "bottom";
  }
}

JsonDocument ConfigToJson(Config *cfg){
  JsonDocument jsonCfg;

  jsonCfg["input_config"] = InputConfigToJson(cfg);
  JsonArray levelCfgs = jsonCfg["level_configs"].to<JsonArray>();
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
  inputCfg["invert_steer"] =  BoolToString(cfg->inputConfig.steerInverted);
  inputCfg["esc_channel"] = cfg->inputConfig.escChannel;
  inputCfg["invert_esc"] = BoolToString(cfg->inputConfig.escInverted);
  inputCfg["trigger_channel"] = cfg->inputConfig.enableChannel;
  inputCfg["level_channel"] = cfg->inputConfig.levelChannel;
  return inputCfg;
}

JsonDocument LevelConfigToJson(Config *cfg, int levelNum){
  JsonDocument levelCfg;

  levelCfg["level_num"] = levelNum+1;
  levelCfg["level_leftTurn"] = BoolToString(cfg->levelConfigs[levelNum].roles.leftTurn);
  levelCfg["level_rightTurn"] = BoolToString(cfg->levelConfigs[levelNum].roles.rightTurn);
  levelCfg["level_brake"] = BoolToString(cfg->levelConfigs[levelNum].roles.brake);
  levelCfg["level_tail"] = BoolToString(cfg->levelConfigs[levelNum].roles.tail);
  levelCfg["level_head"] = BoolToString(cfg->levelConfigs[levelNum].roles.head);
  levelCfg["level_reverse"] = BoolToString(cfg->levelConfigs[levelNum].roles.reverse);
  levelCfg["level_hazard"] = BoolToString(cfg->levelConfigs[levelNum].roles.hazard);
  levelCfg["level_running"] = BoolToString(cfg->levelConfigs[levelNum].roles.running);
  levelCfg["level_aux1"] = BoolToString(cfg->levelConfigs[levelNum].roles.aux1);
  levelCfg["level_aux2"] = BoolToString(cfg->levelConfigs[levelNum].roles.aux2);
  levelCfg["level_strobe1"] = BoolToString(cfg->levelConfigs[levelNum].roles.strobe1);
  levelCfg["level_strobe2"] = BoolToString(cfg->levelConfigs[levelNum].roles.strobe2);
  levelCfg["level_underglow"] = BoolToString(cfg->levelConfigs[levelNum].animations.underglow);
  levelCfg["level_throttle_light"] = BoolToString(cfg->levelConfigs[levelNum].animations.throttleBrakeLight);
  levelCfg["level_exhaust"] = BoolToString(cfg->levelConfigs[levelNum].animations.exhaustFlame);
  levelCfg["level_emergency"] = BoolToString(cfg->levelConfigs[levelNum].animations.emergencyLights);

  return levelCfg;
}

JsonDocument RoleConfigToJson(Config *cfg, int outNum){
  JsonDocument roleCfg;

  if(cfg->outputConfig.channelConfigs[outNum].type != SINGLE_LED){
    return roleCfg;
  }

  roleCfg["leftTurn"] = BoolToString(cfg->outputConfig.channelConfigs[outNum].roles.leftTurn);
  roleCfg["rightTurn"] = BoolToString(cfg->outputConfig.channelConfigs[outNum].roles.rightTurn);
  roleCfg["brake"] = BoolToString(cfg->outputConfig.channelConfigs[outNum].roles.brake);
  roleCfg["tail"] = BoolToString(cfg->outputConfig.channelConfigs[outNum].roles.tail);
  roleCfg["head"] = BoolToString(cfg->outputConfig.channelConfigs[outNum].roles.head);
  roleCfg["reverse"] = BoolToString(cfg->outputConfig.channelConfigs[outNum].roles.reverse);
  roleCfg["hazard"] = BoolToString(cfg->outputConfig.channelConfigs[outNum].roles.hazard);
  roleCfg["running"] = BoolToString(cfg->outputConfig.channelConfigs[outNum].roles.running);
  roleCfg["aux1"] = BoolToString(cfg->outputConfig.channelConfigs[outNum].roles.aux1);
  roleCfg["aux2"] = BoolToString(cfg->outputConfig.channelConfigs[outNum].roles.aux2);
  roleCfg["strobe1"] = BoolToString(cfg->outputConfig.channelConfigs[outNum].roles.strobe1);
  roleCfg["strobe2"] = BoolToString(cfg->outputConfig.channelConfigs[outNum].roles.strobe2);

  return roleCfg;
}

JsonDocument ExhaustConfigToJson(Config *cfg, int outNum){
  JsonDocument exhaustCfg;

  if(cfg->outputConfig.channelConfigs[outNum].type != LED_STRIP || cfg->outputConfig.channelConfigs[outNum].stripAnimation != EXHAUST){
    return exhaustCfg;
  }

  exhaustCfg["exhaust_palette"] = FlamePaletteToString(cfg->outputConfig.channelConfigs[outNum].exhaustConfig.palette);

  return exhaustCfg;
}

JsonDocument ThrottleBrakeConfigToJson(Config *cfg, int outNum){
  JsonDocument tbCfg;

  if(cfg->outputConfig.channelConfigs[outNum].type != LED_STRIP || cfg->outputConfig.channelConfigs[outNum].stripAnimation != THROTTLE_BRAKE){
    return tbCfg;
  }

  tbCfg["tb_type"] = ThrottleBrakeTypeToString(cfg->outputConfig.channelConfigs[outNum].throttleBrakeConfig.type);

  tbCfg["throttle_color"] = ColorToHexString(cfg->outputConfig.channelConfigs[outNum].throttleBrakeConfig.throttleColor);
  tbCfg["brake_color"] = ColorToHexString(cfg->outputConfig.channelConfigs[outNum].throttleBrakeConfig.brakeColor);

  return tbCfg;
}

JsonDocument UnderglowConfigToJson(Config *cfg, int outNum){
  JsonDocument ugCfg;

  if(cfg->outputConfig.channelConfigs[outNum].type != LED_STRIP || cfg->outputConfig.channelConfigs[outNum].stripAnimation != UNDERGLOW){
    return ugCfg;
  }

  ugCfg["ug_type"] = UnderGlowTypeToString(cfg->outputConfig.channelConfigs[outNum].underglowConfig.type);
  ugCfg["primary_color"] = ColorToHexString(cfg->outputConfig.channelConfigs[outNum].underglowConfig.primaryColor);
  ugCfg["secondary_color"] = ColorToHexString(cfg->outputConfig.channelConfigs[outNum].underglowConfig.secondaryColor);
  ugCfg["ug_palette"] = UnderGlowPaletteToString(cfg->outputConfig.channelConfigs[outNum].underglowConfig.palette);

  return ugCfg;
}

JsonDocument EmergencyConfigToJson(Config *cfg, int outNum){
  JsonDocument emCfg;

  if(cfg->outputConfig.channelConfigs[outNum].type != LED_STRIP || cfg->outputConfig.channelConfigs[outNum].stripAnimation != EMERGENCY){
    return emCfg;
  }

  emCfg["em_type"] = cfg->outputConfig.channelConfigs[outNum].emergencyConfig.type == EMERGENCY_WRAP ? "wrap" : "solid";
  emCfg["primary_color"] = ColorToHexString(cfg->outputConfig.channelConfigs[outNum].emergencyConfig.primaryColor);
  emCfg["secondary_color"] = ColorToHexString(cfg->outputConfig.channelConfigs[outNum].emergencyConfig.secondaryColor);

  return emCfg;
}

JsonDocument OutConfigToJson(Config *cfg, int outNum){
  JsonDocument outCfg;

  outCfg["out_num"] = outNum+1;
  outCfg["out_type"] = cfg->outputConfig.channelConfigs[outNum].type == SINGLE_LED ? "single" : "strip";
  outCfg["out_order"] = String(ColorOrderToString(cfg->outputConfig.channelConfigs[outNum].colorOrder));
  outCfg["out_num_leds"] = cfg->outputConfig.channelConfigs[outNum].stripLedCount;

  outCfg["out_animation"] = StripAnimationToString(cfg->outputConfig.channelConfigs[outNum].stripAnimation);
  outCfg["out_roles"] = RoleConfigToJson(cfg, outNum);
  outCfg["out_exhaust"] = ExhaustConfigToJson(cfg, outNum);
  outCfg["out_throttle_brake"] = ThrottleBrakeConfigToJson(cfg, outNum);
  outCfg["out_underglow"] = UnderglowConfigToJson(cfg, outNum);
  outCfg["out_emergency"] = EmergencyConfigToJson(cfg, outNum);

  return outCfg;
}