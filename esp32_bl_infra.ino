#include <BluetoothSerial.h>

#define BT_DISCOVER_TIME	10000
BluetoothSerial SerialBT;

static bool btScanAsync = true;
static bool btScanSync  = false;

void setup() {
  Serial.begin(115200);

  // Need this? Don't think so
  SerialBT.begin("com");
  Serial.println("com dev. started");

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
  
  if (btScanSync) {
    Serial.println("Start sync. mode");
    btRes *res = SerialBT.discover(BT_DISCOVER_TIME);
    if (res)
      res->dump(&Serial);
    else
      Serial.println("Error for sync mode");
  }
}

void loop() {
  delay(100);
}

void btDevFound(btDev* dev) {
	Serial.printf("Dev found: %s\n", dev->toString().c_str());
}
