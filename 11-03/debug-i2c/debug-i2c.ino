#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin();

  delay(1000);
  Serial.println("I2C Scanner Starting...");
}

void loop() {
  int devicesFound = 0;

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Device found at 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      devicesFound++;
    }
  }

  if (devicesFound == 0) {
    Serial.println("No I2C devices found!");
  }

  Serial.println("Scan complete.");
  delay(3000);
}