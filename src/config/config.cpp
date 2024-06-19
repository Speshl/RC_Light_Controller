#include "config.h"

Preferences preferences;
Config config;

void PrintConfig(){
  Serial.println("Config:");

  Serial.println("Input Config:");
  Serial.print("Type: ");
  Serial.println(config.inputConfig.type);
  Serial.print("Steer Channel: ");
  Serial.println(config.inputConfig.steerChannel);
  Serial.print("Steer Inverted: ");
  Serial.println(config.inputConfig.steerInverted);
  Serial.print("ESC Channel: ");
  Serial.println(config.inputConfig.escChannel);
  Serial.print("ESC Inverted: ");
  Serial.println(config.inputConfig.escInverted);
  Serial.print("Enable Channel: ");
  Serial.println(config.inputConfig.enableChannel);
  Serial.print("Enabled Inverted: ");
  Serial.println(config.inputConfig.enabledInverted);
  Serial.print("Level Channel: ");
  Serial.println(config.inputConfig.levelChannel);
  Serial.print("Level Inverted: ");
  Serial.println(config.inputConfig.levelInverted);

  Serial.println("Output Config:");
  for(int i=0; i<MAX_CHANNELS; i++){
    Serial.print("Channel ");
    Serial.println(i);
    Serial.print("Pin: ");
    Serial.println(config.outputConfig.channelConfigs[i].pin);
    Serial.print("Type: ");
    Serial.println(int32_t(config.outputConfig.channelConfigs[i].type));
    Serial.print("Strip Animation: ");
    Serial.println(int32_t(config.outputConfig.channelConfigs[i].stripAnimation));
    Serial.println("Roles: ");
    Serial.print("Aux1: ");
    Serial.println(config.outputConfig.channelConfigs[i].roles.aux1);
    Serial.print("Aux2: ");
    Serial.println(config.outputConfig.channelConfigs[i].roles.aux2);
    Serial.print("Brake: ");
    Serial.println(config.outputConfig.channelConfigs[i].roles.brake);
    Serial.print("Head: ");
    Serial.println(config.outputConfig.channelConfigs[i].roles.head);
    Serial.print("Hazard: ");
    Serial.println(config.outputConfig.channelConfigs[i].roles.hazard);
    Serial.print("Left Turn: ");
    Serial.println(config.outputConfig.channelConfigs[i].roles.leftTurn);
    Serial.print("Reverse: ");
    Serial.println(config.outputConfig.channelConfigs[i].roles.reverse);
    Serial.print("Right Turn: ");
    Serial.println(config.outputConfig.channelConfigs[i].roles.rightTurn);
    Serial.print("Running: ");
    Serial.println(config.outputConfig.channelConfigs[i].roles.running);
    Serial.print("Tail: ");
    Serial.println(config.outputConfig.channelConfigs[i].roles.tail);\
    Serial.print("StripLEDCount: ");
    Serial.println(config.outputConfig.channelConfigs[i].stripLedCount);
    Serial.print("Color: ");
    Serial.print("R: ");
    Serial.print(config.outputConfig.channelConfigs[i].color.r);
    Serial.print(", G: ");
    Serial.print(config.outputConfig.channelConfigs[i].color.g);
    Serial.print(", B: ");
    Serial.println(config.outputConfig.channelConfigs[i].color.b);
  }

  Serial.println("Level Config:");
  for(int i=0; i<NUM_LEVELS; i++){
    Serial.print("Level ");
    Serial.println(i);
    Serial.print("Roles: ");
    Serial.print("Hazard: ");
    Serial.println(config.levelConfigs[i].roles.hazard);
    Serial.print(" Left Turn: ");
    Serial.println(config.levelConfigs[i].roles.leftTurn);
    Serial.print(" Right Turn: ");
    Serial.println(config.levelConfigs[i].roles.rightTurn);
    Serial.print(" Brake: ");
    Serial.println(config.levelConfigs[i].roles.brake);
    Serial.print(" Head: ");
    Serial.println(config.levelConfigs[i].roles.head);
    Serial.print(" Reverse: ");
    Serial.println(config.levelConfigs[i].roles.reverse);
    Serial.print(" Tail: ");
    Serial.println(config.levelConfigs[i].roles.tail);
    Serial.print(" Aux1: ");
    Serial.println(config.levelConfigs[i].roles.aux1);
    Serial.print(" Aux2: ");
    Serial.println(config.levelConfigs[i].roles.aux2);
    Serial.println("Animations:");
    Serial.print(" Exhaust Flame: ");
    Serial.println(config.levelConfigs[i].animations.exhaustFlame);
    Serial.print(" Underglow: ");
    Serial.println(config.levelConfigs[i].animations.underglow);
    Serial.print(" Throttle Brake Light: ");
    Serial.println(config.levelConfigs[i].animations.throttleBrakeLight);
    Serial.print(" Police Lights: ");
    Serial.println(config.levelConfigs[i].animations.policeLights);
    Serial.print(" Caution Lights: ");
    Serial.println(config.levelConfigs[i].animations.cautionLights);
  }
}

Config LoadConfig(){
  bool cfgFound = preferences.getBool("cfgFound", false);
  if(!cfgFound){
    return GetDefaultConfig();
  }

  Serial.println("loading saved config");
  Config config;

  config.sysConfig.forcedShutdown = preferences.getBool("shutdown", false);

  config.inputConfig.type = InputType(preferences.getChar("1", 0));
  config.inputConfig.steerChannel = preferences.getChar("2", STEER_CHANNEL);
  config.inputConfig.steerInverted = preferences.getBool("3", false);
  config.inputConfig.escChannel = preferences.getChar("4", ESC_CHANNEL);
  config.inputConfig.escInverted = preferences.getBool("5", false);
  config.inputConfig.enableChannel = preferences.getChar("6", SYSTEM_ENABLE_CHANNEL);
  config.inputConfig.enabledInverted = preferences.getBool("7", false);
  config.inputConfig.levelChannel = preferences.getChar("8", LIGHT_LEVEL_CHANNEL);
  config.inputConfig.levelInverted = preferences.getBool("9", false);

  for(byte i=0; i<MAX_CHANNELS; i++){
    config.outputConfig.channelConfigs[i].pin = preferences.getChar((String(i)+String("_0_0")).c_str(), 0);
    config.outputConfig.channelConfigs[i].type = OutputType(preferences.getChar((String(i)+String("_0_1")).c_str(), pinNums[i]));
    config.outputConfig.channelConfigs[i].stripAnimation = StripAnimation(preferences.getChar((String(i)+String("_0_2")).c_str(), 0));
    config.outputConfig.channelConfigs[i].roles.aux1 = bool(preferences.getBool((String(i)+String("_0_3")).c_str(), 0));
    config.outputConfig.channelConfigs[i].roles.aux2 = bool(preferences.getBool((String(i)+String("_0_4")).c_str(), 0));
    config.outputConfig.channelConfigs[i].roles.brake = bool(preferences.getBool((String(i)+String("_0_5")).c_str(), 0));
    config.outputConfig.channelConfigs[i].roles.head = bool(preferences.getBool((String(i)+String("_0_6")).c_str(), 0));
    config.outputConfig.channelConfigs[i].roles.hazard = bool(preferences.getBool((String(i)+String("_0_7")).c_str(), 0));
    config.outputConfig.channelConfigs[i].roles.leftTurn = bool(preferences.getBool((String(i)+String("_0_8")).c_str(), 0));
    config.outputConfig.channelConfigs[i].roles.reverse = bool(preferences.getBool((String(i)+String("_0_9")).c_str(), 0));
    config.outputConfig.channelConfigs[i].roles.rightTurn = bool(preferences.getBool((String(i)+String("_0_10")).c_str(), 0));
    config.outputConfig.channelConfigs[i].roles.running = bool(preferences.getBool((String(i)+String("_0_11")).c_str(), 0));
    config.outputConfig.channelConfigs[i].roles.tail = bool(preferences.getBool((String(i)+String("_0_12")).c_str(), 0));
    config.outputConfig.channelConfigs[i].stripLedCount = preferences.getChar((String(i)+String("_0_13")).c_str(), 0);
    preferences.getBytes((String(i)+String("_0_14")).c_str(), config.outputConfig.channelConfigs[i].color.raw, 3);
    config.outputConfig.channelConfigs[i].roles.strobe1 = bool(preferences.getBool((String(i)+String("_0_15")).c_str(), 0));
    config.outputConfig.channelConfigs[i].roles.strobe2 = bool(preferences.getBool((String(i)+String("_0_16")).c_str(), 0));
    config.outputConfig.channelConfigs[i].colorOrder = EOrder(preferences.getInt((String(i)+String("_0_17")).c_str(), 0));
  }

  for(int i=0; i<NUM_LEVELS; i++){
    config.levelConfigs[i].roles.hazard = preferences.getBool((String(i)+String("_1_0")).c_str(), false);
    config.levelConfigs[i].roles.leftTurn = preferences.getBool((String(i)+String("_1_1")).c_str(), false);
    config.levelConfigs[i].roles.rightTurn = preferences.getBool((String(i)+String("_1_2")).c_str(), false);
    config.levelConfigs[i].roles.brake = preferences.getBool((String(i)+String("_1_3")).c_str(), false);
    config.levelConfigs[i].roles.head = preferences.getBool((String(i)+String("_1_4")).c_str(), false);
    config.levelConfigs[i].roles.reverse = preferences.getBool((String(i)+String("_1_5")).c_str(), false);
    config.levelConfigs[i].roles.tail = preferences.getBool((String(i)+String("_1_6")).c_str(), false);
    config.levelConfigs[i].roles.aux1 = preferences.getBool((String(i)+String("_1_7")).c_str(), false);
    config.levelConfigs[i].roles.aux2 = preferences.getBool((String(i)+String("_1_8")).c_str(), false);

    config.levelConfigs[i].animations.exhaustFlame = preferences.getBool((String(i)+String("_1_9")).c_str(), false);
    config.levelConfigs[i].animations.underglow = preferences.getBool((String(i)+String("_1_10")).c_str(), false);
    config.levelConfigs[i].animations.throttleBrakeLight = preferences.getBool((String(i)+String("_1_11")).c_str(), false);
    config.levelConfigs[i].animations.policeLights = preferences.getBool((String(i)+String("_1_12")).c_str(), false);
    config.levelConfigs[i].animations.cautionLights = preferences.getBool((String(i)+String("_1_13")).c_str(), false);

    config.levelConfigs[i].roles.strobe1 = preferences.getBool((String(i)+String("_1_14")).c_str(), false);
    config.levelConfigs[i].roles.strobe2 = preferences.getBool((String(i)+String("_1_15")).c_str(), false);
    config.levelConfigs[i].roles.running = preferences.getBool((String(i)+String("_1_16")).c_str(), false);
  }

  return config;
}

void SaveConfigWithRestart(Config cfg){
  cfg.sysConfig.forcedShutdown = true;
  SaveConfig(cfg);
  Serial.println("Restarting to apply new config...");
  ESP.restart();
}

void SaveConfig(Config cfg){
  Serial.println("saving config");
  preferences.putBool("cfgFound", true);

  preferences.putBool("shutdown", cfg.sysConfig.forcedShutdown);

  preferences.putChar("1", byte(cfg.inputConfig.type));
  preferences.putChar("2", byte(cfg.inputConfig.steerChannel));
  preferences.putBool("3", cfg.inputConfig.steerInverted);
  preferences.putChar("4", byte(cfg.inputConfig.escChannel));
  preferences.putBool("5", cfg.inputConfig.escInverted);
  preferences.putChar("6", byte(cfg.inputConfig.enableChannel));
  preferences.putBool("7", cfg.inputConfig.enabledInverted);
  preferences.putChar("8", byte(cfg.inputConfig.levelChannel));
  preferences.putBool("9", cfg.inputConfig.levelInverted);

  for(byte i=0; i<MAX_CHANNELS; i++){
    preferences.putChar((String(i)+String("_0_0")).c_str(), cfg.outputConfig.channelConfigs[i].pin);
    preferences.putChar((String(i)+String("_0_1")).c_str(), byte(cfg.outputConfig.channelConfigs[i].type));
    preferences.putChar((String(i)+String("_0_2")).c_str(), byte(cfg.outputConfig.channelConfigs[i].stripAnimation));
    preferences.putBool((String(i)+String("_0_3")).c_str(), bool(cfg.outputConfig.channelConfigs[i].roles.aux1));
    preferences.putBool((String(i)+String("_0_4")).c_str(), bool(cfg.outputConfig.channelConfigs[i].roles.aux2));
    preferences.putBool((String(i)+String("_0_5")).c_str(), bool(cfg.outputConfig.channelConfigs[i].roles.brake));
    preferences.putBool((String(i)+String("_0_6")).c_str(), bool(cfg.outputConfig.channelConfigs[i].roles.head));
    preferences.putBool((String(i)+String("_0_7")).c_str(), bool(cfg.outputConfig.channelConfigs[i].roles.hazard));
    preferences.putBool((String(i)+String("_0_8")).c_str(), bool(cfg.outputConfig.channelConfigs[i].roles.leftTurn));
    preferences.putBool((String(i)+String("_0_9")).c_str(), bool(cfg.outputConfig.channelConfigs[i].roles.reverse));
    preferences.putBool((String(i)+String("_0_10")).c_str(), bool(cfg.outputConfig.channelConfigs[i].roles.rightTurn));
    preferences.putBool((String(i)+String("_0_11")).c_str(), bool(cfg.outputConfig.channelConfigs[i].roles.running));
    preferences.putBool((String(i)+String("_0_12")).c_str(), bool(cfg.outputConfig.channelConfigs[i].roles.tail));
    preferences.putChar((String(i)+String("_0_13")).c_str(), cfg.outputConfig.channelConfigs[i].stripLedCount);
    preferences.putBytes((String(i)+String("_0_14")).c_str(), cfg.outputConfig.channelConfigs[i].color.raw, 3);
    preferences.putBool((String(i)+String("_0_15")).c_str(), bool(cfg.outputConfig.channelConfigs[i].roles.strobe1));
    preferences.putBool((String(i)+String("_0_16")).c_str(), bool(cfg.outputConfig.channelConfigs[i].roles.strobe2));
    preferences.putInt((String(i)+String("_0_17")).c_str(), int(cfg.outputConfig.channelConfigs[i].colorOrder));
  }

  for(int i=0; i<NUM_LEVELS; i++){
    preferences.putBool((String(i)+String("_1_0")).c_str(), bool(cfg.levelConfigs[i].roles.hazard));
    preferences.putBool((String(i)+String("_1_1")).c_str(), bool(cfg.levelConfigs[i].roles.leftTurn));
    preferences.putBool((String(i)+String("_1_2")).c_str(), bool(cfg.levelConfigs[i].roles.rightTurn));
    preferences.putBool((String(i)+String("_1_3")).c_str(), bool(cfg.levelConfigs[i].roles.brake));
    preferences.putBool((String(i)+String("_1_4")).c_str(), bool(cfg.levelConfigs[i].roles.head));
    preferences.putBool((String(i)+String("_1_5")).c_str(), bool(cfg.levelConfigs[i].roles.reverse));
    preferences.putBool((String(i)+String("_1_6")).c_str(), bool(cfg.levelConfigs[i].roles.tail));
    preferences.putBool((String(i)+String("_1_7")).c_str(), bool(cfg.levelConfigs[i].roles.aux1));
    preferences.putBool((String(i)+String("_1_8")).c_str(), bool(cfg.levelConfigs[i].roles.aux2));
    preferences.putBool((String(i)+String("_1_9")).c_str(), bool(cfg.levelConfigs[i].animations.exhaustFlame));
    preferences.putBool((String(i)+String("_1_10")).c_str(), bool(cfg.levelConfigs[i].animations.underglow));
    preferences.putBool((String(i)+String("_1_11")).c_str(), bool(cfg.levelConfigs[i].animations.throttleBrakeLight));
    preferences.putBool((String(i)+String("_1_12")).c_str(), bool(cfg.levelConfigs[i].animations.policeLights));
    preferences.putBool((String(i)+String("_1_13")).c_str(), bool(cfg.levelConfigs[i].animations.cautionLights));
    preferences.putBool((String(i)+String("_1_14")).c_str(), bool(cfg.levelConfigs[i].roles.strobe1));
    preferences.putBool((String(i)+String("_1_15")).c_str(), bool(cfg.levelConfigs[i].roles.strobe2));
    preferences.putBool((String(i)+String("_1_16")).c_str(), bool(cfg.levelConfigs[i].roles.running));
  }

  return;
}

Config CreateOrLoadCfg(){
  preferences.begin("rclc", false);
  bool cfgFound = preferences.getBool("cfgFound", false);
  if(cfgFound){
    config = LoadConfig();
    // config = GetDefaultConfig();
    // SaveConfig(config);
    // config = LoadConfig();
  }else{
    config = GetDefaultConfig();
    SaveConfig(config);
    config = LoadConfig();
  }
  //PrintConfig();
  return config;
}