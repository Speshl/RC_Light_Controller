#ifndef LIGHT_HANDLER_H
#define LIGHT_HANDLER_H
#include "Arduino.h"
#include "config.h"


struct Light {
  LightType type;
  bool on;
};


void SetupLights(Config config);
void LoadDefaultFlags();

void UpdateLights(ControlState state);
void UpdateLight(ControlState state, int i);


#endif