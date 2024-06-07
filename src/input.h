#ifndef INPUT_H
#define INPUT_H
#include "config.h"
#include <CrsfSerial.h>

void SetupInput(Config* config);

InputValues GetLatestInput();

void PrintInput(InputValues input);

#endif