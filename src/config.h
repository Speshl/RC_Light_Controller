#ifndef CONFIG_H
#define CONFIG_H
#include "Arduino.h"
#include <FastLED.h>

//led strip configs
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define VOLTS 5
#define MAX_AMPS 500 //value in milliamps
#define BRIGHTNESS 60

#define SIGNAL_TYPE CRSF

//CRSF config
//990-1500-2011
#define ESC_DEADZONE 20// Small deadzone so lights turn off
#define TURN_FLEX_RANGE 400// More distance from center before turn signals enabled
#define FLEX_RANGE 100 //Distance from midpoint before update acknowleded
#define CRSF_LOW 990
#define CRSF_MID 1500
#define CRSF_HIGH 2011

//channels configs
#define STEER_CHANNEL 1
#define ESC_CHANNEL 2
#define SYSTEM_ENABLE_CHANNEL 10
#define LIGHT_LEVEL_CHANNEL 11

#define INVERT_ESC false
#define INVERT_STEER true

//pinout configs
#define NUM_LIGHT_OUTPUTS 8
#define NUM_FLASH_GROUPS 3 //2 + off = 3

//SLC v1.1 stacked
#define LIGHT_OUT_1 32
#define LIGHT_OUT_2 33
#define LIGHT_OUT_3 25
#define LIGHT_OUT_4 26

#define LIGHT_OUT_5 27
#define LIGHT_OUT_6 14
#define LIGHT_OUT_7 12
#define LIGHT_OUT_8 13 

#define NUM_STRIPS 3
#define STRIP_OUT_1 4
#define STRIP_OUT_2 5
#define STRIP_OUT_3 18
// #define STRIP_OUT_4 4

#define NUM_STRIP_LEDS 50

//control configs
#define NUM_LEVELS 3
#define ENABLE_DRIFT_LIGHT true
#define ENABLE_UNDERGLOW true

#define ENABLE_TURNSIGNALS true
#define TURN_SIGNAL_ALSO_BRAKE true
#define TURN_SIGNAL_ALSO_HEAD true

#define ENABLE_HAZARDS true
#define ENABLE_FLASH false
#define HAZARD_TIME 500
#define FLASH_TIME 500
#define IDLE_TIME 30000

#define ENABLE_EXHAUST true
#define NUM_EXHAUST_HISTORY 10
#define MAX_EXHAUST_INTENSITY 1000

#define POP_EXHAUST_LEVEL (((CRSF_HIGH - CRSF_MID) / 100) * 90) + CRSF_MID
#define MAX_START_POP_EXHAUST_INTENSITY 1000
#define MIN_START_POP_EXHAUST_INTENSITY 950
#define MAX_CHANGE_POP_EXHAUST_INTENSITY 100 //value is halfed on increase, full value used for decreases
#define MIN_CHANGE_POP_EXHAUST_INTENSITY 50 //value is halfed on increase, full value used for decreases
#define CHANCE_POP_EXHAUST_INTENSITY_INCREASE 25 //percent chance intensity will increase instead of decrease

#define BRIGHT_EXHAUST_LEVEL (((CRSF_HIGH - CRSF_MID) / 100) * 60) + CRSF_MID
#define MAX_START_BRIGHT_EXHAUST_INTENSITY 1000
#define MIN_START_BRIGHT_EXHAUST_INTENSITY 800
#define MAX_CHANGE_BRIGHT_EXHAUST_INTENSITY 20 //value is halfed on increase, full value used for decreases
#define MIN_CHANGE_BRIGHT_EXHAUST_INTENSITY 5 //value is halfed on increase, full value used for decreases
#define CHANCE_BRIGHT_EXHAUST_INTENSITY_INCREASE 50 //percent chance intensity will increase instead of decrease

#define DIM_EXHAUST_LEVEL (((CRSF_HIGH - CRSF_MID) / 100) * 40) + CRSF_MID
#define MAX_START_DIM_EXHAUST_INTENSITY 1000
#define MIN_START_DIM_EXHAUST_INTENSITY 750
#define MAX_CHANGE_DIM_EXHAUST_INTENSITY 100 //value is halfed on increase, full value used for decreases
#define MIN_CHANGE_DIM_EXHAUST_INTENSITY 20 //value is halfed on increase, full value used for decreases
#define CHANCE_DIM_EXHAUST_INTENSITY_INCREASE 10 //percent chance intensity will increase instead of decrease


struct ControlState {
  bool systemEnabled;//complete on/off
  int systemLevel; //0 - day lights | 1 - night lights | 2 - everything

  int esc;

  bool lowBeams;
  bool highBeams;
  bool auxLights;
  bool brakes;
  bool hazards;

  bool driftLights;
  bool underglow;
  bool exhaust;

  bool leftTurn;
  bool rightTurn;
  bool flashLights;
};

struct Level {
  bool headLights;
  bool auxLights;
  bool brakes;
  bool hazards;
  bool flashLights;
  bool turnSignals;
  bool driftLights;
  bool underglow;
  bool exhaust;
};

enum SignalType {
  CRSF,
  SBUS
};

enum LightType {
  RIGHT_HEAD,
  LEFT_HEAD,

  RIGHT_FRONT_TURN,
  LEFT_FRONT_TURN,

  RIGHT_BRAKE,
  LEFT_BRAKE,

  RIGHT_REAR_TURN,
  LEFT_REAR_TURN,

  AUX
};

enum StripType {
  DRIFT_LIGHT,
  UNDERGLOW,
  EXHAUST
};

enum DriftLightType {
  MIDDLE_OUT,
  FRONT_TO_BACK,
  BACK_TO_FRONT
};

enum FlashGroup {
  OFF,
  GROUP1,
  GROUP2
};

struct OutConfig {
  LightType lightType;
  FlashGroup flashGroup;
};

struct StripConfig {
  int numLeds;
  StripType stripType;
  DriftLightType driftLightType;
  CRGB color;
};

struct Config {
  //input
  SignalType signalType;
  int triggerChannel;
  int levelChannel;

  //options
  bool invertSteering;
  bool invertESC;
  bool enableTurnSignals;
  bool turnSignalsAlsoHead;
  bool turnSignalsAlsoBrake;
  bool enableHazards;
  bool enableFlash;

  //Levels
  Level levelCfgs[NUM_LEVELS];

  //Out
  OutConfig outCfgs[NUM_LIGHT_OUTPUTS];

  //Strip
  StripConfig stripCfgs[NUM_STRIPS];

};

Config GetDefaultConfig();

void PrintConfig(Config config);

SignalType GetSignalTypeFromString(const std::string& value);

LightType GetLightTypeFromString(const std::string& value);

StripType GetStripTypeFromString(const std::string& value);

FlashGroup GetFlashGroupFromString(const std::string& value);

DriftLightType GetDriftLightTypeFromString(const std::string& value);

CRGB GetColorFromHexString(const String& hexString);

bool GetBoolFromString(const std::string& value);

#endif