# Holiday-Lights-Knight-Rider
#  8-LED Programmable Holiday Light Array

An embedded systems project featuring a dynamic 8-LED hardware array controlled by an Elegoo UNO R3 microcontroller. The system cycles through 5 custom programmable animation sequences using a debounced hardware pushbutton, with real-time speed control modulated via an analog potentiometer.

##  Features & Embedded Software Concepts

* **Multi-Variable State Machine:** Uses C++ logic to smoothly cycle through 5 distinct animation states (including a randomized `sparkleMode()` and an overlapping `collisionMode()`) without resetting the active circuit.
* **Hardware Debouncing:** Implements custom software debouncing logic (`lastButtonState`) to filter electrical noise from the mechanical pushbutton, ensuring accurate state changes.
* **Non-Blocking Control Architecture:** Developed optimized loops to manage timing sequences dynamically, ensuring responsive input reading from the physical hardware components.
* **Analog-to-Digital Interface:** Reads variable voltage inputs from a 10k Ohm potentiometer to scale the timing intervals of the LED animations on the fly.

##  Hardware Components
* **Microcontroller:** Elegoo Uno R3 (Arduino architecture)
* **Display Array:** 8x LEDs mapped across sequential digital output pins
* **Current Limiting:** 8x 220 Ohm resistors (protecting individual diode channels)
* **Inputs:** 1x 10k Ohm Potentiometer, 1x Tactile Pushbutton, 1x 10k Ohm pull-down resistor
* **Power:** 9V Battery / USB bus power

## 📁 Repository Structure
* `src/` — Core C++ firmware file containing the animation functions, debouncing logic, and pin mappings.
