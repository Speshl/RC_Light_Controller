#include "animation.h"

void startPopFlame(FlameState* flame) {
    flame->lastType = flame->type;
    flame->type = POP_FLAME;
    flame->startTime = millis();
    flame->intensity = random(MIN_START_POP_EXHAUST_INTENSITY, MAX_START_POP_EXHAUST_INTENSITY);
    return;
}

void startBrightFlame(FlameState* flame) {
    flame->lastType = flame->type;
    flame->type = BRIGHT_FLAME;
    flame->startTime = millis();
    flame->intensity = random(MIN_START_BRIGHT_EXHAUST_INTENSITY, MAX_START_BRIGHT_EXHAUST_INTENSITY);
    return;
}

void startDimFlame(FlameState* flame) {
    flame->lastType = flame->type;
    flame->type = DIM_FLAME;
    flame->startTime = millis();
    flame->intensity = random(MIN_START_DIM_EXHAUST_INTENSITY, MAX_START_DIM_EXHAUST_INTENSITY);
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