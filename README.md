# 💡 Smart Street Light System

An Arduino-based **Smart Street Light System** that automatically controls street-light intensity according to **ambient light conditions and vehicle/person movement**.

The system uses an **LDR sensor** to determine whether it is daytime or nighttime. During low-light conditions, six IR sensors detect movement near individual street-light sections. The corresponding LEDs increase their brightness when motion is detected and remain dim when no movement is present.

A **16×2 LCD** provides real-time information about the operating condition, while the Serial Monitor displays sensor readings for monitoring and debugging.

---

## 🚀 Features

* 🌙 **Automatic Day/Night Detection**

  * Uses an LDR sensor to measure ambient light.
  * Automatically switches the street lights OFF during daylight.
  * Activates smart lighting control during low-light conditions.

* 🚶 **Motion Detection**

  * Uses six independent IR sensors.
  * Each IR sensor controls a corresponding street-light section.
  * Detects movement near individual lights.

* 💡 **Automatic Light Brightness Control**

  * Lights operate at reduced brightness when no movement is detected.
  * Lights switch to full brightness when movement is detected.
  * Helps reduce unnecessary power consumption.

* 🖥️ **LCD Status Display**

  * Displays whether the system is operating during daytime or nighttime.
  * Shows whether motion is detected.
  * Indicates whether lights are OFF, DIM, or ON.

* 📊 **Serial Monitoring**

  * Displays the LDR sensor value.
  * Displays the state of all six IR sensors.
  * Useful for testing and calibration.

---

## 🧰 Hardware Requirements

| Component       |    Quantity |
| --------------- | ----------: |
| Arduino Uno     |           1 |
| LDR Sensor      |           1 |
| IR Sensors      |           6 |
| LEDs            |           6 |
| 220Ω Resistors  |           6 |
| 16×2 LCD        |           1 |
| Breadboard      |           1 |
| Jumper Wires    | As required |
| 5V Power Supply |           1 |

---

## 🔌 Pin Connections

The following connections match the uploaded Arduino code.

### LDR Sensor

| Component | Pin           | Arduino Uno |
| --------- | ------------- | ----------- |
| LDR       | Analog Output | **A0**      |

The LDR value is read using:

```cpp
const int ldrPin = A0;
```

---

### IR Sensors

Six IR sensors are used to monitor movement.

| IR Sensor   | Arduino Pin |
| ----------- | ----------: |
| IR Sensor 1 |          D8 |
| IR Sensor 2 |          D9 |
| IR Sensor 3 |         D10 |
| IR Sensor 4 |         D11 |
| IR Sensor 5 |         D12 |
| IR Sensor 6 |         D13 |

The corresponding code is:

```cpp
const int irPin1 = 8;
const int irPin2 = 9;
const int irPin3 = 10;
const int irPin4 = 11;
const int irPin5 = 12;
const int irPin6 = 13;
```

For typical IR modules:

```text
VCC → 5V
GND → GND
OUT → Arduino digital pin
```

---

## 💡 LED Connections

Each IR sensor is associated with one LED.

| Street Light | LED Pin | IR Sensor |
| ------------ | ------: | --------: |
| LED 1        |      D7 |      IR 1 |
| LED 2        |      D6 |      IR 2 |
| LED 3        |      D5 |      IR 3 |
| LED 4        |      D4 |      IR 4 |
| LED 5        |      D3 |      IR 5 |
| LED 6        |      D2 |      IR 6 |

The code defines:

```cpp
const int ledPin1 = 7;
const int ledPin2 = 6;
const int ledPin3 = 5;
const int ledPin4 = 4;
const int ledPin5 = 3;
const int ledPin6 = 2;
```

Each LED should use an appropriate current-limiting resistor.

```text
Arduino Pin ─── 220Ω ─── LED Anode (+)
LED Cathode (−) ──────── GND
```

> **Important:** The Arduino pins should not directly drive high-power street-light lamps. For a real street-light installation, use suitable transistor/MOSFET drivers or relay/contactor circuits designed for the lamp's voltage and current.

---

## 🖥️ LCD Connection

The project uses:

```cpp
#include <Adafruit_LiquidCrystal.h>
```

and initializes the LCD using:

```cpp
Adafruit_LiquidCrystal lcd(0);
```

The LCD is therefore controlled through the `Adafruit_LiquidCrystal` interface rather than manually assigning the usual parallel LCD pins in the sketch.

For an **I²C-compatible Adafruit LCD setup**, connect the module according to the specific backpack/module being used.

Typical I²C connections are:

| LCD | Arduino Uno |
| --- | ----------- |
| VCC | 5V          |
| GND | GND         |
| SDA | A4          |
| SCL | A5          |

> Verify the exact LCD backpack/module before wiring, because `Adafruit_LiquidCrystal` can support different interface configurations.

---

## 🧠 System Architecture

```text
                     ┌─────────────────┐
                     │    LDR Sensor   │
                     │ Ambient Light   │
                     └────────┬────────┘
                              │
                              ▼
                     ┌─────────────────┐
                     │   Arduino UNO   │
                     │                 │
                     │ Day/Night Logic │
                     │ Motion Logic    │
                     │ Light Control   │
                     └───────┬─────────┘
                             │
            ┌────────────────┼────────────────┐
            │                │                │
            ▼                ▼                ▼
       IR Sensors        LED Control       16×2 LCD
       IR1 → IR6         LED1 → LED6       Status
            │                │
            └────────────────┘
                     │
                     ▼
              Smart Street
               Lighting
```

---

# ⚙️ How the System Works

The system continuously monitors the LDR and six IR sensors.

The basic operating sequence is:

```text
              START
                │
                ▼
          Read LDR Value
                │
                ▼
       Is it Low Light?
          /          \
        YES           NO
         │             │
         ▼             ▼
   Read IR Sensors   LEDs OFF
         │             │
         ▼             ▼
 Motion Detected?   DAYTIME
      /     \       LIGHTS OFF
    YES      NO
     │        │
     ▼        ▼
 Full Light  Dim Light
     │        │
     └────┬───┘
          ▼
      LCD Status
          │
          ▼
     Repeat Process
```

---

## 🌞 Daylight Mode

The system uses the following threshold:

```cpp
const int ldrThreshold = 550;
```

The LDR value is read using:

```cpp
ldrValue = analogRead(ldrPin);
```

When:

```text
LDR Value ≥ 550
```

the system considers the environment to be sufficiently bright.

All LEDs are turned OFF:

```cpp
digitalWrite(ledPin1, LOW);
analogWrite(ledPin2, 0);
analogWrite(ledPin3, 0);
digitalWrite(ledPin4, LOW);
analogWrite(ledPin5, 0);
digitalWrite(ledPin6, LOW);
```

The LCD displays:

```text
DAYTIME
LIGHTS OFF
```

---

## 🌙 Night / Low-Light Mode

When:

```text
LDR Value < 550
```

the system enters nighttime/low-light operation.

The six IR sensors are then used to determine whether movement is present near each lighting section.

```text
LDR < 550
   │
   ▼
LOW LIGHT
   │
   ├── Read IR1 → Control LED1
   ├── Read IR2 → Control LED2
   ├── Read IR3 → Control LED3
   ├── Read IR4 → Control LED4
   ├── Read IR5 → Control LED5
   └── Read IR6 → Control LED6
```

---

# 🚶 Motion-Based Lighting

Each IR sensor controls its corresponding light.

### LED 1

```cpp
if (irState1 == HIGH)
{
    digitalWrite(ledPin1, HIGH);
}
else
{
    digitalWrite(ledPin1, LOW);
}
```

When IR1 detects the configured sensor state, LED1 turns ON.

---

### LED 2

LED2 uses PWM:

```cpp
if (irState2 == HIGH)
{
    analogWrite(ledPin2, 255);
}
else
{
    analogWrite(ledPin2, 50);
}
```

Therefore:

```text
Motion detected → 255 → Full brightness
No motion       → 50  → Dim brightness
```

---

### LED 3

LED3 operates in the same PWM-based manner:

```cpp
if (irState3 == HIGH)
{
    analogWrite(ledPin3, 255);
}
else
{
    analogWrite(ledPin3, 50);
}
```

---

### LED 4

LED4 uses digital ON/OFF control:

```cpp
if (irState4 == HIGH)
{
    digitalWrite(ledPin4, HIGH);
}
else
{
    digitalWrite(ledPin4, LOW);
}
```

---

### LED 5

LED5 uses PWM brightness control:

```cpp
if (irState5 == HIGH)
{
    analogWrite(ledPin5, 255);
}
else
{
    analogWrite(ledPin5, 50);
}
```

---

### LED 6

LED6 uses digital ON/OFF control:

```cpp
if (irState6 == HIGH)
{
    digitalWrite(ledPin6, HIGH);
}
else
{
    digitalWrite(ledPin6, LOW);
}
```

> **Implementation note:** In the current code, LEDs 2, 3, and 5 have dim-mode PWM control, while LEDs 1, 4, and 6 use digital ON/OFF control. If you want identical dim/full-bright behavior for all six lights, those three digital-controlled outputs would need to be changed to PWM-capable pins.

---

# 💡 Light Control Logic

The intended smart-lighting concept is:

```text
                  NIGHT
                    │
                    ▼
             IR Sensor Check
                    │
          ┌─────────┴─────────┐
          │                   │
      Motion              No Motion
          │                   │
          ▼                   ▼
    Full Brightness       Dim Light
```

This reduces unnecessary illumination when there is no movement while still providing stronger lighting when movement is detected.

---

# 🖥️ LCD Status Display

The LCD provides two-line status information.

### Motion Detected

When any of the six IR sensors detects the configured motion state:

```text
MOTION DETECTED
LIGHTS ON
```

The program uses:

```cpp
lcd.setCursor(0, 0);
lcd.print("MOTION DETECTED");

lcd.setCursor(0, 1);
lcd.print("LIGHTS ON");
```

---

### No Motion

When no motion is detected:

```text
NO MOTION
DIM LIGHT
```

---

### Daytime

During daylight:

```text
DAYTIME
LIGHTS OFF
```

---

# 📊 Serial Monitor

The Serial Monitor operates at:

```cpp
Serial.begin(9600);
```

The LDR value is displayed continuously:

```text
LDR Value: 420
```

The six IR sensor states are also displayed:

```text
IR1: 0 IR2: 1 IR3: 0 IR4: 0 IR5: 0 IR6: 1
```

This makes it easier to test the system and determine whether the sensors are producing the expected HIGH/LOW signals.

---

# ⚙️ Configurable Parameters

The main threshold can be modified here:

```cpp
const int ldrThreshold = 550;
```

### LDR Threshold

```text
LDR < 550
→ Low-light / night mode

LDR ≥ 550
→ Daylight mode
```

The exact threshold depends on:

* LDR type
* Resistor value
* Ambient lighting
* Sensor placement
* Local environmental conditions

It is recommended to determine the threshold experimentally using the Serial Monitor.

---

# 🔄 System Operating Modes

| Condition         | LED Behavior                            | LCD                           |
| ----------------- | --------------------------------------- | ----------------------------- |
| Daylight          | All OFF                                 | `DAYTIME / LIGHTS OFF`        |
| Night + No Motion | Dim where PWM is implemented            | `NO MOTION / DIM LIGHT`       |
| Night + Motion    | Corresponding lights ON/full brightness | `MOTION DETECTED / LIGHTS ON` |

---

# 📦 Required Library

The project uses:

```cpp
#include <Adafruit_LiquidCrystal.h>
```

Install the **Adafruit LiquidCrystal** library through the Arduino IDE Library Manager if it is not already installed.

---

# 📥 Installation

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/your-repository.git
```

### 2. Open the Arduino Project

Open:

```text
smart-street-light-system.ino
```

using Arduino IDE.

### 3. Install the LCD Library

In Arduino IDE:

```text
Tools → Manage Libraries
```

Search for:

```text
Adafruit LiquidCrystal
```

and install the required library.

### 4. Connect the Hardware

Connect the LDR, six IR sensors, six LEDs, and LCD according to the connection tables.

### 5. Select the Board

```text
Board → Arduino Uno
Port  → Your Arduino COM Port
```

### 6. Upload the Program

Upload the program to the Arduino Uno.

### 7. Open Serial Monitor

Set the baud rate to:

```text
9600
```

Observe the LDR and IR sensor readings.

---

# 🧪 Testing Procedure

### Test 1 — LDR

1. Power on the Arduino.
2. Open the Serial Monitor.
3. Observe the LDR value.
4. Cover or illuminate the LDR.
5. Verify that the system changes between daylight and low-light modes.

### Test 2 — IR Sensors

1. Place the system in low-light mode.
2. Trigger each IR sensor individually.
3. Verify that its corresponding LED changes state.
4. Check the Serial Monitor for the IR sensor value.

### Test 3 — LCD

Verify that the LCD displays:

```text
DAYTIME
LIGHTS OFF
```

during daylight.

During low light with no motion:

```text
NO MOTION
DIM LIGHT
```

During detected motion:

```text
MOTION DETECTED
LIGHTS ON
```

---

# ⚠️ Important Hardware Considerations

The LEDs shown in this prototype should not be replaced directly with high-power street lamps.

For a real street-light implementation, use appropriate driver circuitry such as:

* MOSFET driver
* Transistor driver
* Relay module
* Contactor for higher-power AC loads
* Proper isolated power supply

For high-power lighting, the Arduino should only provide the **control signal**, while the driver circuit handles the actual lamp current.

Also ensure that each small LED has an appropriate current-limiting resistor.

---

# 🏙️ Real-World Application

The concept can be adapted for:

* Residential streets
* Campus roads
* Parking areas
* Industrial areas
* Smart-city infrastructure
* Pedestrian pathways
* Rural roads
* Railway/industrial access roads

The same architecture can be scaled by replacing the prototype LEDs with suitable power-lighting drivers.

---

# 🔮 Future Improvements

Possible upgrades include:

* 📡 ESP8266/ESP32 Wi-Fi connectivity
* 📱 Mobile application
* ☁️ Cloud-based monitoring
* 📊 Energy-consumption monitoring
* 🌞 Solar-powered street lights
* 🔋 Battery and charge-controller monitoring
* 🌧️ Weather sensors
* 💡 Automatic PWM brightness control for every light
* 🌐 IoT-based centralized control
* 📈 Energy-saving statistics
* 🚨 Fault detection for individual street lights
* 🌙 Adaptive brightness based on ambient light
* 📷 Camera-based vehicle detection
* 🚗 Vehicle counting and traffic-density detection

---

# 🧠 Complete System Architecture

```text
                         ┌───────────────┐
                         │   LDR Sensor  │
                         └───────┬───────┘
                                 │
                                 ▼
                       ┌──────────────────┐
                       │    Arduino UNO   │
                       │                  │
                       │ Light Detection  │
                       │ Motion Detection │
                       │ LED Control      │
                       └────────┬─────────┘
                                │
          ┌─────────────────────┼─────────────────────┐
          │                     │                     │
          ▼                     ▼                     ▼
     IR Sensor 1           IR Sensor 2          IR Sensor 3
          │                     │                     │
          ▼                     ▼                     ▼
        LED 1                 LED 2                 LED 3

          ┌─────────────────────┼─────────────────────┐
          │                     │                     │
          ▼                     ▼                     ▼
     IR Sensor 4           IR Sensor 5          IR Sensor 6
          │                     │                     │
          ▼                     ▼                     ▼
        LED 4                 LED 5                 LED 6

                                │
                                ▼
                         ┌───────────────┐
                         │    16×2 LCD   │
                         │ System Status │
                         └───────────────┘
```

---

# 🎯 Project Objective

The objective of this project is to develop an **automatic and energy-conscious street-lighting system** that responds to both environmental lighting and movement.

Instead of operating all lights at full brightness continuously, the system uses an LDR to determine when artificial lighting is required and IR sensors to identify movement near individual lighting sections.

---

# 👨‍💻 Project Overview

The **Smart Street Light System** demonstrates the integration of **ambient-light sensing, motion detection, automatic LED control, PWM brightness control, and LCD-based status monitoring** using an Arduino.

The prototype provides a foundation for developing larger smart-city lighting systems where lighting can dynamically respond to environmental conditions and road or pedestrian activity while reducing unnecessary energy usage.

