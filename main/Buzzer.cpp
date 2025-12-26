#include "Buzzer.h"
#include "Config.h"

void Buzzer::begin() {
  pinMode(BUZZER_PIN, OUTPUT);
  lastBuzzerStartTime = 0;
  isBuzzerOn = false;
}

void Buzzer::update(int distance) {
  unsigned long currentMillis = millis();

  // ブザー制御セクション
  // 100cm以内に入ったら鳴らし始める
  if (distance > 0 && distance < 100) {

    // 距離2cm〜100cmに対して、間隔を50ms〜800msへ変化
    int interval = map(distance, 2, 100, 50, 800);

    if (!isBuzzerOn) {
      // 待ち時間が経過したら音を出す
      if (currentMillis - lastBuzzerStartTime >= interval) {
        digitalWrite(BUZZER_PIN, HIGH);
        lastBuzzerStartTime = currentMillis;
        isBuzzerOn = true;
      }
    } else {
      // 音を出して20ms経ったら止める
      if (currentMillis - lastBuzzerStartTime >= 20) {
        digitalWrite(BUZZER_PIN, LOW);
        isBuzzerOn = false;
      }
    }
  } else {
    // 範囲外なら音を消す
    digitalWrite(BUZZER_PIN, LOW);
    isBuzzerOn = false;
  }
}

void Buzzer::beep() {
  // 起動時のテスト用ビープ音
  digitalWrite(BUZZER_PIN, HIGH);
  delay(20);
  digitalWrite(BUZZER_PIN, LOW);
}