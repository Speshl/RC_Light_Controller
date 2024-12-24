#include "animation.h"

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