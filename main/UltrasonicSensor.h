#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>

class UltrasonicSensor {
public:
  void begin();
  void update();
  int getDistance();
  bool isNewDataAvailable();

  static void echoISR();  // 割り込みハンドラ（staticが必要）

private:
  static UltrasonicSensor* instance;  // Singletonパターン

  volatile unsigned long echoStartTime;
  volatile unsigned long echoDuration;
  volatile bool newDistanceAvailable;

  unsigned long lastSensorTriggerTime;
  int currentDistance;
};

#endif