#include <BluetoothSerial.h>

#define BT_DISCOVER_TIME	10000
BluetoothSerial SerialBT;

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
