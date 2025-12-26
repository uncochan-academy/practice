#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
public:
  void begin();
  void update(int distance);
  void beep();  // テスト用ビープ音

private:
  unsigned long lastBuzzerStartTime;
  bool isBuzzerOn;
};

#endif