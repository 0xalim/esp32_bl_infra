#include <Arduino.h>
#line 1 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
#include <BluetoothSerial.h>

#define BT_DISCOVER_TIME	10000
BluetoothSerial SerialBT;

static bool btScanAsync = true;
static bool btScanSync  = false;

#line 9 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
void setup();
#line 38 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
void loop();
#line 42 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
void btAdvertisedDeviceFound(BTAdvertisedDevice* pDevice);
#line 9 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");


  if (btScanAsync) {
    Serial.print("Starting discoverAsync...");
    if (SerialBT.discoverAsync(btAdvertisedDeviceFound)) {
      Serial.println("Findings will be reported in \"btAdvertisedDeviceFound\"");
      delay(10000);
      Serial.print("Stopping discoverAsync... ");
      SerialBT.discoverAsyncStop();
      Serial.println("stopped");
    } else {
      Serial.println("Error on discoverAsync f.e. not workin after a \"connect\"");
    }
  }
  
  if (btScanSync) {
    Serial.println("Starting discover...");
    BTScanResults *pResults = SerialBT.discover(BT_DISCOVER_TIME);
    if (pResults)
      pResults->dump(&Serial);
    else
      Serial.println("Error on BT Scan, no result!");
  }
}

void loop() {
  delay(100);
}

void btAdvertisedDeviceFound(BTAdvertisedDevice* pDevice) {
	Serial.printf("Found a device asynchronously: %s\n", pDevice->toString().c_str());
}

