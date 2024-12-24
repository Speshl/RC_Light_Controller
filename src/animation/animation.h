#ifndef ANIMATION_H
#define ANIMATION_H
#include "../config/config.h"

void calculateExhaustFlameAnimation(State* state);
void calculateUnderglowPaletteAnimation(UnderglowState* glow);
void calculateUnderglowBreatheAnimation(UnderglowState* glow);
void calculateEmergencyLightAnimation(EmergencyState* emergency);
void calculateBlinkRoleAnimation(BlinkState* blinkState, bool inputState);
void calculateStrobesAnimation(State* state);

void CalculateAnimations(State* state);

#endif