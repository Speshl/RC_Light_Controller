#include "animation.h"

void calculateUnderglowPaletteAnimation(UnderglowState* glow) {
    glow->palettePos ++;

    int speed = 3;
    // if(glow->paletteSpeed > 0) {
    //     speed = glow->paletteSpeed;
    // }

    if(glow->palettePos >= 255 * speed){
        glow->palettePos = 0;
    }
    return;
}

void calculateUnderglowBreatheAnimation(UnderglowState* glow) {
    switch(glow->breatheState){
        case 0:// fade up primary color
            glow->breatheBrightness += 1;
            if(glow->breatheBrightness >= 255){
                glow->breatheBrightness = 255;
                glow->breatheHold = 0;
                glow->breatheState = 1;
            }
            break;
        case 1:// hold primary color
            glow->breatheHold += 1;
            if(glow->breatheHold >= 127){
                glow->breatheHold = 0;
                glow->breatheState = 2;
            }
            break;
        case 2:// fade down primary color
            glow->breatheBrightness -= 1;
            if(glow->breatheBrightness <= 0){
                glow->breatheBrightness = 0;
                glow->breatheState = 3;
            }
            break;
        case 3:// fade up secondary color
            glow->breatheBrightness += 1;
            if(glow->breatheBrightness >= 255){
                glow->breatheBrightness = 255;
                glow->breatheHold = 0;
                glow->breatheState = 4;
            }
            break;
        case 4:// hold secondary color
            glow->breatheHold += 1;
            if(glow->breatheHold >= 127){
                glow->breatheHold = 0;
                glow->breatheState = 5;
            }
            break;
        case 5:// fade down secondary color
            glow->breatheBrightness -= 1;
            if(glow->breatheBrightness <= 0){
                glow->breatheBrightness = 0;
                glow->breatheState = 0;
            }
            break;
        default:
            glow->breatheState = 0;
            break;
    }
    return;
}