#include "storage.h"

Config CreateOrLoadCfg(Preferences* preferences){

  int cfgFound = preferences->getBool("cfgFound", false);
  if(!cfgFound){
    Serial.println("first boot, loading default config");
    Config defaultConfig = GetDefaultConfig();
    SaveConfig(preferences,defaultConfig);
    return defaultConfig;
  }else{
    return LoadConfig(preferences);
  }
}

Config LoadConfig(Preferences* preferences){
  int cfgFound = preferences->getBool("cfgFound", false);
  if(!cfgFound){
    return GetDefaultConfig();
  }

  Config config;
  Serial.println("loading saved config");

  config.signalType = SignalType(preferences->getInt("signal", SIGNAL_TYPE));
  config.triggerChannel = preferences->getInt("trigger", SYSTEM_ENABLE_CHANNEL);
  config.levelChannel = preferences->getInt("level", LIGHT_LEVEL_CHANNEL);

  config.invertSteering = preferences->getBool("i_steer", INVERT_STEER);
  config.invertESC = preferences->getBool("i_esc", INVERT_ESC);
  config.enableTurnSignals = preferences->getBool("signals", ENABLE_TURNSIGNALS);
  config.turnSignalsAlsoHead = preferences->getBool("s_Head", TURN_SIGNAL_ALSO_HEAD);
  config.turnSignalsAlsoBrake = preferences->getBool("s_Brake", TURN_SIGNAL_ALSO_BRAKE);
  config.enableHazards = preferences->getBool("hazards", ENABLE_HAZARDS);
  config.enableFlash = preferences->getBool("flash", ENABLE_FLASH);

  for(int i =0; i < NUM_LEVELS; i++){
    config.levelCfgs[i].hazards = preferences->getBool("hazards_"+i, true);
    config.levelCfgs[i].turnSignals = preferences->getBool("turn_"+i, true);
    config.levelCfgs[i].brakes = preferences->getBool("brakes_"+i, true);
    config.levelCfgs[i].headLights = preferences->getBool("head_"+i, false);
    config.levelCfgs[i].flashLights = preferences->getBool("flash_"+i, false);
    config.levelCfgs[i].driftLights = preferences->getBool("drift_"+i, false);
    config.levelCfgs[i].underglow = preferences->getBool("glow_"+i, false);
    config.levelCfgs[i].auxLights = preferences->getBool("aux_"+i, false);
    config.levelCfgs[i].exhaust = preferences->getBool("exhaust_"+i, true);
  }

  for(int i = 0; i < NUM_LIGHT_OUTPUTS; i++){
    config.outCfgs[i].lightType = LightType(preferences->getInt("out_t"+i, RIGHT_FRONT_TURN));
    int32_t flashGroupInt = preferences->getInt((String("o_f")+String(i)).c_str(), OFF);
    config.outCfgs[i].flashGroup = FlashGroup(flashGroupInt);
  }

  for(int i=0; i < NUM_STRIPS; i++){
    config.stripCfgs[i].stripType = StripType(preferences->getInt("type1_"+i, DRIFT_LIGHT));
    config.stripCfgs[i].numLeds = preferences->getInt("numLeds_"+i, NUM_STRIP_LEDS);
    config.stripCfgs[i].driftLightType = DriftLightType(preferences->getInt("dType_"+i, MIDDLE_OUT));
    preferences->getBytes("color_"+i, config.stripCfgs[i].color.raw, 3);
  }

  //PrintConfig(config);
  return config;
}

void SaveConfig(Preferences* preferences, Config config){
  Serial.println("saving config");

  preferences->putInt("signal", config.signalType);
  preferences->putInt("trigger", config.triggerChannel);
  preferences->putInt("level", config.levelChannel);

  preferences->putBool("i_steer", config.invertSteering);
  preferences->putBool("i_esc", config.invertESC);
  preferences->putBool("signals", config.enableTurnSignals);
  preferences->putBool("s_Head", config.turnSignalsAlsoHead);
  preferences->putBool("s_Brake", config.turnSignalsAlsoBrake);
  preferences->putBool("hazards", config.enableHazards);
  preferences->putBool("flash", config.enableFlash);

  for(int i = 0; i < NUM_LEVELS; i++){
    preferences->putBool("hazards_"+i, config.levelCfgs[i].hazards);
    preferences->putBool("turn_"+i, config.levelCfgs[i].turnSignals);
    preferences->putBool("brakes_"+i, config.levelCfgs[i].brakes);
    preferences->putBool("head_"+i, config.levelCfgs[i].headLights);
    preferences->putBool("flash_"+i, config.levelCfgs[i].flashLights);
    preferences->putBool("drift_"+i, config.levelCfgs[i].driftLights);
    preferences->putBool("glow_"+i, config.levelCfgs[i].underglow);
    preferences->putBool("aux_"+i, config.levelCfgs[i].auxLights);
    preferences->putBool("exhaust_"+i, config.levelCfgs[i].exhaust);
  }

  for(int i = 0; i < NUM_LIGHT_OUTPUTS; i++){
    preferences->putInt("out_t"+i, int32_t(config.outCfgs[i].lightType));
    preferences->putInt((String("o_f")+String(i)).c_str(), int32_t(config.outCfgs[i].flashGroup));
  }

  for(int i=0; i < NUM_STRIPS; i++){
    preferences->putInt("type1_"+i, int(config.stripCfgs[i].stripType));
    preferences->putInt("numLeds_"+i, config.stripCfgs[i].numLeds);
    preferences->putInt("dType_"+i, config.stripCfgs[i].driftLightType);
    preferences->putBytes("color_"+i, config.stripCfgs[i].color.raw, 3);
  }

  preferences->putBool("cfgFound", true); //signal to load config instead of defaults

  //PrintConfig(config);
}