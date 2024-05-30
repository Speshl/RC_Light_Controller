#include "light_handler.h"

uint8_t light_output_pins[NUM_LIGHT_OUTPUTS] = {LIGHT_OUT_1,LIGHT_OUT_2,LIGHT_OUT_3,LIGHT_OUT_4,LIGHT_OUT_5,LIGHT_OUT_6,LIGHT_OUT_7,LIGHT_OUT_8};

Light out_lights[NUM_LIGHT_OUTPUTS];

Config lightConfig;

//private functions
void updateHead(ControlState state, int i){
  if(!state.systemEnabled){
    //Serial.println("system off");
    analogWrite(light_output_pins[i], 0); //lights off
    out_lights[i].on = false;
    return;
  }

  if(state.flashLights && lightConfig.outCfgs[i].flashGroup != OFF){
    int activeGroup = (millis() / FLASH_TIME) % 2;
    if(activeGroup == 0 && lightConfig.outCfgs[i].flashGroup == GROUP1){
      analogWrite(light_output_pins[i], 255); //lights on
      out_lights[i].on = true;
    }else if(activeGroup == 1 && lightConfig.outCfgs[i].flashGroup == GROUP2){
      analogWrite(light_output_pins[i], 255); //lights on
      out_lights[i].on = true;
    }else{
      analogWrite(light_output_pins[i], 0); //lights off
      out_lights[i].on = false;
    }
    return;
  }


  if(state.lowBeams){
    //Serial.println("headlight low");
    analogWrite(light_output_pins[i], 85);
    out_lights[i].on = true;
    return;
  }
  
  if(state.highBeams){
    //Serial.println("headlight high");
    analogWrite(light_output_pins[i], 255);
    out_lights[i].on = true;
    return;
  }

  //Serial.println("headlight off");
  analogWrite(light_output_pins[i], 0);
  out_lights[i].on = false;
}

void updateBrake(ControlState state, int i){
  if(!state.systemEnabled){
    analogWrite(light_output_pins[i], 0); //lights off
    out_lights[i].on = false;
    return;
  }

  if(state.brakes){
    analogWrite(light_output_pins[i], 255);
    out_lights[i].on = true;
    return;
  }

  if(state.flashLights && lightConfig.outCfgs[i].flashGroup != OFF){
    int activeGroup = (millis() / FLASH_TIME) % 2;
    if(activeGroup == 0 && lightConfig.outCfgs[i].flashGroup == GROUP1){
      analogWrite(light_output_pins[i], 85); //lights on
      out_lights[i].on = true;
    }else if(activeGroup == 1 && lightConfig.outCfgs[i].flashGroup == GROUP2){
      analogWrite(light_output_pins[i], 85); //lights on
      out_lights[i].on = true;
    }else{
      analogWrite(light_output_pins[i], 0); //lights off
      out_lights[i].on = false;
    }
    return;
  }
  
  if(state.lowBeams || state.highBeams){
    analogWrite(light_output_pins[i], 85);
    out_lights[i].on = true;
  }else{
    analogWrite(light_output_pins[i], 0);
    out_lights[i].on = false;
  }
}

void updateLFTurn(ControlState state, int i){
  if(!state.systemEnabled){
    analogWrite(light_output_pins[i], 0); //lights off
    out_lights[i].on = false;
    return;
  }

  if((state.leftTurn && lightConfig.enableTurnSignals) || (state.hazards && lightConfig.enableHazards)){
    if(millis() % 1000 < HAZARD_TIME){ //flash on first half of second
      analogWrite(light_output_pins[i], 255);
      out_lights[i].on = true;
    }else{//flash off last half of second
      analogWrite(light_output_pins[i], 0);
      out_lights[i].on = false;
    }
    return;
  }
  
  if(state.flashLights && lightConfig.outCfgs[i].flashGroup != OFF){
    int activeGroup = (millis() / FLASH_TIME) % 2;
    if(activeGroup == 0 && lightConfig.outCfgs[i].flashGroup == GROUP1){
      analogWrite(light_output_pins[i], 85); //lights on
      out_lights[i].on = true;
    }else if(activeGroup == 1 && lightConfig.outCfgs[i].flashGroup == GROUP2){
      analogWrite(light_output_pins[i], 85); //lights on
      out_lights[i].on = true;
    }else{
      analogWrite(light_output_pins[i], 0); //lights off
      out_lights[i].on = false;
    }
    return;
  }
  
  if(state.lowBeams && lightConfig.turnSignalsAlsoHead){
    analogWrite(light_output_pins[i], 85);
    out_lights[i].on = true;
  }else if(state.highBeams && lightConfig.turnSignalsAlsoHead){
    analogWrite(light_output_pins[i], 255);
    out_lights[i].on = true;
  }else{
    analogWrite(light_output_pins[i], 0);
    out_lights[i].on = false;
  }
}

void updateRFTurn(ControlState state, int i){
  if(!state.systemEnabled){
    analogWrite(light_output_pins[i], 0); //lights off
    out_lights[i].on = false;
    return;
  }

  if((state.rightTurn && lightConfig.enableTurnSignals) || (state.hazards && lightConfig.enableHazards)){
    if(millis() % 1000 < HAZARD_TIME){ //flash on first half of second
      analogWrite(light_output_pins[i], 255);
      out_lights[i].on = true;
    }else{//flash off last half of second
      analogWrite(light_output_pins[i], 0);
      out_lights[i].on = false;
    }
    return;
  }
  
  if(state.flashLights && lightConfig.outCfgs[i].flashGroup != OFF){
    int activeGroup = (millis() / FLASH_TIME) % 2;
    if(activeGroup == 0 && lightConfig.outCfgs[i].flashGroup == GROUP1){
      analogWrite(light_output_pins[i], 85); //lights on
      out_lights[i].on = true;
    }else if(activeGroup == 1 && lightConfig.outCfgs[i].flashGroup == GROUP2){
      analogWrite(light_output_pins[i], 85); //lights on
      out_lights[i].on = true;
    }else{
      analogWrite(light_output_pins[i], 0); //lights off
      out_lights[i].on = false;
    }
    return;
  }
  
  if(state.lowBeams && lightConfig.turnSignalsAlsoHead){
    analogWrite(light_output_pins[i], 85);
    out_lights[i].on = true;
  }else if(state.highBeams && lightConfig.turnSignalsAlsoHead){
    analogWrite(light_output_pins[i], 255);
    out_lights[i].on = true;
  }else{
    analogWrite(light_output_pins[i], 0);
    out_lights[i].on = false;
  }
}

void updateRRTurn(ControlState state, int i){
  if(!state.systemEnabled){
    analogWrite(light_output_pins[i], 0); //lights off
    out_lights[i].on = false;
    return;
  }

  if((state.rightTurn && lightConfig.enableTurnSignals) || (state.hazards && lightConfig.enableHazards)){
    if(millis() % 1000 < HAZARD_TIME){ //flash on first half of second
      analogWrite(light_output_pins[i], 255);
      out_lights[i].on = true;
    }else{//flash off last half of second
      analogWrite(light_output_pins[i], 0);
      out_lights[i].on = false;
    }
    return;
  }
  
  if(state.brakes && lightConfig.turnSignalsAlsoBrake){
    analogWrite(light_output_pins[i], 255);
    out_lights[i].on = true;
    return;
  }
  
  if(state.flashLights && lightConfig.outCfgs[i].flashGroup != OFF){
    int activeGroup = (millis() / FLASH_TIME) % 2;
    if(activeGroup == 0 && lightConfig.outCfgs[i].flashGroup == GROUP1){
      analogWrite(light_output_pins[i], 85); //lights on
      out_lights[i].on = true;
    }else if(activeGroup == 1 && lightConfig.outCfgs[i].flashGroup == GROUP2){
      analogWrite(light_output_pins[i], 85); //lights on
      out_lights[i].on = true;
    }else{
      analogWrite(light_output_pins[i], 0); //lights off
      out_lights[i].on = false;
    }
    return;
  }
  
  if((state.lowBeams || state.highBeams) && lightConfig.turnSignalsAlsoBrake){
    analogWrite(light_output_pins[i], 85);
    out_lights[i].on = true;
  }else{
    analogWrite(light_output_pins[i], 0);
    out_lights[i].on = false;
  }
}

void updateLRTurn(ControlState state, int i){
  if(!state.systemEnabled){
    analogWrite(light_output_pins[i], 0); //lights off
    out_lights[i].on = false;
    return;
  }

  if((state.leftTurn && lightConfig.enableTurnSignals) || (state.hazards && lightConfig.enableHazards)){
    if(millis() % 1000 < HAZARD_TIME){ //flash on first half of second
      analogWrite(light_output_pins[i], 255);
      out_lights[i].on = true;
    }else{//flash off last half of second
      analogWrite(light_output_pins[i], 0);
      out_lights[i].on = false;
    }
    return;
  }
  
  if(state.brakes && lightConfig.turnSignalsAlsoBrake){
    analogWrite(light_output_pins[i], 255);
    out_lights[i].on = true;
    return;
  }
  
  if(state.flashLights && lightConfig.outCfgs[i].flashGroup != OFF){
    int activeGroup = (millis() / FLASH_TIME) % 2;
    if(activeGroup == 0 && lightConfig.outCfgs[i].flashGroup == GROUP1){
      analogWrite(light_output_pins[i], 85); //lights on
      out_lights[i].on = true;
    }else if(activeGroup == 1 && lightConfig.outCfgs[i].flashGroup == GROUP2){
      analogWrite(light_output_pins[i], 85); //lights on
      out_lights[i].on = true;
    }else{
      analogWrite(light_output_pins[i], 0); //lights off
      out_lights[i].on = false;
    }
    return;
  }
  
  if((state.lowBeams || state.highBeams) && lightConfig.turnSignalsAlsoBrake){
    analogWrite(light_output_pins[i], 85);
    out_lights[i].on = true;
  }else{
    analogWrite(light_output_pins[i], 0);
    out_lights[i].on = false;
  }
}

void updateAux(ControlState state, int i){
  if(!state.systemEnabled){
    analogWrite(light_output_pins[i], 0); //lights off
    out_lights[i].on = false;
    return;
  }

  if(state.auxLights){

    if(state.flashLights && lightConfig.outCfgs[i].flashGroup != OFF){
      int activeGroup = (millis() / FLASH_TIME) % 2;
      if(activeGroup == 0 && lightConfig.outCfgs[i].flashGroup == GROUP1){
        analogWrite(light_output_pins[i], 255); //lights on
        out_lights[i].on = true;
      }else if(activeGroup == 1 && lightConfig.outCfgs[i].flashGroup == GROUP2){
        analogWrite(light_output_pins[i], 255); //lights on
        out_lights[i].on = true;
      }else{
        analogWrite(light_output_pins[i], 0); //lights off
        out_lights[i].on = false;
      }
      return;
    }

    analogWrite(light_output_pins[i], 255); //lights off
    out_lights[i].on = true;
  }else{
    analogWrite(light_output_pins[i], 0); //lights off
    out_lights[i].on = false;
  }
}

//public functions
void SetupLights(Config cfg){
  for(int i=0; i<NUM_LIGHT_OUTPUTS; i++){
    pinMode(light_output_pins[i], OUTPUT);
    analogWrite(light_output_pins[i], 0); //lights off
  }

  lightConfig = cfg;
}

void UpdateLights(ControlState state){
  for(int i=0; i<NUM_LIGHT_OUTPUTS; i++){
    UpdateLight(state, i);
  }
}

void UpdateLight(ControlState state, int i){
  switch(out_lights[i].type){
    case RIGHT_HEAD:
    case LEFT_HEAD:
      updateHead(state, i);
      break;
    case RIGHT_FRONT_TURN:
      updateRFTurn(state, i);
      break;
    case LEFT_FRONT_TURN:
      updateLFTurn(state, i);
      break;
    case RIGHT_BRAKE:
    case LEFT_BRAKE:
      updateBrake(state, i);
      break;
    case RIGHT_REAR_TURN:
      updateRRTurn(state, i);
      break;
    case LEFT_REAR_TURN:
      updateLRTurn(state, i);
      break;
    case AUX:
      updateAux(state, i);
      break;
  }
}
