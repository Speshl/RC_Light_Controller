# RC Light Controller (RCLC)

This software, when paired with an ESP32 and a custom board, allows the control of up to 16 channels of lights intended for an RC car. All 16 channels can either be role-based lights (turn signals, brake light, etc.) or LED strips with selectable animations (exhaust backfire, police light, etc.). The controller connects directly to the RC receiver through either an ELRS or SBUS connection, allowing the RCLC to access steering, ESC, and aux channel information to animate the lights accordingly.

## Table of Contents

- [Supported Features](#supported-features)
- [Installation](#installation)
- [Flashing ESP32 with RCLC Firmware](#flashing-esp32-with-rclc-firmware)
- [Web Configuration](#web-configuration)
- [License](#license)

## Supported Features
 - Support of On/Off toggle on specified channel
 - Supports 3 configurable light levels (some possibilities below)
   - Day lights | Low Beams | High Beams
   - Day lights | Night Lights | Party Lights
 - 16 light channels support any combination of 12 roles
   - Left Turn
   - Right Turn
   - Brake Light
   - Tail Light (on with headlights, but half power)
   - Head Light
   - Reverse Light
   - Hazard Light
   - Running Light (on with headlights, but half power)
   - Aux1 Light
   - Aux2 Light
   - Strobe1 Light
   - Strobe2 Light
     
- 16 LED strip animation channels
  - Solid Underglow
  - Breathing Underglow
  - Cycling Underglow
  - Throttle Brake Bottom
  - Throttle Brake Top
  - Throttle Brake Middle
  - Exhaust Flame
  - Police Solid
  - Police Wrap
   

### Installation
 TODO

### Web Configuration
  1.  Power on the RCLC after flashing firmware.
  2.  On your pc (or any device with a browser), connect to the "RCLC-Config" wifi network which should be visible within a few seconds of powering on.
  3.  In your browser navigate to "192.168.4.20", and you should see the web interface.
  
### Force JSON Configuration
 In the platformio.ini file in the root of the repository, you can modify the "ForceConfig" command line variable to be "true".  This will force the controller to always load forced config file located at /data/config/forced.json.  The json values here can be manually adjusted quickly but you risk setting values outside of supported ranges.

### Example Implementations
- [Overview Video](https://youtu.be/ARDWy_AEoaI?si=Mk2jUiTP16_hjR4u)
- Cop Car Video
- Tow Pig Video
- BMW Video
- Comaro Video

### Example Hookup Guides
- ELRS Hookup Guide
- SBUS Hookup Guide
