#include <Arduino.h>
#line 1 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
#include <BluetoothSerial.h>

#define BT_DISCOVER_TIME	10000
BluetoothSerial SerialBT;

#line 6 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
void setup();
#line 11 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
void loop();
#line 22 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
void btDevFound(BTAdvertisedDevice* dev);
#line 6 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
void setup() {
  Serial.begin(115200);
  SerialBT.begin("com");
}

void loop() {
	while (true) {
		BTScanResults *pResults = SerialBT.discover(BT_DISCOVER_TIME);

		if (pResults)
			pResults->dump(&Serial);
		else
			Serial.println("no results");
	}
}

void btDevFound(BTAdvertisedDevice* dev) {
	Serial.printf("%s", dev->toString().c_str());
}

