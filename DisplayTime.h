#ifndef DISPLAYTIME_H
#define DISPLAYTIME_H

extern const char* dayOfWeek3letter[8];

enum whichSetTimeState {
  normalDisp = 0,
  setTimeDisp,
};

enum whichDigitToBlink
{
  blinkColon = 0,
  blinkHour,
  blinkMinute,
  blinkDay,
  blinkMonth,
  blinkYear,
  blinkDOTW,
  blinkNone,
};

class DisplayTime {

  public:
    DisplayTime();
    void Update();
    void SetTimeUpdate(int8_t PlusOrMinus);
    void Display(uint8_t setBlinkDigit);
    uint8_t GetTimeState();
    void SetTimeState(uint8_t state);
    void SetBlinkState(uint8_t blinkState);
    uint8_t GetBlinkState();
    void NextBlinkState();
    void ResetSetTimeCounter();
    inline void adjustForDay(uint32_t& _year, int8_t& _month, int8_t& _day);
    
  private:
    uint8_t state;
    uint8_t blinkState;
    uint8_t showDigit;
    uint32_t digitToggleTime = 500;
    uint32_t previousMillis;
    uint32_t timeSetDuration = 3250;
    uint8_t setTimeCounter = 0;
    uint8_t setTimeCounterMax = (uint8_t)(timeSetDuration / digitToggleTime);
};

#endif
