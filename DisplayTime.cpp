#include <Arduino.h>
#include "DisplayTime.h"
#include "custCharLCD.h"
#include "main.h"

const char *dayOfWeek3letter[8] = {
  "SUN",
  "MON",
  "TUE",
  "WED",
  "THU",
  "FRI",
  "SAT",
};

DisplayTime::DisplayTime() {
  //timeSetTimeCountIn500ms = 0;
  setTimeCounter = 0;
  previousMillis = 0;
  blinkState = blinkColon;
  state = normalDisp;
  showDigit = true;
}

void DisplayTime::NextBlinkState() {
  ++blinkState;

  if (blinkState > blinkYear) {
    blinkState = blinkColon;
    SetTimeState(normalDisp);
  }
}

uint8_t DisplayTime::GetTimeState() {
  return state;
}

void DisplayTime::SetTimeState(uint8_t state) {
  this->state = state;
}

void DisplayTime::SetBlinkState(uint8_t blinkState) {
  this->blinkState = blinkState;
}

uint8_t DisplayTime::GetBlinkState() {
  return blinkState;
}

void DisplayTime::Display(uint8_t setBlinkDigit) {

  RtcDateTime now = Rtc.GetDateTime();

  const uint8_t hourLocation = 1;
  const uint8_t minuteLocation = 4;
  const uint8_t colonLocation = 3;
  const uint8_t dayLocation = 7;
  const uint8_t monthLocation = 10;
  const uint8_t yearLocation = 13;
  const uint8_t DOTWLocation = 7;

  char dateStr[9];
  sprintf(dateStr, "%02d-%02d-%02d", now.Day(), now.Month(), now.Year() - 2000);

  lcd.setCursor(7, 0);
  lcd.print(dateStr);
  lcd.setCursor(7, 1);
  lcd.print(dayOfWeek3letter[now.DayOfWeek()]);

  PlaceNum(hourLocation, 0, now.Hour() / 10);
  PlaceNum(hourLocation + 1, 0, now.Hour() % 10);
  lcd.setCursor(colonLocation, 0);
  lcd.write(byte(0xa5));
  PlaceNum(minuteLocation, 0, now.Minute() / 10);
  PlaceNum(minuteLocation + 1, 0, now.Minute() % 10);
  lcd.setCursor(colonLocation, 1);
  lcd.write(byte(0xa5));

  switch (setBlinkDigit)
  {
    case blinkHour:
      lcd.setCursor(hourLocation, 0);
      lcd.print("  ");
      lcd.setCursor(hourLocation, 1);
      lcd.print("  ");
      break;

    case blinkMinute:
      lcd.setCursor(minuteLocation, 0);
      lcd.print("  ");
      lcd.setCursor(minuteLocation, 1);
      lcd.print("  ");
      break;

    case blinkDay:
      lcd.setCursor(dayLocation, 0);
      lcd.print("  ");
      break;

    case blinkMonth:
      lcd.setCursor(monthLocation, 0);
      lcd.print("  ");
      break;

    case blinkYear:
      lcd.setCursor(yearLocation, 0);
      lcd.print("  ");
      break;

    case blinkDOTW:
      lcd.setCursor(DOTWLocation, 1);
      lcd.print("   ");
      break;

    case blinkColon:
      lcd.setCursor(colonLocation, 0);
      lcd.write(' ');
      lcd.setCursor(colonLocation, 1);
      lcd.write(' ');
      break;

    default:
      break;
  }
}

void DisplayTime::ResetSetTimeCounter() {
  setTimeCounter = 0;
}

inline void DisplayTime::adjustForDay(uint32_t& _year, int8_t& _month, int8_t& _day) {
  if ((_month == 1) || (_month == 3) || (_month == 5) || (_month == 7) ||
      (_month == 8) || (_month == 10) || (_month == 12))
  {
    if (_day > 31)
      _day = 1;
    if (_day < 1)
      _day = 31;
  }
  else if ((_month == 2) && !(_year % 4))
  {
    if (_day > 29)
      _day = 1;
    if (_day < 1)
      _day = 29;
  }
  else if ((_month == 2) && (_year % 4))
  {
    if (_day > 28)
      _day = 1;
    if (_day < 1)
      _day = 28;
  }
  else
  {
    if (_day > 30)
      _day = 1;
    if (_day < 1)
      _day = 30;
  }
}

void DisplayTime::SetTimeUpdate(int8_t PlusOrMinus) {
  uint32_t currentMillis = millis();

  RtcDateTime now = Rtc.GetDateTime();
  int8_t _hour = now.Hour();
  int8_t _minute = now.Minute();
  int8_t _month = now.Month();
  uint32_t _year = now.Year();
  int8_t _day = now.Day();

  if (PlusOrMinus == 1) {
    switch (blinkState) {
      case blinkHour:
        _hour++;
        if (_hour > 23) _hour = 0;
        now = RtcDateTime(now.Year(), now.Month(), now.Day(), (uint8_t)_hour, now.Minute(), now.Second());
        Rtc.SetDateTime(now);
        break;
      case blinkMinute:
        _minute++;
        if (_minute > 59) _minute = 0;
        now = RtcDateTime(now.Year(), now.Month(), now.Day(), now.Hour(), (uint8_t)_minute, now.Second());
        Rtc.SetDateTime(now);
        break;
      case blinkDay:
        _day++;
        adjustForDay(_year, _month, _day);
        now = RtcDateTime(now.Year(), now.Month(), (uint8_t)_day, now.Hour(), now.Minute(), now.Second());
        Rtc.SetDateTime(now);
        break;        
      case blinkMonth:
        _month++;
        if (_month > 12) _month = 1;
        adjustForDay(_year, _month, _day);
        now = RtcDateTime(now.Year(), _month, now.Day(), now.Hour(), now.Minute(), now.Second());
        Rtc.SetDateTime(now);
        break;
      case blinkYear:
        _year++;
        if (_year > 2099) _year = 2000;
        adjustForDay(_year, _month, _day);
        now = RtcDateTime(_year, now.Month(), now.Day(), now.Hour(), now.Minute(), now.Second());
        Rtc.SetDateTime(now);
        break;
      default:
        break;
    }
  } else if (PlusOrMinus == -1) {
    switch (blinkState) {
      case blinkHour:
        _hour--;
        if (_hour < 0) _hour = 23;
        now = RtcDateTime(now.Year(), now.Month(), now.Day(), _hour, now.Minute(), now.Second());
        Rtc.SetDateTime(now);
        break;
      case blinkMinute:
        _minute--;
        if (_minute < 0) _minute = 59;
        now = RtcDateTime(now.Year(), now.Month(), now.Day(), now.Hour(), _minute, now.Second());
        Rtc.SetDateTime(now);
        break;
      case blinkDay:
        _day--;
        adjustForDay(_year, _month, _day);
        now = RtcDateTime(now.Year(), now.Month(), (uint8_t)_day, now.Hour(), now.Minute(), now.Second());
        Rtc.SetDateTime(now);
        break;     
      case blinkMonth:
        _month--;
        if (_month < 1) _month = 12;
        adjustForDay(_year, _month, _day);
        now = RtcDateTime(now.Year(), _month, now.Day(), now.Hour(), now.Minute(), now.Second());
        Rtc.SetDateTime(now);
        break;
      case blinkYear:
        _year--;
        if (_year < 2000) _year = 2099;
        adjustForDay(_year, _month, _day);
        now = RtcDateTime(_year, now.Month(), now.Day(), now.Hour(), now.Minute(), now.Second());
        Rtc.SetDateTime(now);
        break;  
      default:
        break;
    }
  }

  if (checkTimeReachedMillis(currentMillis, previousMillis, digitToggleTime)) {
    //Serial.println(PlusOrMinus, DEC);
    showDigit ^= 1;
    setTimeCounter++;

    if (showDigit) {
      Display(blinkNone);
    } else {
      Display(blinkState);
    }

    if (setTimeCounter > setTimeCounterMax) {
      state = normalDisp;
      blinkState = blinkColon;
      setTimeCounter = 0;
    }

    previousMillis = currentMillis;
  }
}

void DisplayTime::Update() {
  uint32_t currentMillis = millis();

  if (checkTimeReachedMillis(currentMillis, previousMillis, digitToggleTime)) {

    showDigit ^= 1;

    if (showDigit) {
      Display(blinkNone);
    } else {
      Display(blinkColon);
    }

    previousMillis = currentMillis;
  }
}
