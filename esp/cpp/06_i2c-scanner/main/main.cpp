#include "Arduino.h"
#include "Wire.h"

[[maybe_unused]] static const char *TAG = "i2c-scanner";

void i2c_scan()
{
  uint8_t device_num = 0;
  Serial.println("Scanning I2C devices...");
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();
    if (error == 0) {
      Serial.printf(
          "[0x%.2x]: Device found with clock rate %lu and timeout %u\n",
          address,
          Wire.getClock(), Wire.getTimeOut());
      device_num++;
    } else if (error == 4) {
      Serial.printf("[0x%.2x]: Unknown error.\n", address);
    }
  }
  Serial.println(device_num > 0 ? "Done.\n" : "No I2C devices found.\n");
}

void setup()
{
  Serial.begin(115200);
  Wire.begin();
}

void loop()
{
  i2c_scan();
}