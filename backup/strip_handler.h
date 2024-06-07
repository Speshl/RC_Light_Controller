#ifndef STRIP_HANDLER_H
#define STRIP_HANDLER_H
#include "Arduino.h"
#include "config.h"

enum FlameAnimation {
  NONE,
  BRIGHT,
  DIM,
  POP
};

void SetupStrips(Config cfg);
void UpdateStrips(ControlState state);
void UpdateStrip(ControlState state, int i);
void ShowUpdates();

struct Strip {
  int numLeds;
  StripType stripType;
  DriftLightType driftLightType;
  CRGB color;
};

struct ExhaustAnimation {
  int intensity;
  FlameAnimation animation;
  FlameAnimation lastAnimation;
  CRGBPalette16 palette;
};

#endif