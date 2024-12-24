#include "output.h"

void showThrottleBrakeLightTop(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];

    int valuePerLed = (INPUT_HIGH - INPUT_MID) / channelCfg.stripLedCount;
    int absValue = abs(state->inputValues.esc - INPUT_MID);
    int numFullLeds = absValue / valuePerLed;
    int partialBrightness = absValue % valuePerLed;

    CRGB color = reorderColor(channelCfg.throttleBrakeConfig.throttleColor, channelCfg.colorOrder);
    if (state->inputValues.esc < INPUT_MID){
        color = reorderColor(channelCfg.throttleBrakeConfig.brakeColor, channelCfg.colorOrder);
    }

    for(int i=0; i<channelCfg.stripLedCount; i++){
        int idx = (channelCfg.stripLedCount-1)-i;
        if(i < numFullLeds){
            setLedColor(channel, idx, color);
        }else if(i == numFullLeds){
            float percentBrightness = ((float)partialBrightness / (float)valuePerLed);
            setLedColor(channel, idx, color.scale8(255 * percentBrightness));
        }else{
            setLedColor(channel, idx, CRGB::Black);
        }
    }
}

void showThrottleBrakeLightBottom(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];

    int valuePerLed = (INPUT_HIGH - INPUT_MID) / channelCfg.stripLedCount;
    int absValue = abs(state->inputValues.esc - INPUT_MID);
    int numFullLeds = absValue / valuePerLed;
    int partialBrightness = absValue % valuePerLed;

    CRGB color = reorderColor(channelCfg.throttleBrakeConfig.throttleColor, channelCfg.colorOrder);
    if (state->inputValues.esc < INPUT_MID){
        color = reorderColor(channelCfg.throttleBrakeConfig.brakeColor, channelCfg.colorOrder);
    }

    for(int i=0; i<channelCfg.stripLedCount; i++){
        if(i < numFullLeds){
            setLedColor(channel, i, color);
        }else if(i == numFullLeds){
            float percentBrightness = ((float)partialBrightness / (float)valuePerLed);
            setLedColor(channel, i, color.scale8(255 * percentBrightness));
        }else{
            setLedColor(channel, i, CRGB::Black);
        }
    }
}

void showThrottleBrakeLightMid(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];

    int valuePerLed = (INPUT_HIGH - INPUT_MID) / channelCfg.stripLedCount;
    int absValue = abs(state->inputValues.esc - INPUT_MID);
    int numFullLeds = absValue / valuePerLed;
    int partialBrightness = absValue % valuePerLed;

    CRGB color = reorderColor(channelCfg.throttleBrakeConfig.throttleColor, channelCfg.colorOrder);
    if (state->inputValues.esc < INPUT_MID){
        color = reorderColor(channelCfg.throttleBrakeConfig.brakeColor, channelCfg.colorOrder);
    }

    for(int i=0; i<channelCfg.stripLedCount; i++){
        int leftIdx = (channelCfg.stripLedCount/2)-i-1;
        int rightIdx = (channelCfg.stripLedCount/2)+i;
        if(i < numFullLeds){
            setLedColor(channel, leftIdx, color);
            setLedColor(channel, rightIdx, color);
        }else if(i == numFullLeds){
            float percentBrightness = ((float)partialBrightness / (float)valuePerLed);
            setLedColor(channel, leftIdx, color.scale8(255 * percentBrightness));
            setLedColor(channel, rightIdx, color.scale8(255 * percentBrightness));
        }else{
            setLedColor(channel, leftIdx, CRGB::Black);
            setLedColor(channel, rightIdx, CRGB::Black);
        }
    }
}

void showThrottleBrakeLight(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    if(!state->inputState.enabled || !levelCfg.animations.throttleBrakeLight){
        clearStrip(channel);
        return;
    }

    switch(channelCfg.throttleBrakeConfig.type){
        case TB_TOP:
            showThrottleBrakeLightTop(state, channel);
            break;
        case TB_BOTTOM:
            showThrottleBrakeLightBottom(state, channel);
            break;
        case TB_MID:
        default:
            showThrottleBrakeLightMid(state, channel);
            break;
            
    }
}