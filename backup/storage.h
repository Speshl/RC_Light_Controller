#ifndef STORAGE_H
#define STORAGE_H
#include <Preferences.h>
#include "config.h"

void SetupStorage();

Config CreateOrLoadCfg(Preferences* preferences);

void SaveConfig(Preferences* preferences, Config config);

Config LoadConfig(Preferences* preferences);

#endif