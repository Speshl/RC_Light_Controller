#ifndef CONFIG_H
#define CONFIG_H
#include "Arduino.h"
#include <FastLED.h>
#include <Preferences.h>

//led strip configs
#define COLOR_ORDER RGB
#define CHIPSET WS2812B
#define VOLTS 5
#define MAX_AMPS 500 //value in milliamps
#define BRIGHTNESS 100

//OUTPUT CONFIG
#define MAX_CHANNELS 12

#define OUTPUT_PIN_1 32
#define OUTPUT_PIN_2 33
#define OUTPUT_PIN_3 25
#define OUTPUT_PIN_4 26
#define OUTPUT_PIN_5 27
#define OUTPUT_PIN_6 14
#define OUTPUT_PIN_7 12
#define OUTPUT_PIN_8 13
#define OUTPUT_PIN_9 4
#define OUTPUT_PIN_10 5
#define OUTPUT_PIN_11 18
#define OUTPUT_PIN_12 19
const byte pinNums[MAX_CHANNELS] = {32,33,25,26,27,14,12,13,4,5,18,19};//TODO Confirm Pins

#define NUM_STRIP_LEDS 100

//INPUT CONFIG
#define STEER_CHANNEL 1
#define ESC_CHANNEL 2
#define SYSTEM_ENABLE_CHANNEL 10
#define LIGHT_LEVEL_CHANNEL 11

#define INPUT_THRESHOLD 20
#define LEVEL_THRESHOLD 200
#define TURN_THRESHOLD 400
#define INPUT_LOW 0
#define INPUT_MID 500 //0-499 is low, 500 is mid, 501-1000 is high
#define INPUT_HIGH 1000

//CRSF CONFIG
#define CRSF_LOW 990
#define CRSF_MID 1500
#define CRSF_HIGH 2011
#define CRSF_DEADZONE 20

#define TIME_TIL_FLASH 5000
#define TURN_FLASH_INTERVAL 500
#define STROBE_FLASH_INTERVAL 100

#define NUM_LEVELS 3

#define MAX_EXHAUST_INTENSITY 1000

#define POP_EXHAUST_LEVEL (((INPUT_HIGH - INPUT_MID) / 100) * 95) + INPUT_MID
#define MAX_START_POP_EXHAUST_INTENSITY 1000
#define MIN_START_POP_EXHAUST_INTENSITY 950
#define MAX_CHANGE_POP_EXHAUST_INTENSITY 100 //value is halfed on increase, full value used for decreases
#define MIN_CHANGE_POP_EXHAUST_INTENSITY 50 //value is halfed on increase, full value used for decreases
#define CHANCE_POP_EXHAUST_INTENSITY_INCREASE 30 //percent chance intensity will increase instead of decrease

#define BRIGHT_EXHAUST_LEVEL (((INPUT_HIGH - INPUT_MID) / 100) * 80) + INPUT_MID
#define MAX_START_BRIGHT_EXHAUST_INTENSITY 900
#define MIN_START_BRIGHT_EXHAUST_INTENSITY 800
#define MAX_CHANGE_BRIGHT_EXHAUST_INTENSITY 30 //value is halfed on increase, full value used for decreases
#define MIN_CHANGE_BRIGHT_EXHAUST_INTENSITY 5 //value is halfed on increase, full value used for decreases
#define CHANCE_BRIGHT_EXHAUST_INTENSITY_INCREASE 10 //percent chance intensity will increase instead of decrease

#define DIM_EXHAUST_LEVEL (((INPUT_HIGH - INPUT_MID) / 100) * 60) + INPUT_MID
#define MAX_START_DIM_EXHAUST_INTENSITY 400
#define MIN_START_DIM_EXHAUST_INTENSITY 200
#define MAX_CHANGE_DIM_EXHAUST_INTENSITY 40 //value is halfed on increase, full value used for decreases
#define MIN_CHANGE_DIM_EXHAUST_INTENSITY 20 //value is halfed on increase, full value used for decreases
#define CHANCE_DIM_EXHAUST_INTENSITY_INCREASE 0 //percent chance intensity will increase instead of decrease


enum InputType {
  CRSF,
  SBUS
};


struct InputConfig {
  InputType type;

  int steerChannel;
  bool steerInverted;

  int escChannel;
  bool escInverted;

  int enableChannel;
  bool enabledInverted;

  int levelChannel;
  bool levelInverted;
};

struct Roles {
  bool leftTurn;
  bool rightTurn;
  bool brake;
  bool tail;
  bool head;
  bool reverse;
  bool hazard;
  bool running;
  bool aux1;
  bool aux2;
  bool strobe1;
  bool strobe2;
};

enum OutputType {
  LED_STRIP,
  SINGLE_LED
};

enum StripAnimation {
  NONE,
  UNDERGLOW_SOLID,
  UNDERGLOW_BREATHE,
  UNDERGLOW_CYCLE,
  //UNDERGLOW_CHASE,
  THROTTLE_BRAKE_LIGHT_BOTTOM,
  THROTTLE_BRAKE_LIGHT_TOP,
  THROTTLE_BRAKE_LIGHT_MIDDLE,
  EXHAUST_FLAME,
  POLICE_LIGHTS_SOLID,
  POLICE_LIGHTS_WRAP,
  CAUTION_LIGHTS_SOLID,
  CAUTION_LIGHTS_WRAP,
};

struct Animations{
  bool underglow;
  bool throttleBrakeLight;
  bool exhaustFlame;
  bool policeLights;
  bool cautionLights;
};

struct LevelConfig {
  Roles roles;
  Animations animations;
};

struct InputValues {
  int steer;
  int esc;
  int level;
  int enabled;

  unsigned long lastUpdate;
};

struct InputState {
  bool enabled;
  int level;
  bool leftTurn;
  bool rightTurn;
  bool hazards;
  bool brakes;
};

enum FlameType {
  NO_FLAME,
  DIM_FLAME,
  BRIGHT_FLAME,
  POP_FLAME
};

struct AnimationState {
  bool leftTurnOn;
  bool leftTurnBlinkOn;
  unsigned long leftTurnStartTime;

  bool rightTurnOn;
  bool rightTurnBlinkOn;
  unsigned long rightTurnStartTime;

  bool hazardsOn;
  bool hazardsBlinkOn;
  unsigned long hazardsStartTime;

  bool strobe1BlinkOn;
  bool strobe2BlinkOn;

  int flameIntensity;
  CRGBPalette16 flamePalette;
  int lastEscValue;
  int lastMaxEscValue;
  FlameType currentFlameType;
  FlameType lastFlameType;
  unsigned long flameStartTime;

  CRGB underglowCycleColor;
  int underglowPalletePos;

  int wrapPoliceStrobePos;
  unsigned long wrapPoliceLightLastChange;
  bool solidPoliceAlternateColor;
};

struct OutputChannelConfig {
  int pin;
  OutputType type;
  StripAnimation stripAnimation;
  Roles roles;
  int stripLedCount;
  CRGB color;
  EOrder colorOrder;
};

struct OutputConfig {
  OutputChannelConfig channelConfigs[MAX_CHANNELS];
};


struct Config {
  InputConfig inputConfig;
  OutputConfig outputConfig;
  LevelConfig levelConfigs[NUM_LEVELS];
};

struct State{
  Config config;

  InputValues inputValues;
  InputState inputState;
  AnimationState animationState;
};


Config GetDefaultConfig();

Config CreateOrLoadCfg();

void SaveConfig(Config cfg);

#endif