#include "UltrasonicSensor.h"
#include "Config.h"

// Singletonインスタンス（static関数から非staticメンバにアクセスするため）
UltrasonicSensor* UltrasonicSensor::instance = nullptr;

void UltrasonicSensor::begin() {
  instance = this;  // Singleton登録

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  echoStartTime = 0;
  echoDuration = 0;
  newDistanceAvailable = false;
  lastSensorTriggerTime = 0;
  currentDistance = 0;

  // 割り込みの設定
  // ECHO_PINの電圧が変わるたび(CHANGE)、echoISRを自動実行
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), echoISR, CHANGE);
}

void UltrasonicSensor::update() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastSensorTriggerTime >= SENSOR_INTERVAL) {
    lastSensorTriggerTime = currentMillis;

    // 超音波を発射
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // 超音波が返ってくるのを待たずに次の処理へ進む
    // 受信の計算はechoISR関数で行われる
  }

  // 割り込みで計算されたデータを取得
  if (newDistanceAvailable) {
    noInterrupts();  // データ読み取り中に割り込みが入らないよう一時停止
    unsigned long d = echoDuration;
    newDistanceAvailable = false;
    interrupts();  // 再開

    // 距離計算
    int dist = d * 0.034 / 2;
    if (dist > 400 || dist <= 0) dist = 999;  // 範囲外処理
    currentDistance = dist;
  }
}

int UltrasonicSensor::getDistance() {
  return currentDistance;
}

bool UltrasonicSensor::isNewDataAvailable() {
  return newDistanceAvailable;
}

void UltrasonicSensor::echoISR() {
  if (instance == nullptr) return;  // 安全チェック

  // ピンの状態を読む
  if (digitalRead(ECHO_PIN) == HIGH) {
    // HIGHになった瞬間（音が返ってきたスタート）
    instance->echoStartTime = micros();
  } else {
    // LOWになった瞬間（音が終わり）
    // 差分を計算して保存
    instance->echoDuration = micros() - instance->echoStartTime;
    instance->newDistanceAvailable = true;
  }
}