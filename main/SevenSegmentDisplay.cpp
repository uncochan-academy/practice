#include "SevenSegmentDisplay.h"
#include "Config.h"

// Singletonインスタンス（static関数から非staticメンバにアクセスするため）
SevenSegmentDisplay* SevenSegmentDisplay::instance = nullptr;

void SevenSegmentDisplay::begin() {
  instance = this;  // Singleton登録

  // ピン設定
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(DIGIT_PINS[i], OUTPUT);
    digitalWrite(DIGIT_PINS[i], HIGH);  // 消灯（アクティブロー）
  }

  // 初期化
  displayValue = 0;
  currentDigit = 0;
  for (int i = 0; i < 4; i++) {
    digitPatterns[i] = 10;  // すべて消灯
  }

  // ========================================
  // Timer1設定（レジスタ直接操作）
  // ========================================
  noInterrupts();  // 割り込み一時停止

  // Timer1レジスタをクリア
  TCCR1A = 0;  // Timer/Counter Control Register A
  TCCR1B = 0;  // Timer/Counter Control Register B
  TCNT1 = 0;   // Timer/Counter Register（現在のカウント値）

  // 1ms周期の計算:
  // Arduino Unoのクロック: 16MHz
  // 分周比: 64
  // 比較値: 250
  // 周期 = 16,000,000Hz / 64 / 250 = 1000Hz = 1ms
  OCR1A = 249;  // Output Compare Register A（比較値、0から数えるので250-1=249）

  // CTCモード（Clear Timer on Compare Match）
  // カウンタがOCR1Aに到達したら自動的に0にリセット
  TCCR1B |= (1 << WGM12);

  // 64分周設定（CS11とCS10を両方1にする）
  // CS12 CS11 CS10
  //  0    1    1   → 64分周
  TCCR1B |= (1 << CS11) | (1 << CS10);

  // 比較一致割り込み有効化
  TIMSK1 |= (1 << OCIE1A);

  interrupts();  // 割り込み再開
}

void SevenSegmentDisplay::setNumber(int num) {
  // 表示する数値を設定
  displayValue = num;
  calculateDigitPatterns();
}

void SevenSegmentDisplay::calculateDigitPatterns() {
  // 各桁の数値を計算
  int d[4];
  d[0] = (displayValue / 1000) % 10;
  d[1] = (displayValue / 100) % 10;
  d[2] = (displayValue / 10) % 10;
  d[3] = displayValue % 10;

  bool leadingZero = true;  // 先頭ゼロフラグ

  for (int i = 0; i < 4; i++) {
    // 最下位桁(i=3)以外で、かつ「これまでずっと0」かつ「今の桁も0」なら消灯
    if (i < 3 && leadingZero && d[i] == 0) {
      digitPatterns[i] = 10;  // 全消灯パターン
    } else {
      digitPatterns[i] = d[i];
      leadingZero = false;  // 0以外の数字が出たらフラグ解除
    }
  }
}

void SevenSegmentDisplay::clear() {
  // すべての桁を消灯
  for (int i = 0; i < 4; i++) {
    digitPatterns[i] = 10;  // 消灯パターン
    digitalWrite(DIGIT_PINS[i], HIGH);  // すべての桁をOFF
  }
}

// ========================================
// Timer1割り込みハンドラ（1msごとに自動実行）
// ========================================
void SevenSegmentDisplay::timerISR() {
  if (instance == nullptr) return;  // 安全チェック

  instance->updateDisplay();
}

// ========================================
// 実際の表示更新処理
// ========================================
void SevenSegmentDisplay::updateDisplay() {
  // 前の桁をOFF
  digitalWrite(DIGIT_PINS[currentDigit], HIGH);

  // 次の桁へ移動（0→1→2→3→0→...）
  currentDigit = (currentDigit + 1) % 4;

  // 74HC595にパターンを送信
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, NUM_PATTERNS[digitPatterns[currentDigit]]);
  digitalWrite(LATCH_PIN, HIGH);

  // 新しい桁をON
  digitalWrite(DIGIT_PINS[currentDigit], LOW);
}

// ========================================
// Timer1割り込みベクタ
// ========================================
ISR(TIMER1_COMPA_vect) {
  SevenSegmentDisplay::timerISR();
}
