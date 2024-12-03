#include "input.h"
#include "sbus.h"

// Pass any HardwareSerial port
// "Arduino" users (atmega328) can not use CRSF_BAUDRATE, as the atmega does not support it
// and should pass 250000, but then also must flash the receiver with RCVR_UART_BAUD=250000
// Also note the atmega only has one Serial, so logging to Serial must be removed
CrsfSerial crsf(Serial2, CRSF_BAUDRATE); //Arduino IOT use Serial1, ESP32 use Serial2, Serial is debug console

bfs::SbusRx sbus_rx(&Serial2, SERIAL2_RX, SERIAL2_TX, true, ENABLE_FAST_SBUS);

InputValues latestInput;
InputConfig inputConfig;

int sbusTimesWithoutUpdate = 0;

//Private functions

int getCRSFValueWithDeadzone(int value){
    if(value < CRSF_MID - CRSF_DEADZONE || value > CRSF_MID + CRSF_DEADZONE){
        return map(value, CRSF_LOW, CRSF_HIGH, INPUT_LOW, INPUT_HIGH);
    }else{
        return INPUT_MID;
    }
}

int getSBUSValueWithDeadzone(int value){
    if(value < SBUS_MID - SBUS_DEADZONE || value > SBUS_MID + SBUS_DEADZONE){
        return map(value, SBUS_LOW, SBUS_HIGH, INPUT_LOW, INPUT_HIGH);
    }else{
        return INPUT_MID;
    }
}

void handleCRSFUpdate(){
    int steer = crsf.getChannel(inputConfig.steerChannel);
    int esc = crsf.getChannel(inputConfig.escChannel);
    int level = crsf.getChannel(inputConfig.levelChannel);
    int enabled = crsf.getChannel(inputConfig.enableChannel);

    latestInput.steer = getCRSFValueWithDeadzone(steer);
    latestInput.esc = getCRSFValueWithDeadzone(esc);
    latestInput.level = getCRSFValueWithDeadzone(level);
    latestInput.enabled = getCRSFValueWithDeadzone(enabled);

    latestInput.lastUpdate = millis();
}

void handleSBUSUpdate() {
    int steer = SBUS_MID;
    int esc = SBUS_MID;
    int level = SBUS_MID;
    int enabled = SBUS_MID;
    sbusTimesWithoutUpdate++;
    if(sbus_rx.Read()){
        sbusTimesWithoutUpdate = 0;
        bfs::SbusData data = sbus_rx.data();
        steer = data.ch[inputConfig.steerChannel - 1];
        esc = data.ch[inputConfig.escChannel - 1];
        level = data.ch[inputConfig.levelChannel - 1];
        enabled = data.ch[inputConfig.enableChannel - 1];

        latestInput.steer = getSBUSValueWithDeadzone(steer);
        latestInput.esc = getSBUSValueWithDeadzone(esc);
        latestInput.level = getSBUSValueWithDeadzone(level);
        latestInput.enabled = getSBUSValueWithDeadzone(enabled);
        latestInput.lastUpdate = millis(); // Maybe doesn't need update when we don't get input
    }

    if(sbusTimesWithoutUpdate > NO_SIGNAL_TIMES_TIL_MID){
        sbusTimesWithoutUpdate = NO_SIGNAL_TIMES_TIL_MID + 1;
        latestInput.steer = INPUT_MID;
        latestInput.esc = INPUT_MID;
        latestInput.level = INPUT_MID;
        latestInput.enabled = INPUT_MID;
    }
}

//Public functions
void SetupInput(Config* config){
    inputConfig = config->inputConfig;
    switch(config->inputConfig.type){
        case SBUS:
            Serial.println("Setting up SBUS");
            sbus_rx.Begin();
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
            handleSBUSUpdate();
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