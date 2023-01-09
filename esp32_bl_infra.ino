#include <BluetoothSerial.h>

#define BT_DISCOVER_TIME	10000
BluetoothSerial SerialBT;

static bool btScanAsync = true;

void setup() {
  Serial.begin(115200);

  // Need this? Don't think so
  SerialBT.begin("com");
  Serial.println("com dev. started");
}

void loop() {
  delay(100);
  if (btScanAsync) {
    Serial.print("Start async. mode");
    if (SerialBT.discoverAsync(btDevFound)) {
      Serial.println("Dump...");

      delay(10000);
      SerialBT.discoverAsyncStop();
      Serial.print("Stop async. mode");
    } else {
      Serial.println("Error for async. mode");
    }
  }
}

void btDevFound(btDev* dev) {
	Serial.printf("Dev found: %s\n", dev->toString().c_str());
}
