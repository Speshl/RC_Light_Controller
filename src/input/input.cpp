#include "input.h"

// Pass any HardwareSerial port
// "Arduino" users (atmega328) can not use CRSF_BAUDRATE, as the atmega does not support it
// and should pass 250000, but then also must flash the receiver with RCVR_UART_BAUD=250000
// Also note the atmega only has one Serial, so logging to Serial must be removed
CrsfSerial crsf(Serial2, CRSF_BAUDRATE); //Arduino IOT use Serial1, ESP32 use Serial2, Serial is debug console

InputValues latestInput;
InputConfig inputConfig;

//Private functions

int getCRSFValueWithDeadzone(int value){
    if(value < CRSF_MID - CRSF_DEADZONE || value > CRSF_MID + CRSF_DEADZONE){
        return map(value, CRSF_LOW, CRSF_HIGH, INPUT_LOW, INPUT_HIGH);
    }else{
        return INPUT_MID;
    }
}

void handleCRSFUpdate(){
    //Serial.println("Got CRSF Update");
    int steer = crsf.getChannel(inputConfig.steerChannel);
    int esc = crsf.getChannel(inputConfig.escChannel);
    int level = crsf.getChannel(inputConfig.levelChannel);
    int enabled = crsf.getChannel(inputConfig.enableChannel);

    latestInput.steer = getCRSFValueWithDeadzone(steer);
    latestInput.esc = getCRSFValueWithDeadzone(esc);
    latestInput.level = getCRSFValueWithDeadzone(level);
    latestInput.enabled = getCRSFValueWithDeadzone(enabled);

    latestInput.lastUpdate = millis();
    //PrintInput(latestInput);
}

//Public functions
void SetupInput(Config* config){
    inputConfig = config->inputConfig;
    switch(config->inputConfig.type){
        case SBUS:
            Serial.println("Setting up SBUS (but not implemented yet)");
            //TODO: Implement SBUS
            break;
        case CRSF:
        default:
            Serial.println("Setting up CRSF");
            crsf.begin();
            crsf.onPacketChannels = &handleCRSFUpdate;
            break;
    }
}

InputValues GetLatestInput(){
    switch(inputConfig.type){
        case SBUS:
            break;
        case CRSF:
        default:
            crsf.loop();
            break;
    }
    return latestInput;
}

void PrintInput(InputValues inputValues){
    Serial.println("Input Values:");
    Serial.print("Steer: ");
    Serial.println(inputValues.steer);
    Serial.print("ESC: ");
    Serial.println(inputValues.esc);
    Serial.print("Level: ");
    Serial.println(inputValues.level);
    Serial.print("Enabled: ");
    Serial.println(inputValues.enabled);
    // Serial.print("Last Update: ");
    // Serial.println(latestInput.lastUpdate);
}