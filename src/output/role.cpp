#include "output.h"

//The order in which roles are handled is important. Higher priority roles should be handled first, and lower priority roles should be handled last.
void showRole(State* state, int channel){

    OutputChannelConfig channelCfg = state->config.outputConfig.channelConfigs[channel];
    LevelConfig levelCfg = state->config.levelConfigs[state->inputState.level];

    if(!state->inputState.enabled){
        analogWrite(channelCfg.pin, 0);
        return;
    }

    if(channelCfg.roles.hazard && levelCfg.roles.hazard && state->inputState.hazards){
        if(state->animationState.roleStates.hazards.blinkOn){
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
        if(state->animationState.roleStates.leftTurn.blinkOn){
            analogWrite(channelCfg.pin, 255);
        }else{
            analogWrite(channelCfg.pin, 0);
        }
        return;
    }

    if(channelCfg.roles.rightTurn && levelCfg.roles.rightTurn && state->inputState.rightTurn){
        if(state->animationState.roleStates.rightTurn.blinkOn){
            analogWrite(channelCfg.pin, 255);
        }else{
            analogWrite(channelCfg.pin, 0);
        }
        return;
    }

    if(channelCfg.roles.strobe1 && levelCfg.roles.strobe1 && state->animationState.roleStates.strobe1.blinkOn){
        analogWrite(channelCfg.pin, 255);
        return;
    }

    if(channelCfg.roles.strobe2 && levelCfg.roles.strobe2 && state->animationState.roleStates.strobe2.blinkOn){
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
        analogWrite(channelCfg.pin, 75); // low power for tail lights
        return;
    }

    if(channelCfg.roles.reverse && levelCfg.roles.reverse && state->inputState.reverse){
        analogWrite(channelCfg.pin, 255);
        return;
    }
    
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
