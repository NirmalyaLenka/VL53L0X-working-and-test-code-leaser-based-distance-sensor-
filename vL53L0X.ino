#include <Wire.h>
#include <Adafruit_VL53L0X.h>

// Create VL53L0X object
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// Distance thresholds in millimeters
#define DISTANCE_VERY_CLOSE   100   // Less than 10 cm
#define DISTANCE_CLOSE        300   // Less than 30 cm
#define DISTANCE_MEDIUM       600   // Less than 60 cm
#define DISTANCE_FAR          1200  // Less than 120 cm
// Above 1200 mm = Out of range / Very far

// Out of range value returned by sensor
#define OUT_OF_RANGE_VALUE    8190

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize I2C
  Wire.begin(21, 22);

  Serial.println("=================================");
  Serial.println("  ESP32 + VL53L0X Sensor Demo    ");
  Serial.println("=================================");

  // Initialize VL53L0X
  if (!lox.begin()) {
    Serial.println("ERROR: VL53L0X sensor not found!");
    Serial.println("Check wiring:");
    Serial.println("  VCC -> 3.3V");
    Serial.println("  GND -> GND");
    Serial.println("  SDA -> GPIO 21");
    Serial.println("  SCL -> GPIO 22");
    while (1) { delay(1000); }
  }

  Serial.println("VL53L0X initialized successfully.");
  Serial.println("Sensor Mode : Single Ranging");
  Serial.println("I2C Address : 0x29 (default)");
  Serial.println("---------------------------------");
  Serial.println();
}

String getProximityLabel(uint16_t mm) {
  if (mm < DISTANCE_VERY_CLOSE) return "VERY CLOSE  (< 10 cm)";
  else if (mm < DISTANCE_CLOSE)  return "CLOSE       (< 30 cm)";
  else if (mm < DISTANCE_MEDIUM) return "MEDIUM      (< 60 cm)";
  else if (mm < DISTANCE_FAR)    return "FAR         (< 120 cm)";
  else                           return "VERY FAR    (> 120 cm)";
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  // Perform a single ranging measurement
  lox.rangingTest(&measure, false);

  Serial.println("--- VL53L0X Readings ---");

  if (measure.RangeStatus != 4) {
    // Valid measurement
    uint16_t distanceMM = measure.RangeMilliMeter;
    float distanceCM    = distanceMM / 10.0;
    float distanceM     = distanceMM / 1000.0;
    float distanceIN    = distanceMM / 25.4;

    String proximity = getProximityLabel(distanceMM);

    Serial.print("Distance    : ");
    Serial.print(distanceMM);
    Serial.println(" mm");

    Serial.print("            : ");
    Serial.print(distanceCM, 1);
    Serial.println(" cm");

    Serial.print("            : ");
    Serial.print(distanceM, 3);
    Serial.println(" m");

    Serial.print("            : ");
    Serial.print(distanceIN, 2);
    Serial.println(" inches");

    Serial.print("Proximity   : ");
    Serial.println(proximity);

    Serial.print("Range Status: OK (");
    Serial.print(measure.RangeStatus);
    Serial.println(")");

  } else {
    // Out of range or no target
    Serial.println("Distance    : OUT OF RANGE");
    Serial.println("Proximity   : No object detected");
    Serial.println("Range Status: Phase failure (4) - target too far or absent");
  }

  Serial.println("------------------------");
  Serial.println();

  delay(500);
}

