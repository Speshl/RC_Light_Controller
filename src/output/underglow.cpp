#include "output.h"

void showUnderglowSolid(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];

    CRGB color = reorderColor(channelCfg.underglowConfig.primaryColor, channelCfg.colorOrder);
    for(int i=0;i<NUM_STRIP_LEDS;i++){
        setLedColor(channel, i, color);
    }
}

void showUnderglowBreathe(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];

    //int brightness = 127.5 * (1.0 + sin(millis() / 2000.0 * PI));
    CRGB initialColor = channelCfg.underglowConfig.primaryColor;
    if(state->animationState.underglow.breatheState >= 3){
        initialColor = channelCfg.underglowConfig.secondaryColor;
    }

    CRGB color = reorderColor(initialColor, channelCfg.colorOrder).scale8(state->animationState.underglow.breatheBrightness);
    for(int i=0;i<NUM_STRIP_LEDS;i++){
        setLedColor(channel, i, color);
    }
}

void showUnderglowPalette(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];

    CRGBPalette16 palette;
    switch(channelCfg.underglowConfig.palette){
        case UNDERGLOW_RAINBOW:
            palette = RainbowColors_p;
            break;
        case UNDERGLOW_CLOUD:
            palette = CloudColors_p;
            break;
        case UNDERGLOW_LAVA:
            palette = LavaColors_p;
            break;
        case UNDERGLOW_OCEAN:
            palette = OceanColors_p;
            break;
        case UNDERGLOW_FOREST:
            palette = ForestColors_p;
            break;
        case UNDERGLOW_PARTY:
            palette = PartyColors_p;
            break;
        case UNDERGLOW_HEAT:
            palette = HeatColors_p;
            break;
        default:
            palette = RainbowColors_p;
            break;
    }

    int speed = 3;
    // if(channelCfg.underglowConfig.speed > 0){
    //     speed = channelCfg.underglowConfig.speed;
    // }

    CRGB color = reorderColor(ColorFromPalette(palette, state->animationState.underglow.palettePos / speed, 255, LINEARBLEND), channelCfg.colorOrder);
    for(int i=0;i<NUM_STRIP_LEDS;i++){
        setLedColor(channel, i, color);
    }
}

void showUnderglow(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    if(!state->inputState.enabled || !levelCfg.animations.underglow){
        clearStrip(channel);
        return;
    }

    switch(channelCfg.underglowConfig.type){
        case UNDERGLOW_BREATHE:
            showUnderglowBreathe(state, channel);
            break;
        case UNDERGLOW_PALETTE:
            showUnderglowPalette(state, channel);
            break;
        case UNDERGLOW_SOLID:
        default:
            showUnderglowSolid(state, channel);
            break;
    }
}