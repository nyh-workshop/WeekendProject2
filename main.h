#ifndef MAIN_H
#define MAIN_H

#include <LCD_I2C.h>
#include <RtcDS1307.h>
//#include <RTClib.h>
#include <Wire.h> // must be included here so that Arduino library object file references work

inline LCD_I2C lcd(0x3f);
inline RtcDS1307<TwoWire> Rtc(Wire);

inline bool checkTimeReachedMillis(uint32_t currentMillis, uint32_t previousMillis, uint32_t reachTime) {
  return (currentMillis - previousMillis >= reachTime);
}

#endif
