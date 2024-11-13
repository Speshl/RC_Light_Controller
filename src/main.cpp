#include <Arduino.h>
#include <CrsfSerial.h>
#include "config/config.h"
#include "input/input.h"
#include "web/web.h"
#include "output/output.h"
#include "animation/animation.h"

State state;

bool lightsPaused = false;

void setup();
void loop();
void SetupInitialStartState(State* state);
void ApplyInputToState(State* state, InputValues input);
bool UpdatePauseState(bool currentPauseState);
void PrintState(State* state);
void ApplyDemoInput(State* state);
void SetInitialInput(State* state);


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

  //setup initial start state
  SetupInitialStartState(&state);
  //setup RC input (CRSF/SBUS)
  SetupInput(&state.config);
  //setup wifi/web server
  SetupWifi(state.config);
  //setup led outputs
  SetupOutput(state.config);

  SetInitialInput(&state);

  Serial.println("start up complete");
}

void loop() {
  lightsPaused = UpdatePauseState(lightsPaused);

  if(!lightsPaused){
    //check for new RC input
    InputValues newInput = GetLatestInput();

    //sync new input to state
    ApplyInputToState(&state, newInput);

    //calculate shared animation states
    CalculateAnimations(&state);

    //apply state to outputs
    ShowState(&state);
  }

  //check for new wifi input
  ProcessWifi();// this will cause device to reset if config is updated
}

bool UpdatePauseState(bool currentPauseState){
  if(currentPauseState){
    return currentPauseState;
  }


  if(IsActiveWebClient()){
    Serial.println("Web Client Active, Pausing Lights");
    return true;
  }
  return currentPauseState;
}

void SetupInitialStartState(State* state){
  state->config = CreateOrLoadCfg();

  if(state->config.sysConfig.forcedShutdown){
    Serial.println("Forced Shutdown Detected, Pausing Lights");
    lightsPaused = true;
    state->config.sysConfig.forcedShutdown = false;
    SaveConfig(state->config);
  }

  return;
}

void ApplyInputToState(State* state, InputValues input){
  unsigned long currentTime = millis();

  if( ENABLE_DEMO_MODE && currentTime - input.lastUpdate > TIME_TIL_DEMO){
    state->inputState.hazards = false;
    ApplyDemoInput(state);
    input = state->demoState.inputValues;
  }else {
    bool updateFound = false;
    //check if different from current state
    if(input.steer != state->inputValues.steer){
      updateFound = true;
    }else if(input.esc != state->inputValues.esc){
      updateFound = true;
    }else if(input.level != state->inputValues.level){
      updateFound = true;
    }else if(input.enabled != state->inputValues.enabled){
      updateFound = true;
    }

    if(!updateFound){
      if(currentTime - state->inputValues.lastUpdate > TIME_TIL_FLASH){
        state->inputState.hazards = true;
      }
      return;
    }

    //PrintInput(input);

    state->inputValues.steer = input.steer;
    state->inputValues.esc = input.esc;
    state->inputValues.level = input.level;
    state->inputValues.enabled = input.enabled;

    state->inputState.hazards = false;
    state->inputValues.lastUpdate = input.lastUpdate;
  }

  state->inputState.enabled = input.enabled > INPUT_MID+LEVEL_THRESHOLD;

  if(input.level < INPUT_MID-LEVEL_THRESHOLD){
    state->inputState.level = 0;
  }else if(input.level > INPUT_MID+LEVEL_THRESHOLD){
    state->inputState.level = 2;
  }else{
    state->inputState.level = 1;
  }

  state->inputState.leftTurn = input.steer < INPUT_MID - TURN_THRESHOLD;
  state->inputState.rightTurn = input.steer > INPUT_MID + TURN_THRESHOLD;
  state->inputState.brakes = input.esc < INPUT_MID - INPUT_THRESHOLD;

  //PrintState(state);

  return;
}

void PrintState(State* state){
  Serial.println("State: ");
  Serial.print("Enabled: ");
  Serial.println(state->inputState.enabled);
  Serial.print("Level: ");
  Serial.println(state->inputState.level);
  Serial.print("Left Turn: ");
  Serial.println(state->inputState.leftTurn);
  Serial.print("Right Turn: ");
  Serial.println(state->inputState.rightTurn);
  Serial.print("Hazards: ");
  Serial.println(state->inputState.hazards);
  Serial.print("Brakes: ");
  Serial.println(state->inputState.brakes);
  return;
}

void SetInitialInput(State* state){
  state->inputValues.steer = INPUT_MID;
  state->inputValues.esc = INPUT_MID;
  state->inputValues.level = 0;
  state->inputValues.enabled = INPUT_HIGH;
  state->inputValues.lastUpdate = millis();

  state->demoState.inputValues.steer = INPUT_MID;
  state->demoState.inputValues.esc = INPUT_MID;
  state->demoState.inputValues.level = 0;
  state->demoState.inputValues.enabled = INPUT_HIGH;
  state->demoState.inputValues.lastUpdate = millis();
  return;
}

void ApplyDemoInput(State* state){
  // Serial.print("Demo Step: ");
  // Serial.println(state->demoState.step);

  switch(state->demoState.step){
    case 0:
      Serial.println("Demo Mode");
      state->demoState.inputValues.enabled = 1000;
      state->demoState.inputValues.level = 0;
      state->demoState.inputValues.steer = 0;
      state->demoState.inputValues.esc = 0;
      state->demoState.step++;
      break;

    case 1:
    case 6:
    case 11:
      state->demoState.inputValues.steer ++;
      if(state->demoState.inputValues.steer > INPUT_HIGH){
        state->demoState.inputValues.steer = INPUT_HIGH;
        state->demoState.step++;
      }
      break;

    case 2:
    case 7:
    case 12:
      state->demoState.inputValues.steer --;
      if(state->demoState.inputValues.steer < INPUT_LOW){
        state->demoState.inputValues.steer = INPUT_LOW;
        state->demoState.step++;
      }
      break;

    case 3:
    case 8:
    case 13:
      state->demoState.inputValues.esc ++;
      if(state->demoState.inputValues.esc > INPUT_HIGH){
        state->demoState.inputValues.esc = INPUT_HIGH;
        state->demoState.step++;
      }
      break;

    case 4:
    case 9:
    case 14:
      state->demoState.inputValues.esc --;
      if(state->demoState.inputValues.esc < INPUT_LOW){
        state->demoState.inputValues.esc = INPUT_LOW;
        state->demoState.step++;
      }
      break;

    case 5:
    case 10:
    case 15:
      state->demoState.inputValues.level += INPUT_MID;
      state->demoState.step++;
      if(state->demoState.inputValues.level > INPUT_HIGH){
        state->demoState.inputValues.level = INPUT_LOW;
        state->demoState.step = 0;
      }
      break;
  }
}
