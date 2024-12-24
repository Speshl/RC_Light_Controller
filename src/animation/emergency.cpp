#include "animation.h"

void calculateEmergencyLightAnimation(EmergencyState* emergency){
    unsigned long elapsedTime = millis();
    // Alternate the blink on every interval
    if((elapsedTime / TURN_FLASH_INTERVAL) % 2 == 0){
        emergency->solidAlternateColor = true;
    } else {
        emergency->solidAlternateColor = false;
    }


    if(emergency->lastStrobeChange + STROBE_FLASH_INTERVAL < elapsedTime){
        emergency->strobePos ++;
        if(emergency->strobePos > 5){
            emergency->strobePos = 0;
        }
        emergency->lastStrobeChange = elapsedTime;
    }
    return;
}