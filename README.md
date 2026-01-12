# Arduino Software Development Practice Project

## Project Purpose

This is a development practice project to gain broad, full-stack knowledge for coordinating software development at work.

## Current Status

### Hardware

- Elegoo Uno R3
- 4-digit 7-segment display
- 74HC595 shift register
- HC-SR04 ultrasonic sensor

### Source Code

#### tool\arduino_serial_monitor

- Created a tool to display the serial monitor. The code is hardcoded and messy.

#### main\main.ino

- Created a project using Arduino that measures distance with an ultrasonic sensor and displays it on an active buzzer and 4-digit 7-segment display.
- Data layer: Raw data
- Business logic layer: Data validation checks
- Presentation layer: UI processing for 7-segment display and buzzer

### Development Environment

- Arduino IDE

## Failures

### Issues

1. Output interfaces such as the display did not work properly.
2. Switches did not work properly.
3. Ultrasonic wave cycle drifted and picked up old sounds, resulting in incorrect distance measurements (hypothesis, unresolved).
4. Digital display switches too fast and is hard to read (unresolved).

### Causes and Improvements

1. Processing was stopped while waiting for sensor information to return.
   - Don't use delay.
   - Defer processing.
   - Used special pins.
2. Physical issue where switches rapidly turned on/off.
   - Group on/off events within a few seconds into a single input.

### Understanding Level

1. Interrupt control
   - Understanding: ☆★★★★
2. Chattering countermeasures
   - Understanding: ☆★★★★


## Future Plans

### To Do

#### Features to Add

- Add timestamps to distance data.
- Tool to analyze obtained data with graphs.
- Conditional compilation for flexible hardware adaptation.
- Separate high-level presentation layer from low-level data layer.
  This means separating accurate raw data for logging/analysis from UI-optimized smoothed data.
- Control whether to display debug serial monitor with conditional compilation.

#### Study Topics

- Enable environment changes according to development stage.
   - Migrate from Arduino IDE to Arduino CLI, PlatformIO,

     CMake, Makefiles to customize build system.
   - Conditional compilation.
   - How to set up CI.
- Understand architecture design.
   - Modularization to easily adapt to hardware and peripheral changes.
   - Abstraction and layering.

   - Considered implementing proper layers, but might keep it lightweight.
   - Want to try implementing Observer pattern.

### Check

- Record what failed and why regarding environment setup and development methods according to development stages.
