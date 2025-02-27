#ifndef INPUT_H
#define INPUT_H
#include "../config/config.h"
#include <CrsfSerial.h>
#include "sbus.h"

void SetupInput(Config* config);

InputValues GetLatestInput();

void PrintInput(InputValues input);

#endif