#include <Arduino.h>
#include "main.h"
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(uint8_t inputCLK, uint8_t inputDT, uint8_t buttonPin) {
  // Set encoder pins as inputs
  pinMode(inputCLK, INPUT_PULLUP);
  pinMode(inputDT, INPUT_PULLUP);

  previousStateCLK = digitalRead(inputCLK);

  currentStateCLK = 0;
  previousStateCLK = 0;
  this->inputCLK = inputCLK;
  this->inputDT = inputDT;
  this->buttonPin = buttonPin;
}

void RotaryEncoder::clearRotaryEncoderState() {
  RotaryEncoderState = NOCHANGE;
}

int8_t RotaryEncoder::getRotaryEncoderState() {
  return RotaryEncoderState;
}

void RotaryEncoder::Update() {
  //https://dronebotworkshop.com/rotary-encoders-arduino/
  uint32_t currentMillis = millis();

  if (checkTimeReachedMillis(currentMillis, previousMillis, updateTime)) {

    // Read the current state of inputCLK
    currentStateCLK = digitalRead(inputCLK);
    //button = digitalRead(buttonPin);

    // If the previous and the current state of the inputCLK are different then a pulse has occured
    if (currentStateCLK != previousStateCLK) {
      RotaryEncoderState = NOCHANGE;

      // If the inputDT state is different than the inputCLK state then
      // the encoder is rotating counterclockwise
      if (digitalRead(inputDT) != currentStateCLK) {
        RotaryEncoderState = CW;
      } else {
        RotaryEncoderState = CCW;
      }
      //Serial.print("Direction: ");
      //Serial.print(encdir);
      //Serial.print(" -- Value: ");
      //Serial.println(counter);
    }

    // Update previousStateCLK with the current state
    previousStateCLK = currentStateCLK;

    previousMillis = currentMillis;
  }
}
