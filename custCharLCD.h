#ifndef CUSTCHARLCD_H
#define CUSTCHARLCD_H

extern const uint8_t characterS1[8][8];
extern const uint8_t lookupNum[];

void LoadCustomChar(const uint8_t characterS[8][8]);
void PlaceNum(uint8_t colNum, uint8_t rowNum, uint8_t number);
void BlankNum(uint8_t colNum, uint8_t rowNum);

#endif
