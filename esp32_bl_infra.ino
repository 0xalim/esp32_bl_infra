#include <BluetoothSerial.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

BluetoothSerial bts;
BLEScan* bles;

static bool ifSync   = false;
static int  scanTime = 10;

#define BT_DISCOVER_TIME	10000

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
	void onResult(BLEAdvertisedDevice advertisedDevice) {
		Serial.printf("%s\r\n", advertisedDevice.toString().c_str());
	}
};

void setup() {
  Serial.begin(115200);
  bts.begin("Com");

	BLEDevice::init("");
	bles = BLEDevice::getScan();
  bles->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
	bles->setActiveScan(true);
	bles->setInterval(100);
	bles->setWindow(99);

	Serial.println("Bluetooth BR/EDR\r\n");
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
  delay(2000);
	BLEScanResults foundDevices = bles->start(scanTime, false);
	Serial.print("Bluetooth Low Energy\r\n");
	Serial.printf("Count: %d\r\n", foundDevices.getCount());
	bles->clearResults();
}

void btPrint(BTAdvertisedDevice* pDevice) {
	delay(5000);
	Serial.printf("%s\r\n", pDevice->toString().c_str());
}
