#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include "DisplayTime.h"

enum RotaryEncoderState {
  CCW = -1,
  NOCHANGE = 0,
  CW = 1,
};

class RotaryEncoder {
  public:
    RotaryEncoder(uint8_t inputCLK, uint8_t inputDT,  uint8_t button);
    void Update();
    int8_t getRotaryEncoderState();
    void clearRotaryEncoderState();

  private:
    int8_t RotaryEncoderState; // +1 = clockwise, -1 = counter-clockwise, 0 = no change.
    uint8_t inputCLK;
    uint8_t inputDT;
    uint8_t buttonPin;
    uint8_t currentStateCLK;
    uint8_t previousStateCLK;
    String encdir = "";
    uint32_t previousMillis;
    uint32_t updateTime = 10;
};

#endif
