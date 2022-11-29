#include <Arduino.h>
#include <Wire.h>
#include <ArtronShop_SHT45.h>

ArtronShop_SHT45 sht45(&Wire, 0x44); // SHT45-AD1B => 0x44

void setup() {
  Serial.begin(115200);

  Wire.begin();
  while (!sht45.begin()) {
    Serial.println("SHT45 not found !");
    delay(1000);
  }
}

void loop() {
  if (sht45.measure()) {
    Serial.print("Temperature: ");
    Serial.print(sht45.temperature(), 1);
    Serial.print(" *C\tHumidity: ");
    Serial.print(sht45.humidity(), 1);
    Serial.print(" %RH");
    Serial.println();
  } else {
    Serial.println("SHT45 read error");
  }
  delay(1000);
}
