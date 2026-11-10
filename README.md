# ESP32 + VL53L0X Time-of-Flight Distance Sensor

An Arduino example that reads distance from an ST VL53L0X time-of-flight (ToF) sensor over I2C and prints the result in millimetres, centimetres, metres, and inches. It also assigns a coarse proximity label and reports the sensor's range status.

## Features

- Single-shot distance measurements
- Multiple distance units
- Configurable proximity thresholds
- Basic handling of the library's phase-failure status
- Serial output for bench testing

The advertised range of up to 2 m depends on target reflectivity, ambient light, module optics, and operating conditions. A failed range status does not always mean there is no object; it can also indicate insufficient signal quality or a target outside the useful range.

## Hardware and wiring

| VL53L0X module | ESP32 |
| --- | --- |
| VIN/VCC | 3.3 V for this example; follow the exact breakout documentation |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

The firmware initializes I2C with `Wire.begin(21, 22)`. XSHUT and GPIO1 are not used by this sketch and may be left unconnected for a single-sensor test.

**Voltage warning:** Breakout boards differ. Confirm the module's input-voltage and I2C logic specifications before wiring; do not assume every board is 5 V tolerant.

## Bill of materials

| Item | Qty. | Notes |
| --- | ---: | --- |
| ESP32 development board | 1 | Classic ESP32 pin mapping |
| VL53L0X breakout module | 1 | Confirm the module's voltage requirements |
| Jumper wires | 4 | VCC, GND, SDA, SCL |
| USB data cable | 1 | Upload and Serial Monitor |
| Breadboard | 1, optional | For prototyping |

XSHUT and GPIO1 are optional for the current firmware. Multiple sensors on the same I2C bus require separate XSHUT control and address-management logic, which this sketch does not implement.

## Software setup

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Install ESP32 board support using Espressif's package URL:
   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. Install **Adafruit VL53L0X** through Library Manager and allow its dependencies to install.
4. Open `vL53L0X.ino`.
5. Select the correct ESP32 board and serial port, then compile and upload.
6. Open Serial Monitor at **115200 baud**.

## Configuration

Thresholds are defined near the top of `vL53L0X.ino`:

```cpp
#define DISTANCE_VERY_CLOSE 100
#define DISTANCE_CLOSE      300
#define DISTANCE_MEDIUM     600
#define DISTANCE_FAR       1200
```

Values are in millimetres. Adjust them for your application. The current code treats `RangeStatus != 4` as a usable reading, which is a simplified check; applications requiring robust measurement quality should review the library's status codes and reject all invalid measurement states supported by the installed library version.

## Repository structure

```text
VL53L0X-working-and-test-code-leaser-based-distance-sensor-/
├── README.md               # Setup, wiring, BOM, thresholds, and limitations
├── VL53L0X DATA SHEET.pdf  # Sensor reference document
└── vL53L0X.ino              # Main ESP32 Arduino sketch
```

The sketch remains at the root for direct opening in Arduino IDE. If reorganized later, place it in a directory matching the sketch's primary filename.

## Troubleshooting

| Symptom | Checks |
| --- | --- |
| Sensor not detected | Verify power, ground, SDA GPIO 21, and SCL GPIO 22 |
| Always out of range | Check target distance, angle, reflectivity, and ambient IR |
| Readings jump | Stabilize the target and avoid direct strong sunlight where possible |
| Compile failure | Confirm ESP32 core and Adafruit VL53L0X library versions |

## Skills and technologies

`ESP32` · `Arduino C++` · `I2C` · `Time-of-Flight sensing` · `Distance measurement`

## Maintenance & audit

- **Last updated:** 10 November 2026
- **Review scope:** Checked the sketch name, pin map, threshold definitions, setup instructions, BOM, and repository paths.
- **Documentation changes:** Corrected the sketch path and clarified the scope of range-status handling and multi-sensor limitations.
- **Firmware status:** No firmware change was made; the current status handling needs a deliberate review before use in a safety-relevant application. No compilation or hardware test was run.
- **License:** No `LICENSE` file was found in the current root listing; no specific reuse license is claimed here.
