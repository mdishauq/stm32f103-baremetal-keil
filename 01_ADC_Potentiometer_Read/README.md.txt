# 01 - ADC Potentiometer Read (Bare-Metal STM32F103C8T6)

## Description
Reads an analog voltage from a potentiometer using ADC1 (bare-metal register programming) and outputs the value via UART or debugging.

## Hardware
- STM32F103C8T6 "Blue Pill"
- Potentiometer (10kΩ)
- Jumper wires
- ST-Link V2 or USB-to-Serial

## Pinout
- Potentiometer Vcc → 3.3V
- Potentiometer GND → GND
- Potentiometer Output → PA0 (ADC Channel 0)

## Build & Run
- Open `Keil_Project/ADC_testing.uvprojx` in Keil
- Build and flash to the Blue Pill
- Observe ADC values via debugger or UART

