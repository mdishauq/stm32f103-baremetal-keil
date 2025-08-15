# MPU6050 I2C Interface with STM32 / Arduino

## Overview
This project demonstrates interfacing an **MPU6050** (3-axis gyroscope + 3-axis accelerometer) with a microcontroller (STM32 or Arduino) via **I2C communication**. It includes basic initialization, reading sensor data, and troubleshooting tips.

---

## Hardware Required
- MPU6050 module  
- STM32 microcontroller **or** Arduino Uno  
- Jumper wires  
- Breadboard (optional)  
- 3.3V / 5V power supply (depending on module)  

---

## Connections

| MPU6050 Pin | STM32 / Arduino Pin |
|------------|-------------------|
| VCC        | 3.3V / 5V         |
| GND        | GND               |
| SDA        | SDA (STM32 PB7 / Arduino A4) |
| SCL        | SCL (STM32 PB6 / Arduino A5) |

💡 **Note:** GND must be common between MPU6050 and microcontroller.

---

## Software / Code

```c
#include <Wire.h>

#define MPU_ADDR 0x68  // MPU6050 I2C address

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to 0 (wakes up MPU6050)
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting register for accelerometer data
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  int16_t AcX = Wire.read() << 8 | Wire.read();
  int16_t AcY = Wire.read() << 8 | Wire.read();
  int16_t AcZ = Wire.read() << 8 | Wire.read();

  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.println(AcZ);

  delay(500);
}
