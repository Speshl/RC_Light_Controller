#include "animation.h"

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

DEFINE_GRADIENT_PALETTE( popFlamePalette ) {
  0,    0, 0, 0,        // 
  70,   60, 20, 5,    //  
  140,   100, 50, 10,    //  
  200,   200, 100, 15,    // 
  235,   255, 150, 25,    // 
  255,   255, 150, 50,    
};


// Private Functions
void calculateBlinkRoleAnimation(BlinkState* light, bool on) {
    if(!on){
        light->on = false;
        light->blinkOn = false;
        light->startTime = 0;
        return;
    }

    if(!light->on){
        light->on = true;
        light->blinkOn = true;
        light->startTime = millis();
    }

    unsigned long elapsedTime = millis() - light->startTime;
    if((elapsedTime / TURN_FLASH_INTERVAL) % 2 == 0){
        light->blinkOn = true;
    } else {
        light->blinkOn = false;
    }
}

void calculateStrobesAnimation(State* state){
    // Alternate the blink on every interval
    if((millis() / STROBE_FLASH_INTERVAL) % 2 == 0){
        state->animationState.roleStates.strobe1.blinkOn = true;
        state->animationState.roleStates.strobe2.blinkOn = false;
    } else {
        state->animationState.roleStates.strobe1.blinkOn = false;
        state->animationState.roleStates.strobe2.blinkOn = true;
    }
    return;
}

void calculateUnderglowCycleAnimation(UnderglowState* glow) {
    int brightness = 127.5 * (1.0 + sin(millis() / 2000.0 * PI));

    if(brightness < 2){
        glow->palettePos ++;
        if(glow->palettePos >= 255){
            glow->palettePos = 0;
        }
    }

    glow->color = ColorFromPalette(RainbowColors_p, glow->palettePos, brightness, LINEARBLEND);
    return;
}

void startPopFlame(FlameState* flame) {
    flame->lastType = flame->type;
    flame->type = POP_FLAME;
    flame->startTime = millis();
    flame->intensity = random(MIN_START_POP_EXHAUST_INTENSITY, MAX_START_POP_EXHAUST_INTENSITY);
    flame->palette = popFlamePalette;
    return;
}

void startBrightFlame(FlameState* flame) {
    flame->lastType = flame->type;
    flame->type = BRIGHT_FLAME;
    flame->startTime = millis();
    flame->intensity = random(MIN_START_BRIGHT_EXHAUST_INTENSITY, MAX_START_BRIGHT_EXHAUST_INTENSITY);
    flame->palette = brightFlamePalette;
    return;
}

void startDimFlame(FlameState* flame) {
    flame->lastType = flame->type;
    flame->type = DIM_FLAME;
    flame->startTime = millis();
    flame->intensity = random(MIN_START_DIM_EXHAUST_INTENSITY, MAX_START_DIM_EXHAUST_INTENSITY);
    flame->palette = dimFlamePalette;
    return;
}

void updateDimFlame(FlameState* flame){
    int changeAmount = random(MIN_CHANGE_DIM_EXHAUST_INTENSITY,MAX_CHANGE_DIM_EXHAUST_INTENSITY);
    int upOrDown = random(100);
    if(upOrDown <= CHANCE_DIM_EXHAUST_INTENSITY_INCREASE) {
        changeAmount = (changeAmount / 2) * -1;
    }

    int newIntensity = flame->intensity - changeAmount;
    if(newIntensity > MAX_EXHAUST_INTENSITY){
        newIntensity = MAX_EXHAUST_INTENSITY;
    }else if(newIntensity < 0){
        newIntensity = 0;
    }

    flame->intensity = newIntensity;
}

void updateBrightFlame(FlameState* flame){
    int changeAmount = random(MIN_CHANGE_BRIGHT_EXHAUST_INTENSITY,MAX_CHANGE_BRIGHT_EXHAUST_INTENSITY);
    int upOrDown = random(100);
    if(upOrDown <= CHANCE_BRIGHT_EXHAUST_INTENSITY_INCREASE) {
        changeAmount = (changeAmount / 2) * -1;
    }

    int newIntensity = flame->intensity - changeAmount;
    if(newIntensity > MAX_EXHAUST_INTENSITY){
        newIntensity = MAX_EXHAUST_INTENSITY;
    }else if(newIntensity < 0){
        newIntensity = 0;
    }

    flame->intensity = newIntensity;
}

void updatePopFlame(FlameState* flame){
    int changeAmount = random(MIN_CHANGE_POP_EXHAUST_INTENSITY,MAX_CHANGE_POP_EXHAUST_INTENSITY);
    int upOrDown = random(100);
    if(upOrDown <= CHANCE_POP_EXHAUST_INTENSITY_INCREASE) {
        changeAmount = (changeAmount / 2) * -1;
    }

    int newIntensity = flame->intensity - changeAmount;
    if(newIntensity > MAX_EXHAUST_INTENSITY){
        newIntensity = MAX_EXHAUST_INTENSITY;
    }else if(newIntensity < 0){
        newIntensity = 0;
    }

    flame->intensity = newIntensity;
}

void calculateExhaustFlameAnimation(State* state) {
    if(state->inputValues.esc > state->animationState.flame.lastEscValue){
        //Serial.print("ESC Value: ");
        //Serial.print(state->inputValues.esc);
        //Serial.print(" > Last ESC Value: ");
        //Serial.println(state->animationState.lastEscValue);
        state->animationState.flame.lastType = state->animationState.flame.type;
        state->animationState.flame.type = NO_FLAME;
        //Serial.println("No flame on up");
        state->animationState.flame.lastEscValue = state->inputValues.esc;
        return;
    }

    if(state->animationState.flame.lastType == POP_FLAME && state->animationState.flame.intensity == 0){ //pop flame ending triggers a new flame
        if(state->inputValues.esc >= POP_EXHAUST_LEVEL){
            //Serial.println("Start pop flame again");
            startPopFlame(&state->animationState.flame);
        }else{
            //Serial.println("Start bright flame after pop flame");
            startBrightFlame(&state->animationState.flame);
        }
        state->animationState.flame.lastEscValue = state->inputValues.esc;
        return;
    }

    if(state->animationState.flame.type != NO_FLAME){ //a flame is active, update or end it
        if(state->animationState.flame.intensity == 0){ //end flame
            state->animationState.flame.lastType = state->animationState.flame.type;
            state->animationState.flame.type = NO_FLAME;
            state->animationState.flame.startTime = 0;
            state->animationState.flame.palette = CRGBPalette16(CRGB::Black);
            state->animationState.flame.lastMaxEscValue = INPUT_MID;
            state->animationState.flame.lastEscValue = state->inputValues.esc;
            //Serial.println("No flame on intensity 0");
            return;
        }

        switch(state->animationState.flame.type){ //update proper flame type
            case DIM_FLAME:
                //Serial.println("Updating dim flame");
                updateDimFlame(&state->animationState.flame);
                break;
            case BRIGHT_FLAME:
                //Serial.println("Updating bright flame");
                updateBrightFlame(&state->animationState.flame);
                break;
            case POP_FLAME:
                //Serial.println("Updating pop flame");
                updatePopFlame(&state->animationState.flame);
                break;
            default:
                Serial.println("No flame type found");
                break;
        }
    }else{ //check if a new flame should start
        if(state->inputValues.esc >= POP_EXHAUST_LEVEL){
            //Serial.println("Starting pop flame");
            startPopFlame(&state->animationState.flame);
        }else if(state->animationState.flame.lastEscValue >= BRIGHT_EXHAUST_LEVEL && state->inputValues.esc < state->animationState.flame.lastEscValue){
            //Serial.println("Starting bright flame");
            startBrightFlame(&state->animationState.flame);
        }else if(state->animationState.flame.lastEscValue >= DIM_EXHAUST_LEVEL && state->inputValues.esc < state->animationState.flame.lastEscValue){
            //Serial.println("Starting dim flame");
            startDimFlame(&state->animationState.flame);
        }
    }

    state->animationState.flame.lastEscValue = state->inputValues.esc;
    return;
}

void calculateEmergencyLightAnimation(EmergencyState* emergency){
    unsigned long elapsedTime = millis();
    // Alternate the blink on every interval
    if((elapsedTime / TURN_FLASH_INTERVAL) % 2 == 0){
        emergency->solidAlternateColor = true;
    } else {
        emergency->solidAlternateColor = false;
    }


    if(emergency->lastStrobeChange + STROBE_FLASH_INTERVAL < elapsedTime){
        emergency->strobePos ++;
        if(emergency->strobePos > 5){
            emergency->strobePos = 0;
        }
        emergency->lastStrobeChange = elapsedTime;
    }

    return;
}

void calculateSingleAnimations(State* state) {
    calculateBlinkRoleAnimation(&state->animationState.roleStates.leftTurn, state->inputState.leftTurn);
    calculateBlinkRoleAnimation(&state->animationState.roleStates.rightTurn, state->inputState.rightTurn);
    calculateBlinkRoleAnimation(&state->animationState.roleStates.hazards, state->inputState.hazards);
    calculateStrobesAnimation(state);
    return;
}

void calculateStripAnimations(State* state) {
    calculateExhaustFlameAnimation(state);
    calculateUnderglowCycleAnimation(&state->animationState.underglow);
    calculateEmergencyLightAnimation(&state->animationState.emergency);
    return;
}


// Public Functions
void CalculateAnimations(State* state) {
    calculateSingleAnimations(state);
    calculateStripAnimations(state);
    return;
}