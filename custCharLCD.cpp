#include <Arduino.h>
#include "custCharLCD.h"
#include "main.h"

const uint8_t characterS1[8][8] = { { 3, 3, 3, 3, 3, 3, 3, 3 },
  { 31, 31, 24, 24, 24, 24, 31, 31 },
  { 31, 31, 3, 3, 3, 3, 3, 3 },
  { 31, 31, 3, 3, 3, 3, 31, 31 },
  { 27, 27, 27, 27, 27, 27, 31, 31 },
  { 31, 31, 27, 27, 27, 27, 31, 31 },
  { 31, 31, 27, 27, 27, 27, 27, 27 },
  { 3, 3, 3, 3, 3, 3, 31, 31 }
};

// Lookup pattern for the custom large fonts (using characterS1):
const uint8_t lookupNum[] = { 6, 4, // zero
                              0, 0, // one
                              2, 1, // two
                              2, 3, // three
                              4, 0, // four
                              1, 7, // five
                              1, 4, // six
                              2, 0, // seven
                              5, 4, // eight
                              5, 0  // nine
                            };

void LoadCustomChar(const uint8_t characterS[8][8]) {

  for (uint8_t i = 0; i < 8; i++)
    lcd.createChar(i, characterS[i]);

  for (uint8_t i = 0; i < 8; i++)
    lcd.createChar(i, characterS[i]);

}

void PlaceNum(uint8_t colNum, uint8_t rowNum, uint8_t number) {
  lcd.setCursor(colNum, rowNum);
  lcd.write(byte(lookupNum[number * 2]));
  lcd.setCursor(colNum, rowNum + 1);
  lcd.write(byte(lookupNum[number * 2 + 1]));
}

void BlankNum(uint8_t colNum, uint8_t rowNum) {
  lcd.setCursor(colNum, rowNum);
  lcd.print(" ");
  lcd.setCursor(colNum, rowNum + 1);
  lcd.print(" ");
}
