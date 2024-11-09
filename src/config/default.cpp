#include "config.h"

// Cop Car
Config GetDefaultConfig(){
  Config cfg;
  Serial.println("loading default config");

  cfg.sysConfig.forcedShutdown = false;
  
  cfg.inputConfig.type = InputType::CRSF;
  cfg.inputConfig.steerChannel = STEER_CHANNEL;
  cfg.inputConfig.steerInverted = false;
  cfg.inputConfig.escChannel = ESC_CHANNEL;
  cfg.inputConfig.escInverted = false;
  cfg.inputConfig.enableChannel = SYSTEM_ENABLE_CHANNEL;
  cfg.inputConfig.enabledInverted = false;
  cfg.inputConfig.levelChannel = LIGHT_LEVEL_CHANNEL;
  cfg.inputConfig.levelInverted = false;

  // Passenger side headlight (input side, furthest from usb port)
  cfg.outputConfig.channelConfigs[0].pin = pinNums[0];
  cfg.outputConfig.channelConfigs[0].type = SINGLE_LED;
  cfg.outputConfig.channelConfigs[0].stripAnimation = NONE;
  cfg.outputConfig.channelConfigs[0].color = CRGB::Black;
  cfg.outputConfig.channelConfigs[0].colorOrder = GRB;
  cfg.outputConfig.channelConfigs[0].stripLedCount = 0;

  cfg.outputConfig.channelConfigs[0].roles.reverse = false;
  cfg.outputConfig.channelConfigs[0].roles.tail = false;
  cfg.outputConfig.channelConfigs[0].roles.brake = false;
  cfg.outputConfig.channelConfigs[0].roles.hazard = false;
  cfg.outputConfig.channelConfigs[0].roles.running = false;
  cfg.outputConfig.channelConfigs[0].roles.aux1 = false;
  cfg.outputConfig.channelConfigs[0].roles.aux2 = false;
  cfg.outputConfig.channelConfigs[0].roles.rightTurn = false;
  cfg.outputConfig.channelConfigs[0].roles.leftTurn = false;
  cfg.outputConfig.channelConfigs[0].roles.head = true;
  cfg.outputConfig.channelConfigs[0].roles.strobe1 = true;
  cfg.outputConfig.channelConfigs[0].roles.strobe2 = false;

  cfg.outputConfig.channelConfigs[1].pin = pinNums[1];
  cfg.outputConfig.channelConfigs[1].type = SINGLE_LED;
  cfg.outputConfig.channelConfigs[1].stripAnimation = NONE;
  cfg.outputConfig.channelConfigs[1].color = CRGB::Black;
  cfg.outputConfig.channelConfigs[1].colorOrder = GRB;
  cfg.outputConfig.channelConfigs[1].stripLedCount = 0;

  cfg.outputConfig.channelConfigs[1].roles.reverse = false;
  cfg.outputConfig.channelConfigs[1].roles.tail = false;
  cfg.outputConfig.channelConfigs[1].roles.brake = false;
  cfg.outputConfig.channelConfigs[1].roles.hazard = false;
  cfg.outputConfig.channelConfigs[1].roles.running = false;
  cfg.outputConfig.channelConfigs[1].roles.aux1 = true;
  cfg.outputConfig.channelConfigs[1].roles.aux2 = false;
  cfg.outputConfig.channelConfigs[1].roles.rightTurn = false;
  cfg.outputConfig.channelConfigs[1].roles.leftTurn = false;
  cfg.outputConfig.channelConfigs[1].roles.head = false;
  cfg.outputConfig.channelConfigs[1].roles.strobe1 = true;
  cfg.outputConfig.channelConfigs[1].roles.strobe2 = false;


  cfg.outputConfig.channelConfigs[2].pin = pinNums[2];
  cfg.outputConfig.channelConfigs[2].type = SINGLE_LED;
  cfg.outputConfig.channelConfigs[2].stripAnimation = NONE;
  cfg.outputConfig.channelConfigs[2].color = CRGB::Black;
  cfg.outputConfig.channelConfigs[2].colorOrder = GRB;
  cfg.outputConfig.channelConfigs[2].stripLedCount = 0;

  cfg.outputConfig.channelConfigs[2].roles.reverse = false;
  cfg.outputConfig.channelConfigs[2].roles.tail = false;
  cfg.outputConfig.channelConfigs[2].roles.brake = false;
  cfg.outputConfig.channelConfigs[2].roles.hazard = false;
  cfg.outputConfig.channelConfigs[2].roles.running = false;
  cfg.outputConfig.channelConfigs[2].roles.aux1 = true;
  cfg.outputConfig.channelConfigs[2].roles.aux2 = false;
  cfg.outputConfig.channelConfigs[2].roles.rightTurn = false;
  cfg.outputConfig.channelConfigs[2].roles.leftTurn = false;
  cfg.outputConfig.channelConfigs[2].roles.head = false;
  cfg.outputConfig.channelConfigs[2].roles.strobe1 = false;
  cfg.outputConfig.channelConfigs[2].roles.strobe2 = true;

  cfg.outputConfig.channelConfigs[3].pin = pinNums[3];
  cfg.outputConfig.channelConfigs[3].type = SINGLE_LED;
  cfg.outputConfig.channelConfigs[3].stripAnimation = NONE;
  cfg.outputConfig.channelConfigs[3].color = CRGB::Black;
  cfg.outputConfig.channelConfigs[3].colorOrder = GRB;
  cfg.outputConfig.channelConfigs[3].stripLedCount = 0;

  cfg.outputConfig.channelConfigs[3].roles.reverse = false;
  cfg.outputConfig.channelConfigs[3].roles.tail = false;
  cfg.outputConfig.channelConfigs[3].roles.brake = false;
  cfg.outputConfig.channelConfigs[3].roles.hazard = false;
  cfg.outputConfig.channelConfigs[3].roles.running = false;
  cfg.outputConfig.channelConfigs[3].roles.aux1 = false;
  cfg.outputConfig.channelConfigs[3].roles.aux2 = false;
  cfg.outputConfig.channelConfigs[3].roles.rightTurn = false;
  cfg.outputConfig.channelConfigs[3].roles.leftTurn = false;
  cfg.outputConfig.channelConfigs[3].roles.head = true;
  cfg.outputConfig.channelConfigs[3].roles.strobe1 = false;
  cfg.outputConfig.channelConfigs[3].roles.strobe2 = true;

  cfg.outputConfig.channelConfigs[4].pin = pinNums[4];
  cfg.outputConfig.channelConfigs[4].type = SINGLE_LED;
  cfg.outputConfig.channelConfigs[4].stripAnimation = NONE;
  cfg.outputConfig.channelConfigs[4].color = CRGB::Black;
  cfg.outputConfig.channelConfigs[4].colorOrder = GRB;
  cfg.outputConfig.channelConfigs[4].stripLedCount = 0;

  cfg.outputConfig.channelConfigs[4].roles.reverse = false;
  cfg.outputConfig.channelConfigs[4].roles.tail = false;
  cfg.outputConfig.channelConfigs[4].roles.brake = false;
  cfg.outputConfig.channelConfigs[4].roles.hazard = false;
  cfg.outputConfig.channelConfigs[4].roles.running = false;
  cfg.outputConfig.channelConfigs[4].roles.aux1 = false;
  cfg.outputConfig.channelConfigs[4].roles.aux2 = true;
  cfg.outputConfig.channelConfigs[4].roles.rightTurn = false;
  cfg.outputConfig.channelConfigs[4].roles.leftTurn = false;
  cfg.outputConfig.channelConfigs[4].roles.head = false;
  cfg.outputConfig.channelConfigs[4].roles.strobe1 = true;
  cfg.outputConfig.channelConfigs[4].roles.strobe2 = false;

  cfg.outputConfig.channelConfigs[5].pin = pinNums[5];
  cfg.outputConfig.channelConfigs[5].type = SINGLE_LED;
  cfg.outputConfig.channelConfigs[5].stripAnimation = NONE;
  cfg.outputConfig.channelConfigs[5].color = CRGB::Black;
  cfg.outputConfig.channelConfigs[5].colorOrder = GRB;
  cfg.outputConfig.channelConfigs[5].stripLedCount = 0;

  cfg.outputConfig.channelConfigs[5].roles.reverse = false;
  cfg.outputConfig.channelConfigs[5].roles.tail = true;
  cfg.outputConfig.channelConfigs[5].roles.brake = true;
  cfg.outputConfig.channelConfigs[5].roles.hazard = false;
  cfg.outputConfig.channelConfigs[5].roles.running = false;
  cfg.outputConfig.channelConfigs[5].roles.aux1 = false;
  cfg.outputConfig.channelConfigs[5].roles.aux2 = false;
  cfg.outputConfig.channelConfigs[5].roles.rightTurn = false;
  cfg.outputConfig.channelConfigs[5].roles.leftTurn = false;
  cfg.outputConfig.channelConfigs[5].roles.head = false;
  cfg.outputConfig.channelConfigs[5].roles.strobe1 = false;
  cfg.outputConfig.channelConfigs[5].roles.strobe2 = true;

  cfg.outputConfig.channelConfigs[6].pin = pinNums[6];
  cfg.outputConfig.channelConfigs[6].type = SINGLE_LED;
  cfg.outputConfig.channelConfigs[6].stripAnimation = NONE;
  cfg.outputConfig.channelConfigs[6].color = CRGB::Black;
  cfg.outputConfig.channelConfigs[6].colorOrder = GRB;
  cfg.outputConfig.channelConfigs[6].stripLedCount = 0;

  cfg.outputConfig.channelConfigs[6].roles.reverse = false;
  cfg.outputConfig.channelConfigs[6].roles.tail = true;
  cfg.outputConfig.channelConfigs[6].roles.brake = true;
  cfg.outputConfig.channelConfigs[6].roles.hazard = false;
  cfg.outputConfig.channelConfigs[6].roles.running = false;
  cfg.outputConfig.channelConfigs[6].roles.aux1 = false;
  cfg.outputConfig.channelConfigs[6].roles.aux2 = false;
  cfg.outputConfig.channelConfigs[6].roles.rightTurn = false;
  cfg.outputConfig.channelConfigs[6].roles.leftTurn = false;
  cfg.outputConfig.channelConfigs[6].roles.head = false;
  cfg.outputConfig.channelConfigs[6].roles.strobe1 = true;
  cfg.outputConfig.channelConfigs[6].roles.strobe2 = false;

  cfg.outputConfig.channelConfigs[7].pin = pinNums[7];
  cfg.outputConfig.channelConfigs[7].type = SINGLE_LED;
  cfg.outputConfig.channelConfigs[7].stripAnimation = NONE;
  cfg.outputConfig.channelConfigs[7].color = CRGB::Black;
  cfg.outputConfig.channelConfigs[7].colorOrder = GRB;
  cfg.outputConfig.channelConfigs[7].stripLedCount = 0;

  cfg.outputConfig.channelConfigs[7].roles.reverse = false;
  cfg.outputConfig.channelConfigs[7].roles.tail = false;
  cfg.outputConfig.channelConfigs[7].roles.brake = false;
  cfg.outputConfig.channelConfigs[7].roles.hazard = false;
  cfg.outputConfig.channelConfigs[7].roles.running = false;
  cfg.outputConfig.channelConfigs[7].roles.aux1 = false;
  cfg.outputConfig.channelConfigs[7].roles.aux2 = true;
  cfg.outputConfig.channelConfigs[7].roles.rightTurn = false;
  cfg.outputConfig.channelConfigs[7].roles.leftTurn = false;
  cfg.outputConfig.channelConfigs[7].roles.head = false;
  cfg.outputConfig.channelConfigs[7].roles.strobe1 = false;
  cfg.outputConfig.channelConfigs[7].roles.strobe2 = true;

  //back side furthest from usb port (exhaust)
  cfg.outputConfig.channelConfigs[8].pin = pinNums[8];
  cfg.outputConfig.channelConfigs[8].type = LED_STRIP;
  cfg.outputConfig.channelConfigs[8].stripAnimation = EXHAUST_FLAME;
  cfg.outputConfig.channelConfigs[8].color = CRGB::Blue;
  cfg.outputConfig.channelConfigs[8].colorOrder = RGB;
   cfg.outputConfig.channelConfigs[8].stripLedCount = 2; //TODO: match to one of the cars

  cfg.outputConfig.channelConfigs[8].roles.reverse = false;
  cfg.outputConfig.channelConfigs[8].roles.tail = false;
  cfg.outputConfig.channelConfigs[8].roles.brake = false;
  cfg.outputConfig.channelConfigs[8].roles.hazard = false;
  cfg.outputConfig.channelConfigs[8].roles.running = false;
  cfg.outputConfig.channelConfigs[8].roles.aux1 = false;
  cfg.outputConfig.channelConfigs[8].roles.aux2 = false;
  cfg.outputConfig.channelConfigs[8].roles.leftTurn = false;
  cfg.outputConfig.channelConfigs[8].roles.rightTurn = false;
  cfg.outputConfig.channelConfigs[8].roles.head = false;
  cfg.outputConfig.channelConfigs[8].roles.strobe1 = false;
  cfg.outputConfig.channelConfigs[8].roles.strobe2 = false;

  cfg.outputConfig.channelConfigs[9].pin = pinNums[9];
  cfg.outputConfig.channelConfigs[9].type = LED_STRIP;
  cfg.outputConfig.channelConfigs[9].stripAnimation = POLICE_LIGHTS_WRAP;
  cfg.outputConfig.channelConfigs[9].color = CRGB::Blue;
  cfg.outputConfig.channelConfigs[9].colorOrder = RGB;
  cfg.outputConfig.channelConfigs[9].stripLedCount = 2;

  cfg.outputConfig.channelConfigs[9].roles.reverse = false;
  cfg.outputConfig.channelConfigs[9].roles.tail = false;
  cfg.outputConfig.channelConfigs[9].roles.brake = false;
  cfg.outputConfig.channelConfigs[9].roles.hazard = false;
  cfg.outputConfig.channelConfigs[9].roles.running = false;
  cfg.outputConfig.channelConfigs[9].roles.aux1 = false;
  cfg.outputConfig.channelConfigs[9].roles.aux2 = false;
  cfg.outputConfig.channelConfigs[9].roles.leftTurn = false;
  cfg.outputConfig.channelConfigs[9].roles.rightTurn = false;
  cfg.outputConfig.channelConfigs[9].roles.head = false;
  cfg.outputConfig.channelConfigs[9].roles.strobe1 = false;
  cfg.outputConfig.channelConfigs[9].roles.strobe2 = false;

  //Input side closest to usb port (top light)
  cfg.outputConfig.channelConfigs[10].pin = pinNums[10];
  cfg.outputConfig.channelConfigs[10].type = LED_STRIP;
  cfg.outputConfig.channelConfigs[10].stripAnimation = POLICE_LIGHTS_WRAP;
  cfg.outputConfig.channelConfigs[10].color = CRGB::Blue; //TODO: match to one of the cars
  cfg.outputConfig.channelConfigs[10].colorOrder = GRB;
  cfg.outputConfig.channelConfigs[10].stripLedCount = 32;

  cfg.outputConfig.channelConfigs[10].roles.reverse = false;
  cfg.outputConfig.channelConfigs[10].roles.tail = false;
  cfg.outputConfig.channelConfigs[10].roles.brake = false;
  cfg.outputConfig.channelConfigs[10].roles.hazard = false;
  cfg.outputConfig.channelConfigs[10].roles.running = false;
  cfg.outputConfig.channelConfigs[10].roles.aux1 = false;
  cfg.outputConfig.channelConfigs[10].roles.aux2 = false;
  cfg.outputConfig.channelConfigs[10].roles.leftTurn = false;
  cfg.outputConfig.channelConfigs[10].roles.rightTurn = false;
  cfg.outputConfig.channelConfigs[10].roles.head = false;
  cfg.outputConfig.channelConfigs[10].roles.strobe1 = false;
  cfg.outputConfig.channelConfigs[10].roles.strobe2 = false;

  cfg.outputConfig.channelConfigs[11].pin = pinNums[11];
  cfg.outputConfig.channelConfigs[11].type = LED_STRIP;
  cfg.outputConfig.channelConfigs[11].stripAnimation = POLICE_LIGHTS_WRAP;
  cfg.outputConfig.channelConfigs[11].color = CRGB::Blue; //TODO: match to one of the cars
  cfg.outputConfig.channelConfigs[11].colorOrder = GRB;
  cfg.outputConfig.channelConfigs[11].stripLedCount = 2;

  cfg.outputConfig.channelConfigs[11].roles.reverse = false;
  cfg.outputConfig.channelConfigs[11].roles.tail = false;
  cfg.outputConfig.channelConfigs[11].roles.brake = false;
  cfg.outputConfig.channelConfigs[11].roles.hazard = false;
  cfg.outputConfig.channelConfigs[11].roles.running = false;
  cfg.outputConfig.channelConfigs[11].roles.aux1 = false;
  cfg.outputConfig.channelConfigs[11].roles.aux2 = false;
  cfg.outputConfig.channelConfigs[11].roles.leftTurn = false;
  cfg.outputConfig.channelConfigs[11].roles.rightTurn = false;
  cfg.outputConfig.channelConfigs[11].roles.head = false;
  cfg.outputConfig.channelConfigs[11].roles.strobe1 = false;
  cfg.outputConfig.channelConfigs[11].roles.strobe2 = false;

  cfg.levelConfigs[0].roles.hazard = true;
  cfg.levelConfigs[0].roles.leftTurn = true;
  cfg.levelConfigs[0].roles.rightTurn = true;
  cfg.levelConfigs[0].roles.brake = true;
  cfg.levelConfigs[0].animations.exhaustFlame = true;

  cfg.levelConfigs[0].roles.head = false;
  cfg.levelConfigs[0].roles.tail = false;
  cfg.levelConfigs[0].roles.running = false;
  cfg.levelConfigs[0].roles.aux1 = false;
  cfg.levelConfigs[0].roles.aux2 = false;
  cfg.levelConfigs[0].roles.reverse = false;
  cfg.levelConfigs[0].roles.strobe1 = false;
  cfg.levelConfigs[0].roles.strobe2 = false;
  cfg.levelConfigs[0].animations.underglow = false;
  cfg.levelConfigs[0].animations.throttleBrakeLight = false;
  cfg.levelConfigs[0].animations.policeLights = false;
  cfg.levelConfigs[0].animations.cautionLights = false;

  cfg.levelConfigs[1].roles.hazard = true;
  cfg.levelConfigs[1].roles.leftTurn = true;
  cfg.levelConfigs[1].roles.rightTurn = true;
  cfg.levelConfigs[1].roles.brake = true;
  cfg.levelConfigs[1].roles.head = true;
  cfg.levelConfigs[1].roles.tail = true;
  cfg.levelConfigs[1].roles.running = true;
  cfg.levelConfigs[1].animations.exhaustFlame = true;

  cfg.levelConfigs[1].roles.aux1 = false;
  cfg.levelConfigs[1].roles.aux2 = true;
  cfg.levelConfigs[1].roles.reverse = false;
  cfg.levelConfigs[1].roles.strobe1 = false;
  cfg.levelConfigs[1].roles.strobe2 = false;
  cfg.levelConfigs[1].animations.underglow = false;
  cfg.levelConfigs[1].animations.throttleBrakeLight = false;
  cfg.levelConfigs[1].animations.policeLights = false;
  cfg.levelConfigs[1].animations.cautionLights = false;

  cfg.levelConfigs[2].roles.hazard = true;
  cfg.levelConfigs[2].roles.leftTurn = true;
  cfg.levelConfigs[2].roles.rightTurn = true;
  cfg.levelConfigs[2].roles.brake = true;
  cfg.levelConfigs[2].roles.head = true;
  cfg.levelConfigs[2].roles.tail = true;
  cfg.levelConfigs[2].roles.running = true;
  cfg.levelConfigs[2].roles.aux1 = true;
  cfg.levelConfigs[2].roles.aux2 = true;
  cfg.levelConfigs[2].roles.reverse = false;
  cfg.levelConfigs[2].roles.strobe1 = true;
  cfg.levelConfigs[2].roles.strobe2 = true;
  cfg.levelConfigs[2].animations.underglow = true;
  cfg.levelConfigs[2].animations.throttleBrakeLight = true;
  cfg.levelConfigs[2].animations.exhaustFlame = true;
  cfg.levelConfigs[2].animations.policeLights = true;
  cfg.levelConfigs[2].animations.cautionLights = true;
  return cfg;
}

// Default
// Config GetDefaultConfig(){
//   Config cfg;
//   Serial.println("loading default config");

//   cfg.sysConfig.forcedShutdown = false;
  
//   cfg.inputConfig.type = InputType::CRSF;
//   cfg.inputConfig.steerChannel = STEER_CHANNEL;
//   cfg.inputConfig.steerInverted = false;
//   cfg.inputConfig.escChannel = ESC_CHANNEL;
//   cfg.inputConfig.escInverted = false;
//   cfg.inputConfig.enableChannel = SYSTEM_ENABLE_CHANNEL;
//   cfg.inputConfig.enabledInverted = false;
//   cfg.inputConfig.levelChannel = LIGHT_LEVEL_CHANNEL;
//   cfg.inputConfig.levelInverted = false;

//   cfg.outputConfig.channelConfigs[0].pin = pinNums[0];
//   cfg.outputConfig.channelConfigs[0].type = SINGLE_LED;
//   cfg.outputConfig.channelConfigs[0].stripAnimation = NONE;
//   cfg.outputConfig.channelConfigs[0].color = CRGB::Black;
//   cfg.outputConfig.channelConfigs[0].colorOrder = GRB;
//   cfg.outputConfig.channelConfigs[0].stripLedCount = 0;
//   cfg.outputConfig.channelConfigs[0].roles.rightTurn = true;

//   cfg.outputConfig.channelConfigs[0].roles.reverse = false;
//   cfg.outputConfig.channelConfigs[0].roles.tail = false;
//   cfg.outputConfig.channelConfigs[0].roles.head = false;
//   cfg.outputConfig.channelConfigs[0].roles.brake = false;
//   cfg.outputConfig.channelConfigs[0].roles.hazard = false;
//   cfg.outputConfig.channelConfigs[0].roles.running = false;
//   cfg.outputConfig.channelConfigs[0].roles.aux1 = false;
//   cfg.outputConfig.channelConfigs[0].roles.aux2 = false;
//   cfg.outputConfig.channelConfigs[0].roles.leftTurn = false;
//   cfg.outputConfig.channelConfigs[0].roles.strobe1 = false;
//   cfg.outputConfig.channelConfigs[0].roles.strobe2 = false;

//   cfg.outputConfig.channelConfigs[1].pin = pinNums[1];
//   cfg.outputConfig.channelConfigs[1].type = SINGLE_LED;
//   cfg.outputConfig.channelConfigs[1].stripAnimation = NONE;
//   cfg.outputConfig.channelConfigs[1].color = CRGB::Black;
//   cfg.outputConfig.channelConfigs[1].colorOrder = GRB;
//   cfg.outputConfig.channelConfigs[1].stripLedCount = 0;
//   cfg.outputConfig.channelConfigs[1].roles.head = true;
//   cfg.outputConfig.channelConfigs[1].roles.strobe1 = true;

//   cfg.outputConfig.channelConfigs[1].roles.reverse = false;
//   cfg.outputConfig.channelConfigs[1].roles.tail = false;
//   cfg.outputConfig.channelConfigs[1].roles.brake = false;
//   cfg.outputConfig.channelConfigs[1].roles.hazard = false;
//   cfg.outputConfig.channelConfigs[1].roles.running = false;
//   cfg.outputConfig.channelConfigs[1].roles.aux1 = false;
//   cfg.outputConfig.channelConfigs[1].roles.aux2 = false;
//   cfg.outputConfig.channelConfigs[1].roles.leftTurn = false;
//   cfg.outputConfig.channelConfigs[1].roles.rightTurn = false;
//   cfg.outputConfig.channelConfigs[1].roles.strobe2 = false;


//   cfg.outputConfig.channelConfigs[2].pin = pinNums[2];
//   cfg.outputConfig.channelConfigs[2].type = SINGLE_LED;
//   cfg.outputConfig.channelConfigs[2].stripAnimation = NONE;
//   cfg.outputConfig.channelConfigs[2].color = CRGB::Black;
//   cfg.outputConfig.channelConfigs[2].colorOrder = GRB;
//   cfg.outputConfig.channelConfigs[2].stripLedCount = 0;
//   cfg.outputConfig.channelConfigs[2].roles.head = true;
//   cfg.outputConfig.channelConfigs[2].roles.strobe2 = true;

//   cfg.outputConfig.channelConfigs[2].roles.reverse = false;
//   cfg.outputConfig.channelConfigs[2].roles.tail = false;
//   cfg.outputConfig.channelConfigs[2].roles.brake = false;
//   cfg.outputConfig.channelConfigs[2].roles.hazard = false;
//   cfg.outputConfig.channelConfigs[2].roles.running = false;
//   cfg.outputConfig.channelConfigs[2].roles.aux1 = false;
//   cfg.outputConfig.channelConfigs[2].roles.aux2 = false;
//   cfg.outputConfig.channelConfigs[2].roles.leftTurn = false;
//   cfg.outputConfig.channelConfigs[2].roles.rightTurn = false;
//   cfg.outputConfig.channelConfigs[2].roles.strobe1 = false;

//   cfg.outputConfig.channelConfigs[3].pin = pinNums[3];
//   cfg.outputConfig.channelConfigs[3].type = SINGLE_LED;
//   cfg.outputConfig.channelConfigs[3].stripAnimation = NONE;
//   cfg.outputConfig.channelConfigs[3].color = CRGB::Black;
//   cfg.outputConfig.channelConfigs[3].colorOrder = GRB;
//   cfg.outputConfig.channelConfigs[3].stripLedCount = 0;
//   cfg.outputConfig.channelConfigs[3].roles.leftTurn = true;

//   cfg.outputConfig.channelConfigs[3].roles.reverse = false;
//   cfg.outputConfig.channelConfigs[3].roles.tail = false;
//   cfg.outputConfig.channelConfigs[3].roles.brake = false;
//   cfg.outputConfig.channelConfigs[3].roles.hazard = false;
//   cfg.outputConfig.channelConfigs[3].roles.running = false;
//   cfg.outputConfig.channelConfigs[3].roles.aux1 = false;
//   cfg.outputConfig.channelConfigs[3].roles.aux2 = false;
//   cfg.outputConfig.channelConfigs[3].roles.rightTurn = false;
//   cfg.outputConfig.channelConfigs[3].roles.head = false;
//   cfg.outputConfig.channelConfigs[3].roles.strobe1 = false;
//   cfg.outputConfig.channelConfigs[3].roles.strobe2 = false;

//   cfg.outputConfig.channelConfigs[4].pin = pinNums[4];
//   cfg.outputConfig.channelConfigs[4].type = SINGLE_LED;
//   cfg.outputConfig.channelConfigs[4].stripAnimation = NONE;
//   cfg.outputConfig.channelConfigs[4].color = CRGB::Black;
//   cfg.outputConfig.channelConfigs[4].colorOrder = GRB;
//   cfg.outputConfig.channelConfigs[4].stripLedCount = 0;
//   cfg.outputConfig.channelConfigs[4].roles.brake = true;
//   cfg.outputConfig.channelConfigs[4].roles.leftTurn = true;
//   cfg.outputConfig.channelConfigs[4].roles.tail = true;

//   cfg.outputConfig.channelConfigs[4].roles.reverse = false;
//   cfg.outputConfig.channelConfigs[4].roles.hazard = false;
//   cfg.outputConfig.channelConfigs[4].roles.running = false;
//   cfg.outputConfig.channelConfigs[4].roles.aux1 = false;
//   cfg.outputConfig.channelConfigs[4].roles.aux2 = false;
//   cfg.outputConfig.channelConfigs[4].roles.rightTurn = false;
//   cfg.outputConfig.channelConfigs[4].roles.head = false;
//   cfg.outputConfig.channelConfigs[4].roles.strobe1 = false;
//   cfg.outputConfig.channelConfigs[4].roles.strobe2 = false;

//   cfg.outputConfig.channelConfigs[5].pin = pinNums[5];
//   cfg.outputConfig.channelConfigs[5].type = SINGLE_LED;
//   cfg.outputConfig.channelConfigs[5].stripAnimation = NONE;
//   cfg.outputConfig.channelConfigs[5].color = CRGB::Black;
//   cfg.outputConfig.channelConfigs[5].colorOrder = GRB;
//   cfg.outputConfig.channelConfigs[5].stripLedCount = 0;
//   cfg.outputConfig.channelConfigs[5].roles.brake = true;
//   cfg.outputConfig.channelConfigs[5].roles.tail = true;

//   cfg.outputConfig.channelConfigs[5].roles.reverse = false;
//   cfg.outputConfig.channelConfigs[5].roles.hazard = false;
//   cfg.outputConfig.channelConfigs[5].roles.running = false;
//   cfg.outputConfig.channelConfigs[5].roles.aux1 = false;
//   cfg.outputConfig.channelConfigs[5].roles.aux2 = false;
//   cfg.outputConfig.channelConfigs[5].roles.leftTurn = false;
//   cfg.outputConfig.channelConfigs[5].roles.rightTurn = false;
//   cfg.outputConfig.channelConfigs[5].roles.head = false;
//   cfg.outputConfig.channelConfigs[5].roles.strobe1 = false;
//   cfg.outputConfig.channelConfigs[5].roles.strobe2 = false;

//   cfg.outputConfig.channelConfigs[6].pin = pinNums[6];
//   cfg.outputConfig.channelConfigs[6].type = SINGLE_LED;
//   cfg.outputConfig.channelConfigs[6].stripAnimation = NONE;
//   cfg.outputConfig.channelConfigs[6].color = CRGB::Black;
//   cfg.outputConfig.channelConfigs[6].colorOrder = GRB;
//   cfg.outputConfig.channelConfigs[6].stripLedCount = 0;
//   cfg.outputConfig.channelConfigs[6].roles.brake = true;
//   cfg.outputConfig.channelConfigs[6].roles.tail = true;

//   cfg.outputConfig.channelConfigs[6].roles.reverse = false;
//   cfg.outputConfig.channelConfigs[6].roles.hazard = false;
//   cfg.outputConfig.channelConfigs[6].roles.running = false;
//   cfg.outputConfig.channelConfigs[6].roles.aux1 = false;
//   cfg.outputConfig.channelConfigs[6].roles.aux2 = false;
//   cfg.outputConfig.channelConfigs[6].roles.leftTurn = false;
//   cfg.outputConfig.channelConfigs[6].roles.rightTurn = false;
//   cfg.outputConfig.channelConfigs[6].roles.head = false;
//   cfg.outputConfig.channelConfigs[6].roles.strobe1 = false;
//   cfg.outputConfig.channelConfigs[6].roles.strobe2 = false;

//   cfg.outputConfig.channelConfigs[7].pin = pinNums[7];
//   cfg.outputConfig.channelConfigs[7].type = SINGLE_LED;
//   cfg.outputConfig.channelConfigs[7].stripAnimation = NONE;
//   cfg.outputConfig.channelConfigs[7].color = CRGB::Black;
//   cfg.outputConfig.channelConfigs[7].colorOrder = GRB;
//   cfg.outputConfig.channelConfigs[7].stripLedCount = 0;
//   cfg.outputConfig.channelConfigs[7].roles.brake = true;
//   cfg.outputConfig.channelConfigs[7].roles.rightTurn = true;
//   cfg.outputConfig.channelConfigs[7].roles.tail = true;

//   cfg.outputConfig.channelConfigs[7].roles.reverse = false;
//   cfg.outputConfig.channelConfigs[7].roles.hazard = false;
//   cfg.outputConfig.channelConfigs[7].roles.running = false;
//   cfg.outputConfig.channelConfigs[7].roles.aux1 = false;
//   cfg.outputConfig.channelConfigs[7].roles.aux2 = false;
//   cfg.outputConfig.channelConfigs[7].roles.leftTurn = false;
//   cfg.outputConfig.channelConfigs[7].roles.head = false;
//   cfg.outputConfig.channelConfigs[7].roles.strobe1 = false;
//   cfg.outputConfig.channelConfigs[7].roles.strobe2 = false;

//   cfg.outputConfig.channelConfigs[8].pin = pinNums[8];
//   cfg.outputConfig.channelConfigs[8].type = LED_STRIP;
//   cfg.outputConfig.channelConfigs[8].stripAnimation = THROTTLE_BRAKE_LIGHT_MIDDLE;
//   cfg.outputConfig.channelConfigs[8].stripLedCount = 12; //TODO: match to one of the cars
//   cfg.outputConfig.channelConfigs[8].color = CRGB(0,0,255);
//   cfg.outputConfig.channelConfigs[8].colorOrder = GRB;

//   cfg.outputConfig.channelConfigs[8].roles.reverse = false;
//   cfg.outputConfig.channelConfigs[8].roles.tail = false;
//   cfg.outputConfig.channelConfigs[8].roles.brake = false;
//   cfg.outputConfig.channelConfigs[8].roles.hazard = false;
//   cfg.outputConfig.channelConfigs[8].roles.running = false;
//   cfg.outputConfig.channelConfigs[8].roles.aux1 = false;
//   cfg.outputConfig.channelConfigs[8].roles.aux2 = false;
//   cfg.outputConfig.channelConfigs[8].roles.leftTurn = false;
//   cfg.outputConfig.channelConfigs[8].roles.rightTurn = false;
//   cfg.outputConfig.channelConfigs[8].roles.head = false;
//   cfg.outputConfig.channelConfigs[8].roles.strobe1 = false;
//   cfg.outputConfig.channelConfigs[8].roles.strobe2 = false;

//   cfg.outputConfig.channelConfigs[9].pin = pinNums[9];
//   cfg.outputConfig.channelConfigs[9].type = LED_STRIP;
//   cfg.outputConfig.channelConfigs[9].stripAnimation = EXHAUST_FLAME;
//   cfg.outputConfig.channelConfigs[9].color = CRGB(255, 0, 0);
//   cfg.outputConfig.channelConfigs[9].colorOrder = RGB;
//   cfg.outputConfig.channelConfigs[9].stripLedCount = 50;

//   cfg.outputConfig.channelConfigs[9].roles.reverse = false;
//   cfg.outputConfig.channelConfigs[9].roles.tail = false;
//   cfg.outputConfig.channelConfigs[9].roles.brake = false;
//   cfg.outputConfig.channelConfigs[9].roles.hazard = false;
//   cfg.outputConfig.channelConfigs[9].roles.running = false;
//   cfg.outputConfig.channelConfigs[9].roles.aux1 = false;
//   cfg.outputConfig.channelConfigs[9].roles.aux2 = false;
//   cfg.outputConfig.channelConfigs[9].roles.leftTurn = false;
//   cfg.outputConfig.channelConfigs[9].roles.rightTurn = false;
//   cfg.outputConfig.channelConfigs[9].roles.head = false;
//   cfg.outputConfig.channelConfigs[9].roles.strobe1 = false;
//   cfg.outputConfig.channelConfigs[9].roles.strobe2 = false;

//   cfg.outputConfig.channelConfigs[10].pin = pinNums[10];
//   cfg.outputConfig.channelConfigs[10].type = LED_STRIP;
//   cfg.outputConfig.channelConfigs[10].stripAnimation = EXHAUST_FLAME;
//   cfg.outputConfig.channelConfigs[10].color = CRGB::Blue; //TODO: match to one of the cars
//   cfg.outputConfig.channelConfigs[10].colorOrder = GRB;
//   cfg.outputConfig.channelConfigs[10].stripLedCount = 50;

//   cfg.outputConfig.channelConfigs[10].roles.reverse = false;
//   cfg.outputConfig.channelConfigs[10].roles.tail = false;
//   cfg.outputConfig.channelConfigs[10].roles.brake = false;
//   cfg.outputConfig.channelConfigs[10].roles.hazard = false;
//   cfg.outputConfig.channelConfigs[10].roles.running = false;
//   cfg.outputConfig.channelConfigs[10].roles.aux1 = false;
//   cfg.outputConfig.channelConfigs[10].roles.aux2 = false;
//   cfg.outputConfig.channelConfigs[10].roles.leftTurn = false;
//   cfg.outputConfig.channelConfigs[10].roles.rightTurn = false;
//   cfg.outputConfig.channelConfigs[10].roles.head = false;
//   cfg.outputConfig.channelConfigs[10].roles.strobe1 = false;
//   cfg.outputConfig.channelConfigs[10].roles.strobe2 = false;

//   cfg.outputConfig.channelConfigs[11].pin = pinNums[11];
//   cfg.outputConfig.channelConfigs[11].type = LED_STRIP;
//   cfg.outputConfig.channelConfigs[11].stripAnimation = POLICE_LIGHTS_WRAP;
//   cfg.outputConfig.channelConfigs[11].color = CRGB(255,0,255); //TODO: match to one of the cars
//   cfg.outputConfig.channelConfigs[11].colorOrder = GRB;
//   cfg.outputConfig.channelConfigs[11].stripLedCount = 70;

//   cfg.outputConfig.channelConfigs[11].roles.reverse = false;
//   cfg.outputConfig.channelConfigs[11].roles.tail = false;
//   cfg.outputConfig.channelConfigs[11].roles.brake = false;
//   cfg.outputConfig.channelConfigs[11].roles.hazard = false;
//   cfg.outputConfig.channelConfigs[11].roles.running = false;
//   cfg.outputConfig.channelConfigs[11].roles.aux1 = false;
//   cfg.outputConfig.channelConfigs[11].roles.aux2 = false;
//   cfg.outputConfig.channelConfigs[11].roles.leftTurn = false;
//   cfg.outputConfig.channelConfigs[11].roles.rightTurn = false;
//   cfg.outputConfig.channelConfigs[11].roles.head = false;
//   cfg.outputConfig.channelConfigs[11].roles.strobe1 = false;
//   cfg.outputConfig.channelConfigs[11].roles.strobe2 = false;

//   cfg.levelConfigs[0].roles.hazard = true;
//   cfg.levelConfigs[0].roles.leftTurn = true;
//   cfg.levelConfigs[0].roles.rightTurn = true;
//   cfg.levelConfigs[0].roles.brake = true;
//   cfg.levelConfigs[0].animations.exhaustFlame = true;

//   cfg.levelConfigs[0].roles.head = false;
//   cfg.levelConfigs[0].roles.tail = false;
//   cfg.levelConfigs[0].roles.running = false;
//   cfg.levelConfigs[0].roles.aux1 = false;
//   cfg.levelConfigs[0].roles.aux2 = false;
//   cfg.levelConfigs[0].roles.reverse = false;
//   cfg.levelConfigs[0].roles.strobe1 = false;
//   cfg.levelConfigs[0].roles.strobe2 = false;
//   cfg.levelConfigs[0].animations.underglow = false;
//   cfg.levelConfigs[0].animations.throttleBrakeLight = false;
//   cfg.levelConfigs[0].animations.policeLights = false;
//   cfg.levelConfigs[0].animations.cautionLights = false;

//   cfg.levelConfigs[1].roles.hazard = true;
//   cfg.levelConfigs[1].roles.leftTurn = true;
//   cfg.levelConfigs[1].roles.rightTurn = true;
//   cfg.levelConfigs[1].roles.brake = true;
//   cfg.levelConfigs[1].roles.head = true;
//   cfg.levelConfigs[1].roles.tail = true;
//   cfg.levelConfigs[1].roles.running = true;
//   cfg.levelConfigs[1].animations.exhaustFlame = true;

//   cfg.levelConfigs[1].roles.aux1 = false;
//   cfg.levelConfigs[1].roles.aux2 = false;
//   cfg.levelConfigs[1].roles.reverse = false;
//   cfg.levelConfigs[1].roles.strobe1 = false;
//   cfg.levelConfigs[1].roles.strobe2 = false;
//   cfg.levelConfigs[1].animations.underglow = false;
//   cfg.levelConfigs[1].animations.throttleBrakeLight = false;
//   cfg.levelConfigs[1].animations.policeLights = false;
//   cfg.levelConfigs[1].animations.cautionLights = false;

//   cfg.levelConfigs[2].roles.hazard = true;
//   cfg.levelConfigs[2].roles.leftTurn = true;
//   cfg.levelConfigs[2].roles.rightTurn = true;
//   cfg.levelConfigs[2].roles.brake = true;
//   cfg.levelConfigs[2].roles.head = true;
//   cfg.levelConfigs[2].roles.tail = true;
//   cfg.levelConfigs[2].roles.running = true;
//   cfg.levelConfigs[2].roles.aux1 = true;
//   cfg.levelConfigs[2].roles.aux2 = true;
//   cfg.levelConfigs[2].roles.reverse = false;
//   cfg.levelConfigs[2].roles.strobe1 = true;
//   cfg.levelConfigs[2].roles.strobe2 = true;
//   cfg.levelConfigs[2].animations.underglow = true;
//   cfg.levelConfigs[2].animations.throttleBrakeLight = true;
//   cfg.levelConfigs[2].animations.exhaustFlame = true;
//   cfg.levelConfigs[2].animations.policeLights = true;
//   cfg.levelConfigs[2].animations.cautionLights = true;
//   return cfg;
// }
