#include "config.h"

Config config;

Config GetBaseConfig(){
  Config cfg;

  cfg.sysConfig.forcedShutdown = false;
  
  for(int i=0; i<MAX_CHANNELS; i++){
    cfg.outputConfig.channelConfigs[i].pin = pinNums[i];
  }
  return cfg;
}

void saveConfigToFile(Config *cfg, const char* filename) {
  Serial.println("Saving config to file");
  String jsonString;
  JsonDocument doc = ConfigToJson(cfg);
  serializeJson(doc, jsonString);

  // Open the file for writing
  File file = SPIFFS.open(filename, "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  // Write the JSON string to the file
  file.print(jsonString);
  file.close();

  Serial.println("Config saved to file");
}

void SaveConfig(Config cfg){
  saveConfigToFile(&cfg, CONFIG_FILE_PATH);
}

void SaveConfigWithRestart(Config cfg){
  cfg.sysConfig.forcedShutdown = true;
  SaveConfig(cfg);
  Serial.println("Restarting to apply new config...");
  ESP.restart();
}

Config loadConfigFromFile(const char* filename) {
  Serial.println("Opening config file");
  File file = SPIFFS.open(filename, "r");
  if (!file) {
    Serial.println("Failed to open config file");
    return GetBaseConfig(); // Return default config or handle error as needed
  }

  JsonDocument doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.println("Failed to parse config file");
    file.close();
    return GetBaseConfig(); // Return default config or handle error as needed
  }

  // Close the file
  file.close();

  // Parse the JSON document into a Config object
  return parseConfig(doc);
}

Config GetDefaultConfig(){
  return loadConfigFromFile(DEFAULT_CONFIG_FILE_PATH);
}

Config CreateOrLoadCfg(){
  if (!SPIFFS.begin(true)) {
    Serial.println("an error has occurred while mounting SPIFFS");
    while(true);
  }

  if (SPIFFS.exists(FORCE_FILE_PATH) && ENABLE_FORCE_CONFIG){
    Serial.println("FORCED CONFIG DETECTED");
    config = loadConfigFromFile(FORCE_FILE_PATH);
    return config;
  }

  if (!SPIFFS.exists(CONFIG_FILE_PATH)) {
    Serial.println("Config file not found, creating from defaults");
    config = GetDefaultConfig();
    saveConfigToFile(&config, CONFIG_FILE_PATH);
  }

  Serial.println("Config file found, loading config");
  config = loadConfigFromFile(CONFIG_FILE_PATH);
  //PrintConfig(config);

  return config;
}

void PrintConfig(Config cfg){
  Serial.println("Config:");

  Serial.println("Input Config:");
  Serial.print("Type: ");
  Serial.println(cfg.inputConfig.type);
  Serial.print("Steer Channel: ");
  Serial.println(cfg.inputConfig.steerChannel);
  Serial.print("Steer Inverted: ");
  Serial.println(cfg.inputConfig.steerInverted);
  Serial.print("ESC Channel: ");
  Serial.println(cfg.inputConfig.escChannel);
  Serial.print("ESC Inverted: ");
  Serial.println(cfg.inputConfig.escInverted);
  Serial.print("Enable Channel: ");
  Serial.println(cfg.inputConfig.enableChannel);
  Serial.print("Enabled Inverted: ");
  Serial.println(cfg.inputConfig.enabledInverted);
  Serial.print("Level Channel: ");
  Serial.println(cfg.inputConfig.levelChannel);
  Serial.print("Level Inverted: ");
  Serial.println(cfg.inputConfig.levelInverted);

  Serial.println("Output Config:");
  for(int i=0; i<MAX_CHANNELS; i++){
    Serial.print("Channel ");
    Serial.println(i);
    Serial.print("Pin: ");
    Serial.println(cfg.outputConfig.channelConfigs[i].pin);
    Serial.print("Type: ");
    Serial.println(int32_t(cfg.outputConfig.channelConfigs[i].type));
    Serial.print("Strip Animation: ");
    Serial.println(int32_t(cfg.outputConfig.channelConfigs[i].stripAnimation));
    Serial.print("Order: ");
    Serial.println(ColorOrderToString(cfg.outputConfig.channelConfigs[i].colorOrder));
    Serial.println("Roles: ");
    Serial.print("Aux1: ");
    Serial.println(cfg.outputConfig.channelConfigs[i].roles.aux1);
    Serial.print("Aux2: ");
    Serial.println(cfg.outputConfig.channelConfigs[i].roles.aux2);
    Serial.print("Brake: ");
    Serial.println(cfg.outputConfig.channelConfigs[i].roles.brake);
    Serial.print("Head: ");
    Serial.println(cfg.outputConfig.channelConfigs[i].roles.head);
    Serial.print("Hazard: ");
    Serial.println(cfg.outputConfig.channelConfigs[i].roles.hazard);
    Serial.print("Left Turn: ");
    Serial.println(cfg.outputConfig.channelConfigs[i].roles.leftTurn);
    Serial.print("Reverse: ");
    Serial.println(cfg.outputConfig.channelConfigs[i].roles.reverse);
    Serial.print("Right Turn: ");
    Serial.println(cfg.outputConfig.channelConfigs[i].roles.rightTurn);
    Serial.print("Running: ");
    Serial.println(cfg.outputConfig.channelConfigs[i].roles.running);
    Serial.print("Tail: ");
    Serial.println(cfg.outputConfig.channelConfigs[i].roles.tail);\
    Serial.print("StripLEDCount: ");
    Serial.println(cfg.outputConfig.channelConfigs[i].stripLedCount);
    Serial.print("Color: ");
    Serial.print("R: ");
    Serial.print(cfg.outputConfig.channelConfigs[i].color.r);
    Serial.print(", G: ");
    Serial.print(cfg.outputConfig.channelConfigs[i].color.g);
    Serial.print(", B: ");
    Serial.println(cfg.outputConfig.channelConfigs[i].color.b);
  }

  Serial.println("Level Config:");
  for(int i=0; i<NUM_LEVELS; i++){
    Serial.print("Level ");
    Serial.println(i);
    Serial.print("Roles: ");
    Serial.print("Hazard: ");
    Serial.println(cfg.levelConfigs[i].roles.hazard);
    Serial.print(" Left Turn: ");
    Serial.println(cfg.levelConfigs[i].roles.leftTurn);
    Serial.print(" Right Turn: ");
    Serial.println(cfg.levelConfigs[i].roles.rightTurn);
    Serial.print(" Brake: ");
    Serial.println(cfg.levelConfigs[i].roles.brake);
    Serial.print(" Head: ");
    Serial.println(cfg.levelConfigs[i].roles.head);
    Serial.print(" Reverse: ");
    Serial.println(cfg.levelConfigs[i].roles.reverse);
    Serial.print(" Tail: ");
    Serial.println(cfg.levelConfigs[i].roles.tail);
    Serial.print(" Aux1: ");
    Serial.println(cfg.levelConfigs[i].roles.aux1);
    Serial.print(" Aux2: ");
    Serial.println(cfg.levelConfigs[i].roles.aux2);
    Serial.println("Animations:");
    Serial.print(" Exhaust Flame: ");
    Serial.println(cfg.levelConfigs[i].animations.exhaustFlame);
    Serial.print(" Underglow: ");
    Serial.println(cfg.levelConfigs[i].animations.underglow);
    Serial.print(" Throttle Brake Light: ");
    Serial.println(cfg.levelConfigs[i].animations.throttleBrakeLight);
    Serial.print(" Police Lights: ");
    Serial.println(cfg.levelConfigs[i].animations.policeLights);
    Serial.print(" Caution Lights: ");
    Serial.println(cfg.levelConfigs[i].animations.cautionLights);
  }
}
