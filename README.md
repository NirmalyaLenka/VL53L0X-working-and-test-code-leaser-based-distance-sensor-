# VL53L0X-working-and-test-code-leaser-based-distance-sensor-
# ESP32 + VL53L0X Time-of-Flight Distance Sensor

Measure precise distances from 30 mm up to 2000 mm using the VL53L0X Time-of-Flight laser ranging sensor with an ESP32 microcontroller. The sensor outputs distance in millimeters, centimeters, meters, and inches, and classifies the proximity zone of the detected object.

---

## Components Required

| Component | Quantity |
|-----------|----------|
| ESP32 Dev Board | 1 |
| VL53L0X Sensor Module | 1 |
| Jumper Wires | 4 |
| Breadboard (optional) | 1 |

---

## Wiring Diagram

```
VL53L0X         ESP32
-------         -----
VCC    -------> 3.3V
GND    -------> GND
SDA    -------> GPIO 21
SCL    -------> GPIO 22
XSHUT  -------> GPIO 4   (optional - for hardware reset)
GPIO1  -------> GPIO 5   (optional - for interrupt mode)
```

The XSHUT and GPIO1 pins are optional. If you are using only one sensor, you can leave them unconnected. XSHUT is used to reset the sensor or manage multiple sensors on the same I2C bus by enabling them one at a time.

---

## Setup and Installation

### 1. Install Arduino IDE

Download from https://www.arduino.cc/en/software

### 2. Add ESP32 Board Support

1. Open Arduino IDE and go to File > Preferences
2. Add the following URL to Additional Boards Manager URLs:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to Tools > Board > Boards Manager
4. Search for esp32 and click Install

### 3. Install Required Library

1. Go to Sketch > Include Library > Manage Libraries
2. Search for Adafruit VL53L0X
3. Install "Adafruit VL53L0X" by Adafruit
4. Also install "Adafruit BusIO" if prompted as a dependency

### 4. Upload the Sketch

1. Open vl53l0x_esp32.ino in Arduino IDE
2. Select your board: Tools > Board > ESP32 Dev Module
3. Select the correct port: Tools > Port
4. Click Upload

---

## Serial Monitor Output

Open Serial Monitor at 115200 baud to see live readings.

```
=================================
  ESP32 + VL53L0X Sensor Demo
=================================
VL53L0X initialized successfully.
Sensor Mode : Single Ranging
I2C Address : 0x29 (default)
---------------------------------

--- VL53L0X Readings ---
Distance    : 243 mm
            : 24.3 cm
            : 0.243 m
            : 9.57 inches
Proximity   : CLOSE       (< 30 cm)
Range Status: OK (0)
------------------------

--- VL53L0X Readings ---
Distance    : OUT OF RANGE
Proximity   : No object detected
Range Status: Phase failure (4) - target too far or absent
------------------------
```

---

## Configuration

### Distance Thresholds

Adjust these values in the code to match your use case:

```cpp
#define DISTANCE_VERY_CLOSE   100   // Less than 10 cm
#define DISTANCE_CLOSE        300   // Less than 30 cm
#define DISTANCE_MEDIUM       600   // Less than 60 cm
#define DISTANCE_FAR         1200   // Less than 120 cm
```

### Range Status Codes

| Status Code | Meaning |
|-------------|---------|
| 0 | Valid measurement |
| 1 | Sigma failure - low signal quality |
| 2 | Signal failure - target too reflective |
| 4 | Phase failure - out of range or no target |

---

## Features

| Feature | Description |
|---------|-------------|
| Multi-unit Output | Distance in mm, cm, m, and inches |
| Proximity Label | Classifies distance zone (Very Close to Very Far) |
| Range Status | Reports sensor measurement quality |
| Out of Range Handling | Detects and reports when no target is present |
| I2C Interface | Simple 2-wire connection on GPIO 21 and 22 |

---

## Possible Projects Using This Sensor

The VL53L0X is a high-accuracy, compact distance sensor suited for projects where ultrasonic sensors are too slow or too large.


### Beginner

**Smart Dustbin Lid**
Detect when a hand approaches within 10 cm and trigger a servo motor to open the bin lid automatically. The lid closes after a set delay once the hand is removed.

**Liquid Level Monitor**
Mount the sensor above a water tank or container facing downward. Calculate the liquid level by subtracting the measured distance from the known tank height. Send alerts when the level drops below a threshold.

**Touchless Button**
Replace a physical push button with the VL53L0X. When a finger is detected within a set distance, register it as a button press. Useful for hygiene-sensitive environments.

**Proximity-Based Screen Dimmer**
Connect the ESP32 to a display. When no one is within 50 cm, dim or turn off the screen. When someone approaches, wake it up instantly.


### Intermediate

**Obstacle-Avoiding Robot**
Mount the sensor on a robot car facing forward. When an obstacle is detected under 20 cm, stop the motors, turn, and continue. ToF provides faster and more accurate readings than ultrasonic sensors.

**People Counter with Height Filter**
Mount the sensor at a doorway facing downward from a fixed height. Measure the distance to passing people versus the empty floor distance to count entries. The height difference helps filter out small objects.

**Stair Safety Alert for the Elderly**
Place the sensor near the top of a staircase. If a person steps too close to the edge without the handrail being gripped (combined with another sensor), trigger a buzzer or alert.

**Drone Landing Assistance**
Use the VL53L0X on the underside of a small drone to measure altitude from the ground during landing. Feed data to the flight controller for a controlled, soft touchdown.


### Advanced

**Gesture Recognition System**
Read distance values at high frequency and analyze the speed and direction of hand movements. Classify gestures such as swipe left, swipe right, push, and pull to control devices wirelessly.

**1D Scanner or Profiler**
Mount the sensor on a servo motor. Rotate the servo in small steps and record distance at each angle. Plot the data to build a basic 2D profile or map of the surrounding environment.

**Multi-Sensor Array for Object Shape Detection**
Wire multiple VL53L0X sensors on the same I2C bus using XSHUT pins to enable them one at a time with different I2C addresses. Measure distance at multiple points simultaneously to detect the rough shape or width of objects passing by.

**Industrial Part Presence Verification**
On a production line, mount the sensor at a fixed point and measure distance to a reference surface. If a part is correctly placed, the distance changes by a predictable amount. Trigger a pass or fail output accordingly.

---

## Troubleshooting

| Problem | Solution |
|---------|----------|
| Sensor not found on startup | Check SDA on GPIO 21 and SCL on GPIO 22; verify 3.3V power |
| Always reads OUT OF RANGE | Target surface may be too dark, angled, or beyond 2000 mm |
| Unstable or jumping readings | Reduce ambient IR interference; avoid direct sunlight on sensor |
| Multiple sensors not working | Use XSHUT to enable sensors one at a time and assign unique I2C addresses |
| Board not detected by PC | Install CP210x or CH340 USB driver for your ESP32 board |

---

## Project Structure

```
esp32-vl53l0x/
|
|-- vl53l0x_esp32.ino   # Main Arduino sketch
|-- README.md           # This file
```

---

## Resources

- Adafruit VL53L0X Library: https://github.com/adafruit/Adafruit_VL53L0X
- VL53L0X Datasheet: https://www.st.com/resource/en/datasheet/vl53l0x.pdf
- ESP32 I2C Reference: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/i2c.html

---

## License

This project is open source and available under the MIT License.

---

## Contributing

Pull requests are welcome. Feel free to open an issue for bugs, improvements, or new project ideas.

---

## Topics

esp32  vl53l0x  time-of-flight  tof  distance-sensor  laser  i2c  arduino  iot  embedded  robotics

---

## How It Works

The VL53L0X uses Time-of-Flight (ToF) technology to measure distance. Internally, the sensor contains a 940 nm infrared VCSEL laser emitter and a SPAD (Single Photon Avalanche Diode) array receiver built into a single compact module by STMicroelectronics.

When a measurement is triggered, the laser emits a very short pulse of infrared light. This pulse travels through the air, strikes the target surface, and reflects back toward the sensor. The SPAD array detects the returning photons and the internal processing unit measures the exact time elapsed between emission and reception. Since the speed of light is a known constant, the sensor calculates distance using the formula:

```
Distance = (Speed of Light x Time of Flight) / 2
```

The division by 2 accounts for the round trip the light pulse makes. This entire process happens in microseconds and is repeated many times per measurement cycle to average out noise and improve accuracy.

Unlike ultrasonic sensors that emit broad sound waves and are affected by temperature and humidity, the VL53L0X laser beam is narrow and precise, giving it accurate readings on small targets and at faster update rates. The sensor communicates the final distance value over the I2C bus to the ESP32, which reads it using the Adafruit VL53L0X library.

The typical measurement range is 30 mm to 2000 mm, with accuracy of plus or minus 3 percent under normal indoor conditions. Performance can vary based on the reflectivity and color of the target surface, ambient light levels, and the angle at which the beam strikes the object.
