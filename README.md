# WeekendProject2

### Simple custom LCD fonts digital clock.

This is a simple custom LCD (HD44780) fonts digital clock. 

Originally written in January 2011 for the Microchip PIC microcontroller and about 10% of them are re-used.

![alt tag](https://github.com/nyh-workshop/WeekendProject2/blob/main/weekendproject2.jpg)

Basic rotary encoder code from: https://dronebotworkshop.com/rotary-encoders-arduino/

Arduino Multitasking code from: https://learn.adafruit.com/multi-tasking-the-arduino-part-1

Parts required:
- Arduino Nano
- DS1307 module
- LCD (HD44780) module
- I2C to LCD adapter (PCF8574)
- Rotary Encoder with button

Schematic
![alt_tag](https://github.com/nyh-workshop/WeekendProject2/blob/main/schematic.png)

How to use:
- Press the middle button to set the time. 
- Press again to move to the next time you want to set: Hour->Minute->Day->Month->Year
- The time you want to set is blinking. If no activity for about 3 seconds, return back to displaying time.
- Turn clockwise or counterclockwise to adjust the time.
