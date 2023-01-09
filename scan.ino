#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
#define BT_DISCOVER_TIME	1000

static bool btScanAsync = true;
static bool btScanSync  = false;

void setup() {
	Serial.begin(115200);
	SerialBT.begin("com");
	Serial.println("Com started");

	if (btScanAsync) {
		Serial.print("Async disc. mode");
		if (SerialBT.discoverAsync(btPublicDev()) {
			Serial.println("Dumped in list");

			delay(10000);
			SerialBT.discoverAsyncStop();
			Serial.print("Stopped Async dic. mode");
		} else {
			Serial.println("Error on async disc. mode");
		}
	}

	if (btScanSync) {
		Serial.print("Sync disc. mode");
		btRes *res = SerialBT.discover(BT_DISCOVER_TIME);
		if (res)
			res->dump(&Serial);
		else
			Serial.println("Error on sync disc. mode");
	}
}

void loop() {
	delay(100);
}

void btPublicDev(btDev* dev) {
	Serial.printf("Device found: %s\n", dev->toString().c_str());
}
