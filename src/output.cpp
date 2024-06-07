#include "output.h"

CRGB led_strips[MAX_CHANNELS][NUM_STRIP_LEDS];

// Private functions

void clearStrip(int channel){
    for(int i = 0; i < NUM_STRIP_LEDS; i++){
        led_strips[channel][i] = CRGB::Black;
    }
}

CRGB reorderColor(CRGB color, EOrder order){
    CRGB newColor = CRGB::Black;
    switch(order){
        case RGB:
            newColor = CRGB(color.r, color.g, color.b);
            break;
        case RBG:
            newColor = CRGB(color.r, color.b, color.g);
            break;
        case GRB:
            newColor = CRGB(color.g, color.r, color.b);
            break;
        case GBR:
            newColor = CRGB(color.g, color.b, color.r);
            break;
        case BRG:
            newColor = CRGB(color.b, color.r, color.g);
            break;
        case BGR:
            newColor = CRGB(color.b, color.g, color.r);
            break;
        default:
            newColor = CRGB::Black;
            Serial.print("Invalid color order: ");
            Serial.println(order);
            break;
    }
    return newColor;
}

//The order in which roles are handled is important. Higher priority roles should be handled first, and lower priority roles should be handled last.
void showSingleLED(State* state, int channel){

    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    if(!state->inputState.enabled){
        analogWrite(channelCfg.pin, 0);
        return;
    }

    if(channelCfg.roles.hazard && levelCfg.roles.hazard && state->inputState.hazards){
        if(state->animationState.hazardsBlinkOn){
            analogWrite(channelCfg.pin, 255);
        }else{
            analogWrite(channelCfg.pin, 0);
        }
        return;
    }

    if(channelCfg.roles.brake && levelCfg.roles.brake && state->inputState.brakes){
        analogWrite(channelCfg.pin, 255);
        return;
    }

    if(channelCfg.roles.leftTurn && levelCfg.roles.leftTurn && state->inputState.leftTurn){
        if(state->animationState.leftTurnBlinkOn){
            analogWrite(channelCfg.pin, 255);
        }else{
            analogWrite(channelCfg.pin, 0);
        }
        return;
    }

    if(channelCfg.roles.rightTurn && levelCfg.roles.rightTurn && state->inputState.rightTurn){
        if(state->animationState.rightTurnBlinkOn){
            analogWrite(channelCfg.pin, 255);
        }else{
            analogWrite(channelCfg.pin, 0);
        }
        return;
    }

    if(channelCfg.roles.strobe1 && levelCfg.roles.strobe1 && state->animationState.strobe1BlinkOn){
        analogWrite(channelCfg.pin, 255);
        return;
    }

    if(channelCfg.roles.strobe2 && levelCfg.roles.strobe2 && state->animationState.strobe2BlinkOn){
        analogWrite(channelCfg.pin, 255);
        return;
    }

    if((channelCfg.roles.strobe1 && levelCfg.roles.strobe1) || (channelCfg.roles.strobe2 && levelCfg.roles.strobe2)){
        analogWrite(channelCfg.pin, 0); //override lower priority roles since this is a strobe, and our level has enabled strobes. Force off when lower priority roles might have kept it on.
        return;
    }

    if(channelCfg.roles.head && levelCfg.roles.head){
        analogWrite(channelCfg.pin, 255);
        return;
    }

    if(channelCfg.roles.tail && levelCfg.roles.tail){
        analogWrite(channelCfg.pin, 100); // low power for tail lights
        return;
    }

    //Not supported yet if ever
    // if(channelCfg.roles.reverse && levelCfg.roles.reverse){
    //     analogWrite(channelCfg.pin, 255);
    //     return;
    // }
    
    if(channelCfg.roles.running && levelCfg.roles.running){
        analogWrite(channelCfg.pin, 100); // low power for running lights
        return;
    }

    if(channelCfg.roles.aux1 && levelCfg.roles.aux1){
        analogWrite(channelCfg.pin, 255);
        return;
    }

    if(channelCfg.roles.aux2 && levelCfg.roles.aux2){
        analogWrite(channelCfg.pin, 255);
        return;
    }

    analogWrite(channelCfg.pin, 0); //turn off if nothing else matches
    return;
}

void showUnderglowSolid(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    if(!state->inputState.enabled || !levelCfg.animations.underglow){
        clearStrip(channel);
        return;
    }

    // Serial.print("UnderGlowSolid Channel: ");
    // Serial.println(channel);
    for(int i=0;i<NUM_STRIP_LEDS;i++){
        led_strips[channel][i] = reorderColor(channelCfg.color, channelCfg.colorOrder);
    }
}

void showUnderglowBreathe(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    if(!state->inputState.enabled || !levelCfg.animations.underglow){
        clearStrip(channel);
        return;
    }

    int brightness = 127.5 * (1.0 + sin(millis() / 2000.0 * PI));
    for(int i=0;i<NUM_STRIP_LEDS;i++){
        led_strips[channel][i] = reorderColor(channelCfg.color.scale8(brightness), channelCfg.colorOrder);
    }
}

void showUnderglowCycle(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    if(!state->inputState.enabled || !levelCfg.animations.underglow){
        clearStrip(channel);
        return;
    }

    for(int i=0;i<NUM_STRIP_LEDS;i++){
        led_strips[channel][i] = reorderColor(state->animationState.underglowCycleColor, channelCfg.colorOrder);
    }
}

void showThrottleBrakeLightBottom(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    if(!state->inputState.enabled || !levelCfg.animations.throttleBrakeLight){
        clearStrip(channel);
        return;
    }

    int valuePerLed = (INPUT_HIGH - INPUT_MID) / channelCfg.stripLedCount;
    int absValue = abs(state->inputValues.esc - INPUT_MID);
    int numFullLeds = absValue / valuePerLed;
    int partialBrightness = absValue % valuePerLed;

    for(int i=0; i<channelCfg.stripLedCount; i++){
        if(state->inputValues.esc < INPUT_MID){
            if(i < numFullLeds){
                led_strips[channel][i] = reorderColor(CRGB(255,0,0), channelCfg.colorOrder);
            }else if(i == numFullLeds){
                float percentBrightness = ((float)partialBrightness / (float)valuePerLed);
                led_strips[channel][i] = reorderColor(CRGB(255*percentBrightness,0,0), channelCfg.colorOrder);
            }else{
                led_strips[channel][i] = CRGB::Black;
            }
        }else{
            if(i < numFullLeds){
                led_strips[channel][i] = reorderColor(CRGB(0,255,0), channelCfg.colorOrder);
            }else if(i == numFullLeds){
                float percentBrightness = ((float)partialBrightness / (float)valuePerLed);
                led_strips[channel][i] = reorderColor(CRGB(0,255*percentBrightness,0), channelCfg.colorOrder);
            }else{
                led_strips[channel][i] = CRGB::Black;
            }
        }
    }
}

void showThrottleBrakeLightTop(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    if(!state->inputState.enabled || !levelCfg.animations.throttleBrakeLight){
        clearStrip(channel);
        return;
    }

    int valuePerLed = (INPUT_HIGH - INPUT_MID) / channelCfg.stripLedCount;
    int absValue = abs(state->inputValues.esc - INPUT_MID);
    int numFullLeds = absValue / valuePerLed;
    int partialBrightness = absValue % valuePerLed;

    for(int i=0; i<channelCfg.stripLedCount; i++){
        if(state->inputValues.esc < INPUT_MID){
            if(i < numFullLeds){
                led_strips[channel][(channelCfg.stripLedCount-1)-i] = reorderColor(CRGB(255,0,0), channelCfg.colorOrder);
            }else if(i == numFullLeds){
                float percentBrightness = ((float)partialBrightness / (float)valuePerLed);
                led_strips[channel][(channelCfg.stripLedCount-1)-i] = reorderColor(CRGB(255*percentBrightness,0,0), channelCfg.colorOrder);
            }else{
                led_strips[channel][(channelCfg.stripLedCount-1)-i] = CRGB::Black;
            }
        }else{
            if(i < numFullLeds){
                led_strips[channel][(channelCfg.stripLedCount-1)-i] = reorderColor(CRGB(0,255,0), channelCfg.colorOrder);
            }else if(i == numFullLeds){
                float percentBrightness = ((float)partialBrightness / (float)valuePerLed);
                led_strips[channel][(channelCfg.stripLedCount-1)-i] = reorderColor(CRGB(0,255*percentBrightness,0), channelCfg.colorOrder);
            }else{
                led_strips[channel][(channelCfg.stripLedCount-1)-i] = CRGB::Black;
            }
        }
    }
}

void showThrottleBrakeLightMid(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    if(!state->inputState.enabled || !levelCfg.animations.throttleBrakeLight){
        clearStrip(channel);
        return;
    }

    int valuePerLed = (INPUT_HIGH - INPUT_MID) / channelCfg.stripLedCount;
    int absValue = abs(state->inputValues.esc - INPUT_MID);
    int numFullLeds = absValue / valuePerLed;
    int partialBrightness = absValue % valuePerLed;

    for(int i=0; i<channelCfg.stripLedCount/2; i++){
        int leftIdx = (channelCfg.stripLedCount/2)-i-1;
        int rightIdx = (channelCfg.stripLedCount/2)+i;

        if(state->inputValues.esc < INPUT_MID){
            if(i < numFullLeds){
                led_strips[channel][leftIdx] = reorderColor(CRGB(255,0,0), channelCfg.colorOrder);
                led_strips[channel][rightIdx] = reorderColor(CRGB(255,0,0), channelCfg.colorOrder);
            }else if(i == numFullLeds){ 
                float percentBrightness = ((float)partialBrightness / (float)valuePerLed);
                led_strips[channel][leftIdx] = reorderColor(CRGB(255*percentBrightness,0,0), channelCfg.colorOrder);
                led_strips[channel][rightIdx] = reorderColor(CRGB(255*percentBrightness,0,0), channelCfg.colorOrder);
            }else{
                led_strips[channel][leftIdx] = CRGB::Black;
                led_strips[channel][rightIdx] = CRGB::Black;
            }
        }else{
            if(i < numFullLeds){
                led_strips[channel][leftIdx] = reorderColor(CRGB(0,255,0), channelCfg.colorOrder);
                led_strips[channel][rightIdx] = reorderColor(CRGB(0,255,0), channelCfg.colorOrder);
            }else if(i == numFullLeds){
                float percentBrightness = ((float)partialBrightness / (float)valuePerLed);
                led_strips[channel][leftIdx] = reorderColor(CRGB(0,255*percentBrightness,0), channelCfg.colorOrder);
                led_strips[channel][rightIdx] = reorderColor(CRGB(0,255*percentBrightness,0), channelCfg.colorOrder);
            }else{
                led_strips[channel][leftIdx] = CRGB::Black;
                led_strips[channel][rightIdx] = CRGB::Black;
            }
        }
    }
}

void showExhaustFlame(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    if(!state->inputState.enabled || !levelCfg.animations.exhaustFlame){
        clearStrip(channel);
        return;
    }

    if(state->animationState.flameIntensity == 0 || state->animationState.currentFlameType == NO_FLAME){
        return clearStrip(channel);
    }

    uint8_t mappedIntensity = map(state->animationState.flameIntensity,0,MAX_EXHAUST_INTENSITY,0,255);
    //CRGB flameColor = HeatColor(mappedIntensity);
    CRGB flameColor = ColorFromPalette(state->animationState.flamePalette, mappedIntensity);
    for(int i=0; i<NUM_STRIP_LEDS; i++){
        led_strips[channel][i] = reorderColor(flameColor, channelCfg.colorOrder);
    }
}

void showPoliceLightsSolid(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    if(!state->inputState.enabled || !levelCfg.animations.policeLights){
        clearStrip(channel);
        return;
    }

    CRGB color = CRGB::Red;
    if(state->animationState.solidPoliceAlternateColor){
        color = CRGB::Blue;
    }

    for(int i=0;i<NUM_STRIP_LEDS;i++){
        led_strips[channel][i] = reorderColor(color, channelCfg.colorOrder);
    }
}

// void showPoliceLightsWrap(State* state, int channel){ //Split
//     OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
//     LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

//     if(!state->inputState.enabled || !levelCfg.animations.policeLights){
//         clearStrip(channel);
//         return;
//     }

//     for(int i=0;i<channelCfg.stripLedCount;i++){
//         CRGB color = CRGB(0,0,255);
//         CRGB dimColor = CRGB(0,0,0);
//         if(i > channelCfg.stripLedCount/2){
//             color = CRGB(255,0,0);
//             dimColor = CRGB(0,0,0);
//         }

//         bool isEven = true;
//         if(i % 2 == 1){
//             isEven = false;
//         }

//         if(state->animationState.wrapPoliceStrobePos == 2){
//             led_strips[channel][i] = reorderColor(color, channelCfg.colorOrder);
//         }else if(isEven && state->animationState.wrapPoliceStrobePos == 0){
//             led_strips[channel][i] = reorderColor(color, channelCfg.colorOrder);
//         }else if(isEven && state->animationState.wrapPoliceStrobePos == 1){
//             led_strips[channel][i] = reorderColor(dimColor, channelCfg.colorOrder);
//         }else if(!isEven && state->animationState.wrapPoliceStrobePos == 0){
//             led_strips[channel][i] = reorderColor(dimColor, channelCfg.colorOrder);
//         }else if(!isEven && state->animationState.wrapPoliceStrobePos == 1){
//             led_strips[channel][i] = reorderColor(color, channelCfg.colorOrder);
//         }else{
//             Serial.println("Missed Case");
//         }
//     }
// }

void showPoliceLightsWrap(State* state, int channel){ //Split
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    if(!state->inputState.enabled || !levelCfg.animations.policeLights){
        clearStrip(channel);
        return;
    }

    for(int i=0;i<channelCfg.stripLedCount;i++){
        CRGB color = CRGB(0,0,255);
        CRGB dimColor = CRGB(0,0,0);
        if(i > channelCfg.stripLedCount/2){
            color = CRGB(255,0,0);
            dimColor = CRGB(0,0,0);
        }

        if((state->animationState.wrapPoliceStrobePos == 0 || state->animationState.wrapPoliceStrobePos == 2)){
            if(i <= channelCfg.stripLedCount/2){
                led_strips[channel][i] = CRGB::Black;
            }else{
                led_strips[channel][i] = reorderColor(color, channelCfg.colorOrder);
            }
        }else if((state->animationState.wrapPoliceStrobePos == 3 || state->animationState.wrapPoliceStrobePos == 5)){
            if(i > channelCfg.stripLedCount/2){
                led_strips[channel][i] = CRGB::Black;
            }else{
                led_strips[channel][i] = reorderColor(color, channelCfg.colorOrder);
            }
        }else{
            led_strips[channel][i] = CRGB::Black;
        }
    }
}

void showCautionLights(State* state, int channel){
    
}

// Public functions
void SetupOutput(Config cfg){
    // setup led outputs
    for (int i = 0; i < MAX_CHANNELS; i++) {
        if (cfg.outputConfig.channelConfigs[i].type == SINGLE_LED){
            pinMode(cfg.outputConfig.channelConfigs[i].pin, OUTPUT);
        }else if (cfg.outputConfig.channelConfigs[i].type == LED_STRIP){
            EOrder order = cfg.outputConfig.channelConfigs[i].colorOrder;

            if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_1){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_1, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
                Serial.println("Added LED strip to pin 1");
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_2){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_2, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_3){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_3, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_4){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_4, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_5){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_5, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_6){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_6, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_7){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_7, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_8){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_8, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_9){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_9, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_10){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_10, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_11){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_11, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_12){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_12, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else{
                Serial.print("Invalid pin for LED strip: ");
                Serial.println(cfg.outputConfig.channelConfigs[i].pin);
            }
            
        }
    }

    FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_AMPS);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
    FastLED.show();
}

void ShowState(State* state){
    for (int i = 0; i < MAX_CHANNELS; i++) {

        if(!state->inputState.enabled){
            switch(state->config.outputConfig.channelConfigs[i].type){
                case SINGLE_LED:
                    analogWrite(state->config.outputConfig.channelConfigs[i].pin, 0);
                    break;
                case LED_STRIP:
                    clearStrip(i);
                    break;
                default:
                    //Serial.println("Invalid output type");
                    break;
            }
            continue;
        }

        switch(state->config.outputConfig.channelConfigs[i].type){
            case SINGLE_LED:
                showSingleLED(state, i);
                break;
            case LED_STRIP:
                switch(state->config.outputConfig.channelConfigs[i].stripAnimation){
                    case UNDERGLOW_SOLID:
                        showUnderglowSolid(state, i);
                        break;
                    case UNDERGLOW_BREATHE:
                        showUnderglowBreathe(state, i);
                        break;
                    case UNDERGLOW_CYCLE:
                        showUnderglowCycle(state, i);
                        break;
                    case UNDERGLOW_CHASE:
                        //showUnderglowChase(state, i);
                        break;
                    case THROTTLE_BRAKE_LIGHT_BOTTOM:
                        showThrottleBrakeLightBottom(state, i);
                        break;
                    case THROTTLE_BRAKE_LIGHT_TOP:
                        showThrottleBrakeLightTop(state, i);
                        break;
                    case THROTTLE_BRAKE_LIGHT_MIDDLE:
                        showThrottleBrakeLightMid(state, i);
                        break;
                    case EXHAUST_FLAME:
                        showExhaustFlame(state, i);
                        break;
                    case POLICE_LIGHTS_SOLID:
                        showPoliceLightsSolid(state, i);
                        break;
                    case POLICE_LIGHTS_WRAP:
                        showPoliceLightsWrap(state, i);
                        break;
                    case CAUTION_LIGHTS:
                        showCautionLights(state, i);
                        break;
                    default:
                        //Serial.println("Invalid strip animation");
                        break;
                }
                break;
            default:
                //Serial.println("Invalid output type");
                break;
        }
    }
    FastLED.show();
}