# About the Project
  This software when paired with an ESP32 and custom board (here) allows the control of up to 11 (8+3) channels of lights intended for an RC car.  That is 8 channels of role based (turn signals, brake light, etc...) and 3 channels of led strip with selectable animations (Exhaust backfire, police light, etc...).  This controller is to be directly connected to the RC receiver through either a ERLS or SBUS connection. This allows the RC Light Controller (RCLC) to access steering, esc, and aux channel information to animate the lights accordingly.

## Supported Features
 - Support of On/Off toggle on specified channel
 - Supports 3 configurable light levels (some possibilities below)
   - Day lights | Low Beams | High Beams
   - Day lights | Night Lights | Party Lights
 - 8 light channels support any combination of 12 roles
   - Left Turn
   - Right Turn
   - Brake Light
   - Tail Light (on with headlights, but half power)
   - Head Light
   - Reverse Light
   - Hazard Light
   - Running Light
   - Aux1 Light
   - Aux2 Light
   - Strobe1 Light
   - Strobe2 Light
     
- 3 LED strip animation channels (4 with additional soldering)
  - Solid Underglow
  - Breathing Underglow
  - Cycling Underglow
  - Throttle Brake Bottom
  - Throttle Brake Top
  - Throttle Brake Middle
  - Exhaust Flame
  - Police Solid
  - Police Wrap
   

### Flashing ESP32 with RCLC firmware
 TODO

### Web Configuration
  1.  Power on the RCLC after flashing firmware.
  2.  On your pc (or any device with a browser), connect to the "light-control-config" wifi network which should be visible within a few seconds of powering on.
  3.  In your browser navigate to "192.168.1.1", and you should see the web interface.
  
### Force JSON Configuration
 In the platformio.ini file in the root of the repository, you can modify the "ForceConfig" command line variable to be "true".  This will force the controller to always load forced config file located at /data/config/forced.json.  The json values here can be manually adjusted quickly but you risk setting values outside of supported ranges.

### Example Implementations
- Cop Car Video
- Tow Pig Video
- BMW Video
- Comaro Video

### Example Hookup Guides
- ELRS Hookup Guide
- SBUS Hookup Guide
