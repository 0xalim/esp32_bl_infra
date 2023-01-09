#include <Arduino.h>
#line 1 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
#include <BluetoothSerial.h>

BluetoothSerial bts;
static bool ifSync = false;

#define BT_DISCOVER_TIME	10000

#line 8 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
void setup();
#line 28 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
void loop();
#line 32 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
void btPrint(BTAdvertisedDevice* pDevice);
#line 8 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
void setup() {
  Serial.begin(115200);
  bts.begin("Com");

	if (ifSync) {
		Serial.println("Sync");
		BTScanResults *devResults = bts.discover(BT_DISCOVER_TIME);
		if (devResults)
			devResults->dump(&Serial);
		else
			Serial.println("Nothing");
	} else {
		Serial.println("Async");
		if (bts.discoverAsync(btPrint)) {
			delay(10000);
			bts.discoverAsyncStop();
		}
	}
}

void loop() {
  delay(100);
}

void btPrint(BTAdvertisedDevice* pDevice) {
	delay(5000);
	Serial.printf("%s\r\n", pDevice->toString().c_str());
}

