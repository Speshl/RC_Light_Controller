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

void calculateLeftTurnAnimation(State* state) {
    if(!state->inputState.leftTurn){
        state->animationState.leftTurnOn = false;
        state->animationState.leftTurnBlinkOn = false;
        state->animationState.leftTurnStartTime = 0;
        return;
    }

    // First time left turn is on
    if(!state->animationState.leftTurnOn){
        state->animationState.leftTurnOn = true;
        state->animationState.leftTurnBlinkOn = true;
        state->animationState.leftTurnStartTime = millis();
        //return;
    }

    // Calculate the time elapsed since the left turn animation started
    unsigned long elapsedTime = millis() - state->animationState.leftTurnStartTime;

    // Alternate the blink on every interval
    if((elapsedTime / TURN_FLASH_INTERVAL) % 2 == 0){
        state->animationState.leftTurnBlinkOn = true;
    } else {
        state->animationState.leftTurnBlinkOn = false;
    }

    return;
}

void calculateRightTurnAnimation(State* state) {
    if(!state->inputState.rightTurn){
        state->animationState.rightTurnOn = false;
        state->animationState.rightTurnBlinkOn = false;
        state->animationState.rightTurnStartTime = 0;
        return;
    }

    // First time left turn is on
    if(!state->animationState.rightTurnOn){
        state->animationState.rightTurnOn = true;
        state->animationState.rightTurnBlinkOn = true;
        state->animationState.rightTurnStartTime = millis();
        //return;
    }

    // Calculate the time elapsed since the left turn animation started
    unsigned long elapsedTime = millis() - state->animationState.rightTurnStartTime;

    // Alternate the blink on every interval
    if((elapsedTime / TURN_FLASH_INTERVAL) % 2 == 0){
        state->animationState.rightTurnBlinkOn = true;
    } else {
        state->animationState.rightTurnBlinkOn = false;
    }

    return;
}

void calculateHazardsAnimation(State* state) {
    if(!state->inputState.hazards){
        state->animationState.hazardsOn = false;
        state->animationState.hazardsBlinkOn = false;
        state->animationState.hazardsStartTime = 0;
        return;
    }

    // First time left turn is on
    if(!state->animationState.hazardsOn){
        state->animationState.hazardsOn = true;
        state->animationState.hazardsBlinkOn = true;
        state->animationState.hazardsStartTime = millis();
        //return;
    }

    // Calculate the time elapsed since the left turn animation started
    unsigned long elapsedTime = millis() - state->animationState.hazardsStartTime;

    // Alternate the blink on every interval
    if((elapsedTime / TURN_FLASH_INTERVAL) % 2 == 0){
        state->animationState.hazardsBlinkOn = true;
    } else {
        state->animationState.hazardsBlinkOn = false;
    }

    return;
}

void calculateStrobesAnimation(State* state){
    unsigned long elapsedTime = millis();
    // Alternate the blink on every interval
    if((elapsedTime / STROBE_FLASH_INTERVAL) % 2 == 0){
        state->animationState.strobe1BlinkOn = true;
        state->animationState.strobe2BlinkOn = false;
    } else {
        state->animationState.strobe1BlinkOn = false;
        state->animationState.strobe2BlinkOn = true;
    }
    return;
}

void calculateUnderglowCycleAnimation(State* state) {
    int brightness = 127.5 * (1.0 + sin(millis() / 2000.0 * PI));

    if(brightness < 2){
        state->animationState.underglowPalletePos ++;
        if(state->animationState.underglowPalletePos >= 255){
            state->animationState.underglowPalletePos = 0;
        }
    }

    state->animationState.underglowCycleColor = ColorFromPalette(RainbowColors_p, state->animationState.underglowPalletePos, brightness, LINEARBLEND);
    return;
}

void startPopFlame(State* state) {
    state->animationState.currentFlameType = POP_FLAME;
    state->animationState.flameStartTime = millis();
    state->animationState.flameIntensity = random(MIN_START_POP_EXHAUST_INTENSITY, MAX_START_POP_EXHAUST_INTENSITY);
    state->animationState.flamePalette = popFlamePalette;
    return;
}

void startBrightFlame(State* state) {
    state->animationState.currentFlameType = BRIGHT_FLAME;
    state->animationState.flameStartTime = millis();
    state->animationState.flameIntensity = random(MIN_START_BRIGHT_EXHAUST_INTENSITY, MAX_START_BRIGHT_EXHAUST_INTENSITY);
    state->animationState.flamePalette = brightFlamePalette;
    return;
}

void startDimFlame(State* state) {
    state->animationState.currentFlameType = DIM_FLAME;
    state->animationState.flameStartTime = millis();
    state->animationState.flameIntensity = random(MIN_START_DIM_EXHAUST_INTENSITY, MAX_START_DIM_EXHAUST_INTENSITY);
    state->animationState.flamePalette = dimFlamePalette;
    return;
}

void updateDimFlame(State* state){
    int changeAmount = random(MIN_CHANGE_DIM_EXHAUST_INTENSITY,MAX_CHANGE_DIM_EXHAUST_INTENSITY);
    int upOrDown = random(100);
    if(upOrDown <= CHANCE_DIM_EXHAUST_INTENSITY_INCREASE) {
        changeAmount = (changeAmount / 2) * -1;
    }

    int newIntensity = state->animationState.flameIntensity - changeAmount;
    if(newIntensity > MAX_EXHAUST_INTENSITY){
        newIntensity = MAX_EXHAUST_INTENSITY;
    }else if(newIntensity < 0){
        newIntensity = 0;
    }

    state->animationState.flameIntensity = newIntensity;
}

void updateBrightFlame(State* state){
    int changeAmount = random(MIN_CHANGE_BRIGHT_EXHAUST_INTENSITY,MAX_CHANGE_BRIGHT_EXHAUST_INTENSITY);
    int upOrDown = random(100);
    if(upOrDown <= CHANCE_BRIGHT_EXHAUST_INTENSITY_INCREASE) {
        changeAmount = (changeAmount / 2) * -1;
    }

    int newIntensity = state->animationState.flameIntensity - changeAmount;
    if(newIntensity > MAX_EXHAUST_INTENSITY){
        newIntensity = MAX_EXHAUST_INTENSITY;
    }else if(newIntensity < 0){
        newIntensity = 0;
    }

    state->animationState.flameIntensity = newIntensity;
}

void updatePopFlame(State* state){
    int changeAmount = random(MIN_CHANGE_POP_EXHAUST_INTENSITY,MAX_CHANGE_POP_EXHAUST_INTENSITY);
    int upOrDown = random(100);
    if(upOrDown <= CHANCE_POP_EXHAUST_INTENSITY_INCREASE) {
        changeAmount = (changeAmount / 2) * -1;
    }

    int newIntensity = state->animationState.flameIntensity - changeAmount;
    if(newIntensity > MAX_EXHAUST_INTENSITY){
        newIntensity = MAX_EXHAUST_INTENSITY;
    }else if(newIntensity < 0){
        newIntensity = 0;
    }

    state->animationState.flameIntensity = newIntensity;
}

void calculateExhaustFlameAnimation(State* state) {
    if(state->inputValues.esc > state->animationState.lastEscValue){
        if(state->animationState.currentFlameType != DIM_FLAME){
            state->animationState.currentFlameType = NO_FLAME;
            return;
        }
    }

    if(state->animationState.currentFlameType != NO_FLAME){

        if(state->animationState.flameIntensity == 0){
            state->animationState.currentFlameType = NO_FLAME;
            state->animationState.flameStartTime = 0;
            state->animationState.flamePalette = CRGBPalette16(CRGB::Black);
            state->animationState.lastMaxEscValue = INPUT_MID;
            return;
        }

        switch(state->animationState.currentFlameType){
            case DIM_FLAME:
                updateDimFlame(state);
                break;
            case BRIGHT_FLAME:
                updateBrightFlame(state);
                break;
            case POP_FLAME:
                updatePopFlame(state);
                break;
        }
    }else{
        if(state->inputValues.esc >= POP_EXHAUST_LEVEL){
            startPopFlame(state);
        }else if(state->animationState.lastFlameType == POP_FLAME){
            startBrightFlame(state);
        }else if(state->inputValues.esc > state->animationState.lastEscValue){
           //no flames on up
        }else if(state->inputValues.esc < state->animationState.lastEscValue){
            if(state->animationState.lastMaxEscValue >= BRIGHT_EXHAUST_LEVEL){
                startBrightFlame(state);
            }else if(state->animationState.lastMaxEscValue >= DIM_EXHAUST_LEVEL){
                startDimFlame(state);
            }
        }
    }

    state->animationState.lastEscValue = state->inputValues.esc;
    return;
}

void calculatePoliceLightAnimation(State* state){
    unsigned long elapsedTime = millis();
    // Alternate the blink on every interval
    if((elapsedTime / TURN_FLASH_INTERVAL) % 2 == 0){
        state->animationState.solidPoliceAlternateColor = true;
    } else {
        state->animationState.solidPoliceAlternateColor = false;
    }


    if(state->animationState.wrapPoliceLightLastChange + STROBE_FLASH_INTERVAL < elapsedTime){
        state->animationState.wrapPoliceStrobePos ++;
        if(state->animationState.wrapPoliceStrobePos > 5){
            state->animationState.wrapPoliceStrobePos = 0;
        }
        state->animationState.wrapPoliceLightLastChange = elapsedTime;
    }

    return;
}

void calculateSingleAnimations(State* state) {
    calculateLeftTurnAnimation(state);
    calculateRightTurnAnimation(state);
    calculateHazardsAnimation(state);
    calculateStrobesAnimation(state);
    return;
}

void calculateStripAnimations(State* state) {
    calculateExhaustFlameAnimation(state);
    calculateUnderglowCycleAnimation(state);
    calculatePoliceLightAnimation(state);
    return;
}


// Public Functions
void CalculateAnimations(State* state) {
    calculateSingleAnimations(state);
    calculateStripAnimations(state);
    return;
}