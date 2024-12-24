#include "animation.h"

void calculateRoleAnimations(State* state) {
    calculateBlinkRoleAnimation(&state->animationState.roleStates.leftTurn, state->inputState.leftTurn);
    calculateBlinkRoleAnimation(&state->animationState.roleStates.rightTurn, state->inputState.rightTurn);
    calculateBlinkRoleAnimation(&state->animationState.roleStates.hazards, state->inputState.hazards);
    calculateStrobesAnimation(state);
    return;
}

void calculateStripAnimations(State* state) {
    calculateExhaustFlameAnimation(state);
    calculateUnderglowPaletteAnimation(&state->animationState.underglow);
    calculateUnderglowBreatheAnimation(&state->animationState.underglow);
    calculateEmergencyLightAnimation(&state->animationState.emergency);
    return;
}


// Public Functions
void CalculateAnimations(State* state) {
    // TODO: only calculate animations in use
    calculateRoleAnimations(state);
    calculateStripAnimations(state);
    return;
}