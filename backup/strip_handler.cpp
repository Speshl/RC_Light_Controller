#include "strip_handler.h"

CRGB led_strips[NUM_STRIPS][NUM_STRIP_LEDS];
uint8_t strip_output_pins[NUM_STRIPS] = {STRIP_OUT_1, STRIP_OUT_2};

//Strip strips[NUM_STRIPS];

int lastEscValues[NUM_EXHAUST_HISTORY];
int lastMaxEscValue;

ExhaustAnimation flames[NUM_STRIPS];

Config stripConfig;

DEFINE_GRADIENT_PALETTE( dimFlamePalette ) {
  0,    0, 0, 0,        // Black
  150,   127, 38, 0,    // dark Orange
  200,   127, 75, 0,    // Orange
  230,  127, 127, 127,  // White
  240,  75, 75, 125,       // light Blue
  255,  35, 35, 125       // light Blue
};

DEFINE_GRADIENT_PALETTE( brightFlamePalette ) {
  0,    0, 0, 0,        // Black
  150,   255, 77, 0,    // dark Orange
  200,   255, 150, 0,    // Orange
  230,  255, 255, 255,  // White
  240,  150, 150, 255,       // light Blue
  255,  75, 75, 255       // light Blue
};

DEFINE_GRADIENT_PALETTE( simpleFlamePalette ) {
  0,    0, 0, 0,        // 
  70,   60, 20, 5,    //  
  140,   100, 50, 10,    //  
  200,   200, 100, 15,    // 
  235,   255, 150, 25,    // 
  255,   255, 150, 50,    
};

//private functions
void updateUnderglow(ControlState state, int i){
  if(!state.systemEnabled || !state.underglow || !ENABLE_UNDERGLOW){
    for(int j=0; j<stripConfig.stripCfgs[i].numLeds; j++){
      led_strips[i][j] = CRGB(0,0,0);
    }
    return;
  }


  for(int j=0; j<stripConfig.stripCfgs[i].numLeds; j++){
    led_strips[i][j] = stripConfig.stripCfgs[i].color;
  }
}

void updateDriftLightMiddleOut (ControlState state, int i){

  if(!state.systemEnabled || !state.driftLights || !ENABLE_DRIFT_LIGHT){
    for(int j=0; j<stripConfig.stripCfgs[i].numLeds; j++){
      led_strips[i][j] = CRGB(0,0,0);
    }
    return;
  }

  int valuePerLed = (CRSF_HIGH-CRSF_MID) / (stripConfig.stripCfgs[i].numLeds / 2);
  int absValue = abs(state.esc-CRSF_MID);

  int numFullLitLeds = absValue / valuePerLed; //Number of fully lit leds
  int partialBrightness = absValue % valuePerLed; //brightness of the partially lit led

  // Serial.print("idx: ");
  // Serial.print(i);
  // Serial.print(" numLeds: ");
  // Serial.print(strips[i].numLeds);
  // Serial.print(" ESC: ");
  // Serial.print( absValue);
  // Serial.print(" ValuePerLed: ");
  // Serial.print(valuePerLed);
  // Serial.print(" NumFull: ");
  // Serial.print( numFullLitLeds);
  // Serial.print(" Partial: ");
  // Serial.println(partialBrightness);

  for(int j=0; j<stripConfig.stripCfgs[i].numLeds/2; j++){
    int leftJ = (stripConfig.stripCfgs[i].numLeds/2) - j-1;
    int rightJ = (stripConfig.stripCfgs[i].numLeds/2) + j;

    if(state.esc < CRSF_MID){
      if(j < numFullLitLeds){ //
        led_strips[i][leftJ] = CRGB(255,0,0);
        led_strips[i][rightJ] = CRGB(255,0,0);
      }else if(j == numFullLitLeds){
        float percentBrightness = ((float)partialBrightness / (float)valuePerLed);
        led_strips[i][leftJ] = CRGB(255*percentBrightness,0,0);
        led_strips[i][rightJ] = CRGB(255*percentBrightness,0,0);
      }else{
        led_strips[i][leftJ] = CRGB(0,0,0);
        led_strips[i][rightJ] = CRGB(0,0,0);
      }
    }else{//setting to green
      if(j < numFullLitLeds){ //this and it match should be full green
        led_strips[i][leftJ] = CRGB(0,255,0);
        led_strips[i][rightJ] = CRGB(0,255,0);
      }else if(j == numFullLitLeds){
        float percentBrightness = ((float)partialBrightness / (float)valuePerLed);
        led_strips[i][leftJ] = CRGB(0,255*percentBrightness,0);
        led_strips[i][rightJ] = CRGB(0,255*percentBrightness,0);
      }else{
        led_strips[i][leftJ] = CRGB(0,0,0);
        led_strips[i][rightJ] = CRGB(0,0,0);
      }
    }
  }
}

void updateDriftLightFrontToBack(ControlState state, int i){
  if(!state.systemEnabled || !state.driftLights || !ENABLE_DRIFT_LIGHT){
    for(int j=0; j<stripConfig.stripCfgs[i].numLeds; j++){
      led_strips[i][j] = CRGB(0,0,0);
    }
    return;
  }

  int valuePerLed = (CRSF_HIGH-CRSF_MID) / (stripConfig.stripCfgs[i].numLeds);
  int absValue = abs(state.esc-CRSF_MID);

  int numFullLitLeds = absValue / valuePerLed; //Number of fully lit leds
  int partialBrightness = absValue % valuePerLed; //brightness of the partially lit led
  for(int j=0; j<stripConfig.stripCfgs[i].numLeds; j++){
    if(state.esc < CRSF_MID){ //brakes
      if(j < numFullLitLeds){ //fully lit
        led_strips[i][j] = CRGB(255,0,0);
      }else if(j == numFullLitLeds){//partially lit
        float percentBrightness = ((float)partialBrightness / (float)valuePerLed);
        led_strips[i][j] = CRGB(255*percentBrightness,0,0);
      }else{ //off
        led_strips[i][j] = CRGB(0,0,0);
      }
    }else{
      if(j < numFullLitLeds){ //fully lit
        led_strips[i][j] = CRGB(0,255,0);
      }else if(j == numFullLitLeds){//partially lit
        float percentBrightness = ((float)partialBrightness / (float)valuePerLed);
        led_strips[i][j] = CRGB(0,255*percentBrightness,0);
      }else{ //off
        led_strips[i][j] = CRGB(0,0,0);
      }
    }
  }
}

void updateDriftLightBackToFront(ControlState state, int i){
  updateDriftLightFrontToBack(state, i);
  //invert led array
  int startPos = 0;
  int endPos = stripConfig.stripCfgs[i].numLeds - 1;
  CRGB tempVal;
  while(startPos > endPos){
    tempVal = led_strips[i][endPos];
    led_strips[i][endPos] = led_strips[i][startPos];
    led_strips[i][startPos] = tempVal;
    startPos++;
    endPos--;
  }
}

void stopFlame(int i){
  Serial.println("flame stopped");
  flames[i].intensity = 0;
  flames[i].lastAnimation = flames[i].animation;
  flames[i].animation = NONE;
  for(int j=0; j<stripConfig.stripCfgs[i].numLeds; j++){
    led_strips[i][j] = CRGB(0,0,0);
  }
}

void applyFlameToStrip(int i){
  if(flames[i].intensity == 0){
    return stopFlame(i);
  }

  uint8_t mappedIntensity = map(flames[i].intensity,0,MAX_EXHAUST_INTENSITY,0,255);
  //CRGB flameColor = HeatColor(mappedIntensity);
  CRGB flameColor = ColorFromPalette(flames[i].palette, mappedIntensity);
  for(int j=0; j<stripConfig.stripCfgs[i].numLeds; j++){
    led_strips[i][j] = flameColor;
  }

  // Serial.print("intensity: ");
  // Serial.print(flames[i].intensity);
  // Serial.print(" mapped: ");
  // Serial.print(mappedIntensity);
  // Serial.print(" red: ");
  // Serial.print(flameColor.r);
  // Serial.print(" green: ");
  // Serial.print(flameColor.g);
  // Serial.print(" blue: ");
  // Serial.println(flameColor.b);
}

void updatePopFlame(int i){
  int changeAmount = random(MIN_CHANGE_POP_EXHAUST_INTENSITY,MAX_CHANGE_POP_EXHAUST_INTENSITY);
  int upOrDown = random(100);
  if(upOrDown <= CHANCE_POP_EXHAUST_INTENSITY_INCREASE) {
    changeAmount = (changeAmount / 2) * -1;
  }

  int newIntensity = flames[i].intensity - changeAmount;
  if(newIntensity > MAX_EXHAUST_INTENSITY){
    newIntensity = MAX_EXHAUST_INTENSITY;
  }else if(newIntensity < 0){
    newIntensity = 0;
  }

  flames[i].intensity = newIntensity;

  applyFlameToStrip(i);
}

void updateBrightFlame(int i){
  int changeAmount = random(MIN_CHANGE_BRIGHT_EXHAUST_INTENSITY,MAX_CHANGE_BRIGHT_EXHAUST_INTENSITY);
  int upOrDown = random(100);
  if(upOrDown <= CHANCE_BRIGHT_EXHAUST_INTENSITY_INCREASE) {
    changeAmount = (changeAmount / 2) * -1;
  }

  int newIntensity = flames[i].intensity - changeAmount;
  if(newIntensity > MAX_EXHAUST_INTENSITY){
    newIntensity = MAX_EXHAUST_INTENSITY;
  }else if(newIntensity < 0){
    newIntensity = 0;
  }

  flames[i].intensity = newIntensity;

  applyFlameToStrip(i);
}

void updateDimFlame(int i){
  int changeAmount = random(MIN_CHANGE_DIM_EXHAUST_INTENSITY,MAX_CHANGE_DIM_EXHAUST_INTENSITY);
  int upOrDown = random(100);
  if(upOrDown <= CHANCE_DIM_EXHAUST_INTENSITY_INCREASE) {
    changeAmount = (changeAmount / 2) * -1;
  }

  int newIntensity = flames[i].intensity - changeAmount;
  if(newIntensity > MAX_EXHAUST_INTENSITY){
    newIntensity = MAX_EXHAUST_INTENSITY;
  }else if(newIntensity < 0){
    newIntensity = 0;
  }

  flames[i].intensity = newIntensity;

  applyFlameToStrip(i);
}

void startPopFlame(int i){
  flames[i].animation = POP;
  flames[i].palette = simpleFlamePalette;
  flames[i].intensity = random(MIN_START_POP_EXHAUST_INTENSITY, MAX_START_POP_EXHAUST_INTENSITY);
  applyFlameToStrip(i);
}

void startBrightFlame(int i){
  flames[i].animation = BRIGHT;
  flames[i].palette = brightFlamePalette;
  flames[i].intensity = random(MIN_START_BRIGHT_EXHAUST_INTENSITY, MAX_START_BRIGHT_EXHAUST_INTENSITY);
  applyFlameToStrip(i);
}

void startDimFlame(int i){
  flames[i].animation = DIM;
  flames[i].palette = dimFlamePalette;
  flames[i].intensity = random(MIN_START_DIM_EXHAUST_INTENSITY, MAX_START_DIM_EXHAUST_INTENSITY);
  applyFlameToStrip(i);
}

void updateFlame(int i){
  switch(flames[i].animation){
    case POP:
      updatePopFlame(i);
      break;
    case BRIGHT:
      updateBrightFlame(i);
      break;
    case DIM:
      updateDimFlame(i);
      break;
  }
}

void updateExhaust(ControlState state, int i){
  if(!state.systemEnabled || !state.exhaust || !ENABLE_EXHAUST){
    for(int j=0; j<stripConfig.stripCfgs[i].numLeds; j++){
      led_strips[i][j] = CRGB(0,0,0);
    }
    return;
  }

  if(state.esc > lastEscValues[0]){ //esc going up
    if(flames[i].animation != POP){ //stop all flames except pop flames
      stopFlame(i);
    }
    lastMaxEscValue = state.esc;
  }
  
  if(flames[i].animation != NONE){ //showing a flame so update it
      updateFlame(i);
  }else{ //Not showing a flame, so check if we should be

    if(state.esc >= POP_EXHAUST_LEVEL){ //trigger flames related to esc threshold
      startPopFlame(i);
    }else if(flames[i].lastAnimation == POP){
      startBrightFlame(i);  //bright flame follows last pop flame
    }else if(state.esc > lastEscValues[0]){ //trigger flames related to esc going up
      //unused
    }else if(state.esc < lastEscValues[0]){ //trigger flames related to esc going down
      if(lastMaxEscValue >= BRIGHT_EXHAUST_LEVEL){
         startBrightFlame(i);
      }else if(lastMaxEscValue >= DIM_EXHAUST_LEVEL){
        startDimFlame(i);
      }
    }
  }

  //Shift last esc values
  for(int i=NUM_EXHAUST_HISTORY-1; i>0; i--){
    lastEscValues[i] = lastEscValues[i-1];
  }
  lastEscValues[0] = state.esc;

}

// void loadDefaultStrips(){
//   //69 Comaro 
//   // strips[0].numLeds = 12;
//   // strips[0].stripType = EXHAUST;

//   //strips[0].numLeds = 16;
//   // strips[0].stripType = DRIFT_LIGHT;
//   // strips[0].driftLightType = MIDDLE_OUT;

//   // strips[2].numLeds = 12;
//   // strips[2].stripType = EXHAUST;

//   //BMW M3
//   strips[0].numLeds = 13;
//   strips[0].stripType = DRIFT_LIGHT;
//   strips[0].driftLightType = MIDDLE_OUT;

//   strips[1].numLeds = 12;
//   strips[1].stripType = EXHAUST;

//   strips[2].numLeds = NUM_STRIP_LEDS;
//   strips[2].stripType = UNDERGLOW;
//   strips[2].color = CRGB::Green;


// }


//public functions
void SetupStrips(Config cfg){
  stripConfig = cfg;

  FastLED.addLeds<CHIPSET,STRIP_OUT_1,COLOR_ORDER>(led_strips[0],NUM_STRIP_LEDS);
  FastLED.addLeds<CHIPSET,STRIP_OUT_2,COLOR_ORDER>(led_strips[1],NUM_STRIP_LEDS);
  FastLED.addLeds<CHIPSET,STRIP_OUT_3,COLOR_ORDER>(led_strips[2],NUM_STRIP_LEDS);

  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_AMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void UpdateStrips(ControlState state){
  for(int i=0; i<NUM_STRIPS; i++){
    UpdateStrip(state, i);
  }
  ShowUpdates();
}

void ShowUpdates(){
  FastLED.show();
}

void UpdateStrip(ControlState state, int i){
  switch(stripConfig.stripCfgs[i].stripType){
    case DRIFT_LIGHT:
      switch(stripConfig.stripCfgs[i].driftLightType){
        case MIDDLE_OUT:
          updateDriftLightMiddleOut(state,i);
          break;
        case FRONT_TO_BACK:
          updateDriftLightFrontToBack(state,i);
          break;
        case BACK_TO_FRONT:
          updateDriftLightFrontToBack(state,i);
          break;
      }
      break;
    case UNDERGLOW:
      updateUnderglow(state, i);
      break;
    case EXHAUST:
      updateExhaust(state, i);
      break;
  }
}