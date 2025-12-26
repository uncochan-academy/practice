#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ========================================
// ピン定義
// ========================================

// 超音波センサー（HC-SR04）
const int TRIG_PIN = 9;
const int ECHO_PIN = 2;  // 割り込み対応ピン

// ブザー
const int BUZZER_PIN = 6;

// 7セグメントディスプレイ（74HC595シフトレジスタ方式）
const int LATCH_PIN = 10;
const int CLOCK_PIN = 13;
const int DATA_PIN = 11;
const int DIGIT_PINS[] = {8, 3, 4, 5};  // 4桁の制御ピン

// ========================================
// ハードウェア定数
// ========================================

// === センサーステータス定義 ===
enum SensorStatus {
  STATUS_OUT_OF_RANGE = -1,    // 測定範囲外（400cm超過または1cm未満）
  STATUS_NO_ECHO = -2,         // エコー応答なし（将来の拡張用）
  STATUS_TIMEOUT = -3          // タイムアウト（将来の拡張用）
};

// センサー測定間隔（ミリ秒）
const int SENSOR_INTERVAL = 150;

// 正常な距離の範囲
const int MAX_DISTANCE_CM = 400;
const int MIN_DISTANCE_CM = 1;  // 0cmはエラーとする

// 7セグメント数字パターン（0-9と消灯）
const byte NUM_PATTERNS[] = {
  0x3F,  // 0
  0x06,  // 1
  0x5B,  // 2
  0x4F,  // 3
  0x66,  // 4
  0x6D,  // 5
  0x7D,  // 6
  0x07,  // 7
  0x7F,  // 8
  0x6F,  // 9
  0x00   // 消灯（インデックス10）
};

#endif