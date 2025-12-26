# Arduino Software Development Practice Project

## Project Purpose

This is a development practice project to gain broad knowledge across the full stack for coordinating software development at work.

## Current Status

### Hardware

- elegoo uno r3
- Other peripheral components

### Source Code

#### toool\arduino_serial_monitor

- Created a tool to display the serial monitor. The code is hardcoded and messy.

#### arduino\main.ino

- Created a project using Arduino that measures distance with an ultrasonic sensor and displays it on an active buzzer and 4-digit 7-segment display.

### Development Environment

- Arduino IDE

## Failures

### Issues

1. Output interfaces such as the display did not work properly.
2. Switches did not work properly.

### Causes and Improvements

1. Processing was stopped while waiting for sensor information to return.
   - Don't use delay.
   - Defer processing.
   - Used special pins (interrupts).
2. Physical issue where switches rapidly turned on/off (chattering).
   - Group on/off events within a few seconds into a single input.

### Understanding Level

1. Interrupt control
   - Understanding: ☆★★★★
2. Chattering countermeasures
   - Understanding: ☆★★★★


## Future Plans

### To Do

#### Software

- Enable environment changes according to development stage.
   - Gradually move away from integrated development environment
   - Set up CI
- Learn to design architecture.
   - Modularization to easily adapt to hardware and peripheral changes
   - Abstraction and layering.


### Check

- Record what failed and why regarding environment setup and development methods according to development stages.
