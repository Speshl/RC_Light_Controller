#include <Arduino.h>
#include <Preferences.h>
#include "web_cfg.h"
#include <CrsfSerial.h>
#include "light_handler.h"
#include "strip_handler.h"
#include "storage.h"

// Pass any HardwareSerial port
// "Arduino" users (atmega328) can not use CRSF_BAUDRATE, as the atmega does not support it
// and should pass 250000, but then also must flash the receiver with RCVR_UART_BAUD=250000
// Also note the atmega only has one Serial, so logging to Serial must be removed
CrsfSerial crsf(Serial2, CRSF_BAUDRATE); //Arduino IOT use Serial1, ESP32 use Serial2, Serial is debug console

ControlState controlState;
ControlState lastState;

unsigned long lastUpdateTime = millis();

Config config;
Preferences preferences;

void setup();
void loop();
void getUpdatedControlState();
ControlState filterStateByLevel(ControlState state, unsigned long lastUpdateTime);
void CheckForUpdates();

int main() {
    init();
    setup();
    while(1) {
        loop();
    }
    return 0;
}

void setup() {
  randomSeed(analogRead(0));

  Serial.begin(460800);
  // while(!Serial){
  //   ;
  // }
  Serial.println("starting up...");

  preferences.begin("rclc", false);

  config = CreateOrLoadCfg(&preferences);

  crsf.begin();
  crsf.onPacketChannels = &getUpdatedControlState;
  SetupLights(config);
  SetupStrips(config);
  SetupWifi(&preferences,config);

  controlState.esc = CRSF_MID;

  Serial.println("start up complete");
}

void loop() {
  //Serial.println("loop start");
  crsf.loop();

  CheckForUpdates();
  ControlState filteredState = filterStateByLevel(controlState, lastUpdateTime);

  UpdateLights(filteredState);
  UpdateStrips(filteredState);

  unsigned long startMillis = millis();  // Get the current time
  while (millis() - startMillis < 5) {  // Loop for 10 milliseconds
    ProcessWifi();
  }
}

void getUpdatedControlState(){
  //Serial.println("Got Commands");
  int steer = crsf.getChannel(STEER_CHANNEL);
  int esc = crsf.getChannel(ESC_CHANNEL);
  int level = crsf.getChannel(LIGHT_LEVEL_CHANNEL);
  int enabled = crsf.getChannel(SYSTEM_ENABLE_CHANNEL);

  // Serial.print("Steer: ");
  // Serial.print(steer);
  // Serial.print(" Esc: ");
  // Serial.print(esc);
  // Serial.print(" Enabled: ");
  // Serial.print(enabled);
  // Serial.print(" Level: ");
  // Serial.println(level);

  if(config.invertSteering){
    if(steer > CRSF_MID+TURN_FLEX_RANGE){
    controlState.leftTurn = true;
    }else{
      controlState.leftTurn = false;
    }

    if(steer < CRSF_MID-TURN_FLEX_RANGE){
      controlState.rightTurn = true;
    }else{
      controlState.rightTurn = false;
    }
  }else{
    if(steer > CRSF_MID+TURN_FLEX_RANGE){
      controlState.rightTurn = true;
    }else{
      controlState.rightTurn = false;
    }

    if(steer < CRSF_MID-TURN_FLEX_RANGE){
      controlState.leftTurn = true;
    }else{
      controlState.leftTurn = false;
    }
  }  

  if(esc < CRSF_MID-FLEX_RANGE){
    controlState.brakes = true;
  }else{
    controlState.brakes = false;
  }

  if(level < CRSF_MID-FLEX_RANGE){
    controlState.systemLevel = 0; //day time lighting
  }else if(level > CRSF_MID+FLEX_RANGE){
    controlState.systemLevel = 2; //drift lighting
  }else{
    controlState.systemLevel = 1; //night time lighting
  }

  if(enabled > CRSF_MID+FLEX_RANGE){
    controlState.systemEnabled = true;
  }else{
    controlState.systemEnabled = false;
  }

  if(esc > CRSF_MID+ESC_DEADZONE || esc < CRSF_MID-ESC_DEADZONE){
    controlState.esc = esc; 
  }else{
    controlState.esc = CRSF_MID; 
  }
}

ControlState filterStateByLevel(ControlState state, unsigned long lastUpdateTime){
  ControlState returnValue;
  Level level = config.levelCfgs[state.systemLevel];

  returnValue.systemEnabled = state.systemEnabled;
  returnValue.esc = state.esc;  

  if(level.headLights){
    returnValue.highBeams = true;
    returnValue.lowBeams = false;
  }else{
    returnValue.highBeams = false;
    returnValue.lowBeams = false;
  }

  if(level.auxLights){
    returnValue.auxLights = true;
  }else{
    returnValue.auxLights = false;
  }

  if(level.brakes){
    returnValue.brakes = state.brakes;
  }

  if(level.flashLights){
    returnValue.flashLights = true;
  }else{
    returnValue.flashLights = false;
  }

  if(level.turnSignals && config.enableTurnSignals){
    returnValue.leftTurn = state.leftTurn;
    returnValue.rightTurn = state.rightTurn;
  }else{
    returnValue.leftTurn = false;
    returnValue.rightTurn = false;
  }

  if(level.driftLights && ENABLE_DRIFT_LIGHT){
    returnValue.driftLights = true;
  }else{
    returnValue.driftLights = false;
  }

  if(level.underglow && ENABLE_UNDERGLOW){
    returnValue.underglow = true;
  }else{
    returnValue.underglow = false;
  }

  if(level.exhaust && ENABLE_EXHAUST){
    returnValue.exhaust = true;
  }else{
    returnValue.exhaust = false;
  }

  if(level.hazards && config.enableHazards){
    if(lastUpdateTime + IDLE_TIME < millis()) {
      returnValue.hazards = true;
    }else{
      returnValue.hazards = false;
    }
  }

  return returnValue;
}

void CheckForUpdates(){
  bool hadUpdate = false;
  if(controlState.esc != lastState.esc){
    hadUpdate = true;
  }else if(controlState.brakes != lastState.brakes){
    hadUpdate = true;
  }
  else if(controlState.systemLevel != lastState.systemLevel){
    hadUpdate = true;
  }
  else if(controlState.systemEnabled != lastState.systemEnabled){
    hadUpdate = true;
  }
  else if(controlState.rightTurn != lastState.rightTurn){
    hadUpdate = true;
  }
  else if(controlState.leftTurn != lastState.leftTurn){
    hadUpdate = true;
  }

  lastState = controlState;

  if(hadUpdate){
    lastUpdateTime = millis();
  }
}