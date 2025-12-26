#include "Config.h"
#include "UltrasonicSensor.h"
#include "Buzzer.h"
#include "SevenSegmentDisplay.h"

UltrasonicSensor sensor;
Buzzer buzzer;
SevenSegmentDisplay display;

void setup() {
  Serial.begin(9600);

  sensor.begin();
  buzzer.begin();
  display.begin();

  buzzer.beep();  // 起動テスト
  Serial.println("System Ready");
}

void loop() {
  sensor.update();
  int distance = sensor.getDistance();
  buzzer.update(distance);
  display.displayNumber(distance);
}