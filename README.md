# Simon Sleeps: REVIVED!
## _The most annoying alarm clock... but better!_
This is the revival and optimization of our 1st Place Award Winning "[Simon Sleeps](https://github.com/jpeterson1823/engr122_simon_sleeps)" project.
_Currently in developement!_

## Planned Changes & Improvements
- Logic powered by the Raspberry Pi Pico 2 rather than the Arduino Nano
- Much cleaner source code.
- More complex hardware, allowing for more complex behavior.
  * The ability to set & save multiple alarms.
  * Selectively activate or deactivate saved alarms.
  * Available GPIO capabilities for even more behavior down the line.

The RPi Pico 2 was chosen mainly as a challenge/showcase of our skills, but also as a means to drive down prototype cost.
The original source code was rushed due to the short deadline of the project, as well as having other classes on top of our project.
As for the new hardware, we are employing the use of common shift registers to save on GPIO utilization, as well as a 64kb EEPROM for persistent memory.

### Current Hardware List
- Shift Register: SN74HC595N
- EEPROM: AT28HC64B
- 16x2 LCD Screen: NHD-0216K1Z-NS(RGB)-FBW-REV1
  * MPU: ST7066U
