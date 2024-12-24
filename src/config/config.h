#ifndef CONFIG_H
#define CONFIG_H
#include "Arduino.h"
#include <FastLED.h>
// #include <Preferences.h>
#include <SPIFFS.h>
#include <ArduinoJson.h> // ArduinoJson library

#define ENABLE_FORCE_CONFIG true
#define DEFAULT_CONFIG_FILE_PATH "/config/default.json"
#define CONFIG_FILE_PATH "/config/config.json"
#define FORCE_FILE_PATH "/config/forced.json"

#define ENABLE_DEMO_MODE true
#define TIME_TIL_DEMO 1000

//led strip configs
#define COLOR_ORDER RGB
#define CHIPSET WS2812B
#define VOLTS 5
#define MAX_AMPS 500 //value in milliamps
#define BRIGHTNESS 100

//INPUT CONFIG
#define SERIAL2_RX 16
#define SERIAL2_TX 17
#define ENABLE_FAST_SBUS false

//Pinout order for stacked narrow version: 32,33,25,26,27,14,12,13,4,5,18,19
//Pinout order for 16c version: 32,33,25,26,27,14,12,13,4,5,18,19,23,22,21,2
#define MAX_CHANNELS 16

#define OUTPUT_PIN_1 13
#define OUTPUT_PIN_2 12
#define OUTPUT_PIN_3 14
#define OUTPUT_PIN_4 27
#define OUTPUT_PIN_5 26
#define OUTPUT_PIN_6 25
#define OUTPUT_PIN_7 33
#define OUTPUT_PIN_8 32

#define OUTPUT_PIN_9 2
#define OUTPUT_PIN_10 4
#define OUTPUT_PIN_11 5
#define OUTPUT_PIN_12 18
#define OUTPUT_PIN_13 19
#define OUTPUT_PIN_14 21
#define OUTPUT_PIN_15 22
#define OUTPUT_PIN_16 23

const byte pinNums[MAX_CHANNELS] = {
  OUTPUT_PIN_1,
  OUTPUT_PIN_2,
  OUTPUT_PIN_3,
  OUTPUT_PIN_4,
  OUTPUT_PIN_5,
  OUTPUT_PIN_6,
  OUTPUT_PIN_7,
  OUTPUT_PIN_8,
  OUTPUT_PIN_9,
  OUTPUT_PIN_10,
  OUTPUT_PIN_11,
  OUTPUT_PIN_12,
  OUTPUT_PIN_13,
  OUTPUT_PIN_14,
  OUTPUT_PIN_15,
  OUTPUT_PIN_16
  }; //32,33,25,26,27,14,12,13,4,5,18,19

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

//SBUS CONFIG
#define SBUS_LOW 172
#define SBUS_MID 992
#define SBUS_HIGH 1811
#define SBUS_DEADZONE 20
#define NO_SIGNAL_TIMES_TIL_MID 10

#define TIME_TIL_FLASH 5000
#define TURN_FLASH_INTERVAL 500
#define STROBE_FLASH_INTERVAL 100

#define NUM_LEVELS 3

#define MAX_EXHAUST_INTENSITY 1000

#define POP_EXHAUST_LEVEL_PERCENT 95
#define POP_EXHAUST_LEVEL (((INPUT_HIGH - INPUT_MID) / 100) * POP_EXHAUST_LEVEL_PERCENT) + INPUT_MID
#define MAX_START_POP_EXHAUST_INTENSITY 1000
#define MIN_START_POP_EXHAUST_INTENSITY 950
#define MAX_CHANGE_POP_EXHAUST_INTENSITY 100 //value is halfed on increase, full value used for decreases
#define MIN_CHANGE_POP_EXHAUST_INTENSITY 50 //value is halfed on increase, full value used for decreases
#define CHANCE_POP_EXHAUST_INTENSITY_INCREASE 30 //percent chance intensity will increase instead of decrease

#define BRIGHT_EXHAUST_LEVEL_PERCENT 80
#define BRIGHT_EXHAUST_LEVEL (((INPUT_HIGH - INPUT_MID) / 100) * BRIGHT_EXHAUST_LEVEL_PERCENT) + INPUT_MID
#define MAX_START_BRIGHT_EXHAUST_INTENSITY 900
#define MIN_START_BRIGHT_EXHAUST_INTENSITY 800
#define MAX_CHANGE_BRIGHT_EXHAUST_INTENSITY 30 //value is halfed on increase, full value used for decreases
#define MIN_CHANGE_BRIGHT_EXHAUST_INTENSITY 5 //value is halfed on increase, full value used for decreases
#define CHANCE_BRIGHT_EXHAUST_INTENSITY_INCREASE 10 //percent chance intensity will increase instead of decrease

#define DIM_EXHAUST_LEVEL_PERCENT 60
#define DIM_EXHAUST_LEVEL (((INPUT_HIGH - INPUT_MID) / 100) * DIM_EXHAUST_LEVEL_PERCENT) + INPUT_MID
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
  UNDERGLOW,
  THROTTLE_BRAKE,
  EXHAUST,
  EMERGENCY,
};

struct Animations{
  bool underglow;
  bool throttleBrakeLight;
  bool exhaustFlame;
  bool emergencyLights;
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
  bool reverse;
};

enum FlameType {
  NO_FLAME,
  DIM_FLAME,
  BRIGHT_FLAME,
  POP_FLAME
};

struct BlinkState{
  bool on;
  bool blinkOn;
  unsigned long startTime;
};

struct RoleStates{
  BlinkState leftTurn;
  BlinkState rightTurn;
  BlinkState hazards;
  BlinkState strobe1;
  BlinkState strobe2;
};

struct FlameState {
  int intensity;
  FlameType type;
  FlameType lastType;
  unsigned long startTime;
  int lastEscValue;
  int lastMaxEscValue;
};

struct UnderglowState {
  int paletteBrightness;
  int palettePos;
  int paletteSpeed;
  
  int breatheBrightness;
  int breatheHold;
  int breatheState;
};

struct EmergencyState {
  int strobePos;
  unsigned long lastStrobeChange;
  bool solidAlternateColor;
};

struct AnimationState {

  RoleStates roleStates;

  FlameState flame;
  UnderglowState underglow;
  EmergencyState emergency;
};

enum UnderGlowType {
  UNDERGLOW_SOLID,
  UNDERGLOW_BREATHE,
  UNDERGLOW_PALETTE,
};

enum UnderGlowPalette {
  UNDERGLOW_RAINBOW,
  UNDERGLOW_CLOUD,
  UNDERGLOW_LAVA,
  UNDERGLOW_OCEAN,
  UNDERGLOW_FOREST,
  UNDERGLOW_PARTY,
  UNDERGLOW_HEAT
};

struct UnderglowConfig {
  UnderGlowType type;
  CRGB primaryColor;
  CRGB secondaryColor;
  UnderGlowPalette palette;
  uint8_t speed;
};

enum ThrottleBrakeType {
  TB_TOP,
  TB_MID,
  TB_BOTTOM
};

struct ThrottleBrakeConfig {
  ThrottleBrakeType type;
  CRGB throttleColor;
  CRGB brakeColor;
};

enum ExhaustPalette {
  DEFAULT_EXHAUST_PALETTE,
  BLUE_EXHAUST_PALETTE,
  GREEN_EXHAUST_PALETTE,
  PURPLE_EXHAUST_PALETTE,
  CYAN_EXHAUST_PALETTE,
  RAINBOW_EXHAUST_PALETTE,
};

struct ExhaustConfig {
  ExhaustPalette palette;
};

enum EmergencyType {
  EMERGENCY_SOLID,
  EMERGENCY_WRAP
};

struct EmergencyConfig {
  EmergencyType type;
  CRGB primaryColor;
  CRGB secondaryColor;
  //uint8_t speed;
};

struct OutputChannelConfig {
  int pin;
  OutputType type;
  StripAnimation stripAnimation;
  Roles roles;
  int stripLedCount;
  EOrder colorOrder;

  UnderglowConfig underglowConfig;
  ThrottleBrakeConfig throttleBrakeConfig;
  ExhaustConfig exhaustConfig;
  EmergencyConfig emergencyConfig;
};

struct OutputConfig {
  OutputChannelConfig channelConfigs[MAX_CHANNELS];
};

struct SysConfig {
  bool forcedShutdown;
};

struct Config {
  SysConfig sysConfig;
  InputConfig inputConfig;
  OutputConfig outputConfig;
  LevelConfig levelConfigs[NUM_LEVELS];
};

struct DemoState{
  int step;
  InputValues inputValues;
};

struct State{
  Config config;

  InputValues inputValues;
  InputState inputState;
  AnimationState animationState;
  DemoState demoState;
};

Config GetDefaultConfig();

Config GetBaseConfig();

Config CreateOrLoadCfg();

void PrintConfig(Config cfg);

const char* ColorOrderToString(EOrder order);

Config parseConfig(JsonDocument doc);
void parseInputConfig(Config *cfg, JsonVariant doc);
void parseLevelConfig(Config *cfg, JsonVariant doc);
void parseOutConfig(Config *cfg, JsonVariant doc, bool web);

JsonDocument ConfigToJson(Config *cfg);
JsonDocument InputConfigToJson(Config *cfg);
JsonDocument LevelConfigToJson(Config *cfg, int levelNum);
JsonDocument OutConfigToJson(Config *cfg, int outNum);

StripAnimation GetStripAnimationFromString(const std::string& value);

void SaveConfig(Config cfg);

void SaveConfigWithRestart(Config cfg);

#endif