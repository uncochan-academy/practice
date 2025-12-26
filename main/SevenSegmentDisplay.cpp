#include "SevenSegmentDisplay.h"
#include "Config.h"

void SevenSegmentDisplay::begin() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(DIGIT_PINS[i], OUTPUT);
    digitalWrite(DIGIT_PINS[i], HIGH);  // 消灯（アクティブロー）
  }
}

void SevenSegmentDisplay::displayNumber(int num) {
  int d[4];

  // 各桁の数値を計算
  d[0] = (num / 1000) % 10;
  d[1] = (num / 100) % 10;
  d[2] = (num / 10) % 10;
  d[3] = num % 10;

  bool leadingZero = true;  // 先頭ゼロフラグ

  for (int i = 0; i < 4; i++) {
    byte patternIndex = d[i];

    // 最下位桁(i=3)以外で、かつ「これまでずっと0」かつ「今の桁も0」なら消灯
    if (i < 3 && leadingZero && d[i] == 0) {
      patternIndex = 10;  // 全消灯パターン(NUM_PATTERNSの11番目)
    } else {
      leadingZero = false;  // 0以外の数字が出たらフラグ解除
    }

    // 74HC595にパターンを送信
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, NUM_PATTERNS[patternIndex]);
    digitalWrite(LATCH_PIN, HIGH);

    // 桁をON
    digitalWrite(DIGIT_PINS[i], LOW);
    delay(1);
    // 桁をOFF
    digitalWrite(DIGIT_PINS[i], HIGH);
  }
}

void SevenSegmentDisplay::clear() {
  // すべての桁を消灯
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, NUM_PATTERNS[10]);  // 消灯パターン
  digitalWrite(LATCH_PIN, HIGH);

  for (int i = 0; i < 4; i++) {
    digitalWrite(DIGIT_PINS[i], HIGH);  // すべての桁をOFF
  }
}