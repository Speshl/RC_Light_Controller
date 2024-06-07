#include "config.h"

Config GetDefaultConfig(){
  Config defaultConfig;
  Serial.println("loading default config");
  //input
  defaultConfig.signalType = SIGNAL_TYPE;
  defaultConfig.triggerChannel = SYSTEM_ENABLE_CHANNEL;
  defaultConfig.levelChannel = LIGHT_LEVEL_CHANNEL;

  //options
  defaultConfig.invertSteering = INVERT_STEER;
  defaultConfig.invertESC = INVERT_ESC;
  defaultConfig.enableTurnSignals = ENABLE_TURNSIGNALS;
  defaultConfig.turnSignalsAlsoHead = TURN_SIGNAL_ALSO_HEAD;
  defaultConfig.turnSignalsAlsoBrake = TURN_SIGNAL_ALSO_BRAKE;
  defaultConfig.enableHazards = ENABLE_HAZARDS;
  defaultConfig.enableFlash = ENABLE_FLASH;

  //levels
  //day lights
  defaultConfig.levelCfgs[0].hazards = true;
  defaultConfig.levelCfgs[0].turnSignals = true;
  defaultConfig.levelCfgs[0].brakes = true;
  defaultConfig.levelCfgs[0].headLights = false;
  defaultConfig.levelCfgs[0].driftLights = false;
  defaultConfig.levelCfgs[0].underglow = false;
  defaultConfig.levelCfgs[0].auxLights = false;
  defaultConfig.levelCfgs[0].exhaust = true;

    //night lights
  defaultConfig.levelCfgs[1].hazards = true;
  defaultConfig.levelCfgs[1].turnSignals = true;
  defaultConfig.levelCfgs[1].brakes = true;
  defaultConfig.levelCfgs[1].headLights = true;
  defaultConfig.levelCfgs[1].driftLights = false;
  defaultConfig.levelCfgs[1].underglow = false;
  defaultConfig.levelCfgs[1].auxLights = false;
  defaultConfig.levelCfgs[1].exhaust = true;

  //all lights
  defaultConfig.levelCfgs[2].hazards = true;
  defaultConfig.levelCfgs[2].turnSignals = true;
  defaultConfig.levelCfgs[2].brakes = true;
  defaultConfig.levelCfgs[2].headLights = true;
  defaultConfig.levelCfgs[2].driftLights = true;
  defaultConfig.levelCfgs[2].underglow = true;
  defaultConfig.levelCfgs[2].auxLights = true;
  defaultConfig.levelCfgs[2].exhaust = true;
  //end levels

  //light out 
  defaultConfig.outCfgs[0].lightType = RIGHT_FRONT_TURN;
  defaultConfig.outCfgs[0].flashGroup = OFF;

  defaultConfig.outCfgs[1].lightType = RIGHT_HEAD;
  defaultConfig.outCfgs[1].flashGroup = GROUP2;
  
  defaultConfig.outCfgs[2].lightType = LEFT_HEAD;
  defaultConfig.outCfgs[2].flashGroup = GROUP1;

  defaultConfig.outCfgs[3].lightType = LEFT_FRONT_TURN;
  defaultConfig.outCfgs[3].flashGroup = OFF;

  defaultConfig.outCfgs[4].lightType = LEFT_REAR_TURN;
  defaultConfig.outCfgs[4].flashGroup = OFF;

  defaultConfig.outCfgs[5].lightType = LEFT_BRAKE;
  defaultConfig.outCfgs[5].flashGroup = GROUP1;

  defaultConfig.outCfgs[6].lightType = RIGHT_BRAKE;
  defaultConfig.outCfgs[6].flashGroup = GROUP2;
  
  defaultConfig.outCfgs[7].lightType = RIGHT_REAR_TURN;
  defaultConfig.outCfgs[7].flashGroup = OFF;

  //strips
  defaultConfig.stripCfgs[0].stripType = DRIFT_LIGHT;
  defaultConfig.stripCfgs[0].numLeds = 13;
  defaultConfig.stripCfgs[0].driftLightType = MIDDLE_OUT;
  defaultConfig.stripCfgs[0].color = CRGB::Red;

  defaultConfig.stripCfgs[1].stripType = EXHAUST;
  defaultConfig.stripCfgs[1].numLeds = NUM_STRIP_LEDS;
  defaultConfig.stripCfgs[1].driftLightType = BACK_TO_FRONT;
  defaultConfig.stripCfgs[1].color = CRGB::Blue;

  defaultConfig.stripCfgs[2].stripType = UNDERGLOW;
  defaultConfig.stripCfgs[2].numLeds = NUM_STRIP_LEDS;
  defaultConfig.stripCfgs[2].driftLightType = FRONT_TO_BACK;
  defaultConfig.stripCfgs[2].color = CRGB::Green;

  return defaultConfig;
}

void PrintConfig(Config cfg){
  if(!Serial) return;

  Serial.println("Printing config:");
  Serial.print("Signal Type: ");
  Serial.println(cfg.signalType);
  Serial.print("Trigger Channel: ");
  Serial.println(cfg.triggerChannel);
  Serial.print("Level Channel: ");
  Serial.println(cfg.levelChannel);
  
  Serial.print("Invert Steering: ");
  Serial.println(cfg.invertSteering);
  Serial.print("Invert ESC: ");
  Serial.println(cfg.invertESC);
  Serial.print("Enable Turn Signals: ");
  Serial.println(cfg.enableTurnSignals);
  Serial.print("Turn Signals Also Head: ");
  Serial.println(cfg.turnSignalsAlsoHead);
  Serial.print("Turn Signals Also Brake: ");
  Serial.println(cfg.turnSignalsAlsoBrake);
  Serial.print("Enable Hazards: ");
  Serial.println(cfg.enableHazards);
  Serial.print("Enable Flash: ");
  Serial.println(cfg.enableFlash);
  
  Serial.println("Level Configurations:");
  for (int i = 0; i < NUM_LEVELS; i++) {
    Serial.print("Level ");
    Serial.println(i);
    Serial.print("Hazards: ");
    Serial.println(cfg.levelCfgs[i].hazards);
    Serial.print("Turn Signals: ");
    Serial.println(cfg.levelCfgs[i].turnSignals);
    Serial.print("Brakes: ");
    Serial.println(cfg.levelCfgs[i].brakes);
    Serial.print("Head Lights: ");
    Serial.println(cfg.levelCfgs[i].headLights);
    Serial.print("Drift Lights: ");
    Serial.println(cfg.levelCfgs[i].driftLights);
    Serial.print("Underglow: ");
    Serial.println(cfg.levelCfgs[i].underglow);
    Serial.print("Aux Lights: ");
    Serial.println(cfg.levelCfgs[i].auxLights);
    Serial.print("Exhaust: ");
    Serial.println(cfg.levelCfgs[i].exhaust);
  }
  
  Serial.println("Output Configurations:");
  for (int i = 0; i < NUM_LIGHT_OUTPUTS; i++) {
    Serial.print("Output ");
    Serial.println(i);
    Serial.print("Light Type: ");
    Serial.println(cfg.outCfgs[i].lightType);
    Serial.print("Flash Group: ");
    Serial.println(cfg.outCfgs[i].flashGroup);
  }
  
  Serial.println("Strip Configurations:");
  for (int i = 0; i < NUM_STRIPS; i++) {
    Serial.print("Strip ");
    Serial.println(i);
    Serial.print("Strip Type: ");
    Serial.println(cfg.stripCfgs[i].stripType);
    Serial.print("Number of LEDs: ");
    Serial.println(cfg.stripCfgs[i].numLeds);
    Serial.print("Drift Light Type: ");
    Serial.println(cfg.stripCfgs[i].driftLightType);
    Serial.print("Color: ");
    Serial.print("R: ");
    Serial.print(cfg.stripCfgs[i].color.r);
    Serial.print(", G: ");
    Serial.print(cfg.stripCfgs[i].color.g);
    Serial.print(", B: ");
    Serial.println(cfg.stripCfgs[i].color.b);
  }
}

SignalType GetSignalTypeFromString(const std::string& value) {
  std::string lowercaseValue = value;
  std::transform(lowercaseValue.begin(), lowercaseValue.end(), lowercaseValue.begin(), ::tolower);
  
  if (lowercaseValue == "crsf") {
    return CRSF;
  } else if (lowercaseValue == "sbus") {
    return SBUS;
  } else {
    return CRSF; //default value
  }
}

LightType GetLightTypeFromString(const std::string& value) {
  std::string lowercaseValue = value;
  std::transform(lowercaseValue.begin(), lowercaseValue.end(), lowercaseValue.begin(), ::tolower);

  if (lowercaseValue == "right_front_turn") {
    return RIGHT_FRONT_TURN;
  } else if (lowercaseValue == "right_head") {
    return RIGHT_HEAD;
  } else if (lowercaseValue == "left_head") {
    return LEFT_HEAD;
  } else if (lowercaseValue == "left_front_turn") {
    return LEFT_FRONT_TURN;
  } else if (lowercaseValue == "left_rear_turn") {
    return LEFT_REAR_TURN;
  } else if (lowercaseValue == "left_brake") {
    return LEFT_BRAKE;
  } else if (lowercaseValue == "right_brake") {
    return RIGHT_BRAKE;
  } else if (lowercaseValue == "right_rear_turn") {
    return RIGHT_REAR_TURN;
  } else {
    return RIGHT_HEAD; //default value
  }
}

StripType GetStripTypeFromString(const std::string& value) {
  std::string lowercaseValue = value;
  std::transform(lowercaseValue.begin(), lowercaseValue.end(), lowercaseValue.begin(), ::tolower);

  if (lowercaseValue == "drift_light") {
    return DRIFT_LIGHT;
  } else if (lowercaseValue == "exhaust") {
    return EXHAUST;
  } else if (lowercaseValue == "underglow") {
    return UNDERGLOW;
  } else {
    return DRIFT_LIGHT; //default value
  }
}

FlashGroup GetFlashGroupFromString(const std::string& value) {
  int intValue = std::stoi(value);
  
  switch (intValue) {
    case 0:
      return OFF;
    case 1:
      return GROUP1;
    case 2:
      return GROUP2;
    default:
      return OFF; //default value
  }
}

DriftLightType GetDriftLightTypeFromString(const std::string& value) {
  std::string lowercaseValue = value;
  std::transform(lowercaseValue.begin(), lowercaseValue.end(), lowercaseValue.begin(), ::tolower);

  if (lowercaseValue == "middle_out") {
    return MIDDLE_OUT;
  } else if (lowercaseValue == "back_to_front") {
    return BACK_TO_FRONT;
  } else if (lowercaseValue == "front_to_back") {
    return FRONT_TO_BACK;
  } else {
    return MIDDLE_OUT; //default value
  }
}

CRGB GetColorFromHexString(const String& hexString) {
  unsigned long rgb = strtoul(hexString.substring(1).c_str(), NULL, 16);  // Skip the first character (#)
  uint8_t r = rgb >> 16;
  uint8_t g = rgb >> 8 & 0xFF;
  uint8_t b = rgb & 0xFF;
  return CRGB(r, g, b);
}

bool GetBoolFromString(const std::string& value) {
  std::string lowercaseValue = value;
  std::transform(lowercaseValue.begin(), lowercaseValue.end(), lowercaseValue.begin(), ::tolower);
  
  if (lowercaseValue == "on") {
    return true;
  } else {
    return false; //default value
  }
}