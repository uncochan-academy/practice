#ifndef SEVEN_SEGMENT_DISPLAY_H
#define SEVEN_SEGMENT_DISPLAY_H

#include <Arduino.h>

class SevenSegmentDisplay {
public:
  void begin();
  void setNumber(int num);  // 表示する数値を設定（displayNumber から名前変更）
  void clear();

  static void timerISR();  // Timer1割り込みハンドラ（staticが必要）

private:
  static SevenSegmentDisplay* instance;  // Singletonパターン

  volatile int displayValue;     // 表示する数値
  volatile int currentDigit;     // 現在表示中の桁（0-3）
  volatile int digitPatterns[4]; // 各桁のパターン（事前計算）

  void updateDisplay();  // 実際の表示更新（ISRから呼ばれる）
  void calculateDigitPatterns();  // 桁パターンを計算
};

#endif
