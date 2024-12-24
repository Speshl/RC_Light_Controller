#ifndef OUTPUT_H
#define OUTPUT_H
#include "../config/config.h"


void SetupOutput(Config cfg);

void ShowState(State* state);

void showRole(State* state, int channel);
void showUnderglow(State* state, int channel);
void showThrottleBrakeLight(State* state, int channel);
void showExhaustFlame(State* state, int channel);
void showEmergencyLights(State* state, int channel);

void clearStrip(int channel);
CRGB reorderColor(CRGB color, EOrder order);
void setLedColor(int channel, int led, CRGB color);

#endif