#ifndef SEVEN_SEGMENT_DISPLAY_H
#define SEVEN_SEGMENT_DISPLAY_H

#include <Arduino.h>

class SevenSegmentDisplay {
public:
  void begin();
  void displayNumber(int num);
  void clear();

private:
  void displayDigit(int digitIndex, byte pattern);
};

#endif