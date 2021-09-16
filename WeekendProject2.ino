#include "main.h"
#include "custCharLCD.h"
#include "DisplayTime.h"
#include "RotaryEncoder.h"

DisplayTime dispTime;
RotaryEncoder rEncoder(3, 4, 2);
RtcDateTime defaultTime = RtcDateTime("Jan 01 2021", "12:00:00");

void buttonISR() {
  if(dispTime.GetTimeState() == normalDisp) {
    dispTime.SetTimeState(setTimeDisp);
  }

  if(dispTime.GetTimeState() == setTimeDisp) {
     dispTime.NextBlinkState();
     dispTime.ResetSetTimeCounter(); 
  }
}

void checkRTC() {
  if (!Rtc.IsDateTimeValid())
  {
    if (Rtc.LastError() != 0)
    {
      // we have a communications error
      // see https://www.arduino.cc/en/Reference/WireEndTransmission for
      // what the number means
      Serial.print("RTC communications error = ");
      Serial.println(Rtc.LastError());
    }
    else
    {
      Serial.println("RTC lost confidence in the DateTime!");
      Rtc.SetDateTime(defaultTime);
    }
  }

  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }
}

void setup() {

  attachInterrupt(digitalPinToInterrupt(2), buttonISR, FALLING);

  // Setup Serial Monitor
  Serial.begin(9600);
  Serial.println("Hello World!");

  pinMode(10, OUTPUT);

  // Start and check the RTC:
  Rtc.Begin();
  checkRTC();
  
  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
  // this stop the library(LCD_I2C) from calling Wire.begin()

  lcd.begin();

  lcd.backlight();

  // put your setup code here, to run once:
  LoadCustomChar(characterS1);

}

void loop() {
  // put your main code here, to run repeatedly:
  // poll the rotary encoder if in time setting mode! :D
  if(dispTime.GetTimeState() == setTimeDisp) {
    rEncoder.Update();
    int8_t temp = rEncoder.getRotaryEncoderState();
    if(temp != NOCHANGE) dispTime.ResetSetTimeCounter();
    dispTime.SetTimeUpdate(temp);
    rEncoder.clearRotaryEncoderState();
  }
  else
    dispTime.Update();
}
