#include "output.h"

void showEmergencyLightsSolid(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    CRGB color = reorderColor(channelCfg.underglowConfig.primaryColor, channelCfg.colorOrder);
    if(state->animationState.emergency.solidAlternateColor){
        color = reorderColor(channelCfg.underglowConfig.secondaryColor, channelCfg.colorOrder);
    }

    for(int i=0;i<NUM_STRIP_LEDS;i++){
        setLedColor(channel, i, color);
    }
}

void showEmergencyLightsWrap(State* state, int channel){ //Split
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    CRGB primaryColor = reorderColor(channelCfg.underglowConfig.primaryColor, channelCfg.colorOrder);
    CRGB secondaryColor = reorderColor(channelCfg.underglowConfig.secondaryColor, channelCfg.colorOrder);

    for(int i=0;i<channelCfg.stripLedCount;i++){
        if((state->animationState.emergency.strobePos == 0 || state->animationState.emergency.strobePos == 2)){
            if(i < channelCfg.stripLedCount/2){
                setLedColor(channel, i, secondaryColor);
            }else{
                setLedColor(channel, i, primaryColor);
            }
        }else if((state->animationState.emergency.strobePos == 3 || state->animationState.emergency.strobePos == 5)){
            if(i >= channelCfg.stripLedCount/2){
                setLedColor(channel, i, secondaryColor);
            }else{
                setLedColor(channel, i, primaryColor);
            }
        }else{
            setLedColor(channel, i, secondaryColor);
        }
    }
}

void showEmergencyLights(State* state, int channel){
    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    if(!state->inputState.enabled || !levelCfg.animations.emergencyLights){
        clearStrip(channel);
        return;
    }

    switch(state->config.outputConfig.channelConfigs[channel].emergencyConfig.type){
        case EMERGENCY_WRAP:
            showEmergencyLightsWrap(state, channel);
            break;
        case EMERGENCY_SOLID:
        default:
            showEmergencyLightsSolid(state, channel);
            break;
    }
}