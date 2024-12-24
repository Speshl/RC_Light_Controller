#include "output.h"

CRGB led_strips[MAX_CHANNELS][NUM_STRIP_LEDS];

// Private functions

void clearStrip(int channel){
    for(int i = 0; i < NUM_STRIP_LEDS; i++){
        led_strips[channel][i] = CRGB::Black;
    }
}

void setLedColor(int channel, int led, CRGB color){
    led_strips[channel][led] = color;
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
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_13){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_13, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_14){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_14, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_15){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_15, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else if(cfg.outputConfig.channelConfigs[i].pin == OUTPUT_PIN_16){
                FastLED.addLeds<CHIPSET, OUTPUT_PIN_16, COLOR_ORDER>(led_strips[i], NUM_STRIP_LEDS);
            }else{
                Serial.print("Invalid pin for LED strip: ");
                Serial.println(cfg.outputConfig.channelConfigs[i].pin);
            }
            
        }
    }

    //FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_AMPS); //Not using due to issues with fading
    FastLED.setBrightness(BRIGHTNESS); // Make configurable on the global animation tab
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
                showRole(state, i);
                break;
            case LED_STRIP:
                switch(state->config.outputConfig.channelConfigs[i].stripAnimation){
                    case UNDERGLOW:
                        showUnderglow(state, i);
                        break;
                    case THROTTLE_BRAKE:
                        showThrottleBrakeLight(state, i);
                        break;
                    case EXHAUST:
                        showExhaustFlame(state, i);
                        break;
                    case EMERGENCY:
                        showEmergencyLights(state, i);
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