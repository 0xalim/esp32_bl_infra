# 1 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
# 2 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino" 2
# 3 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino" 2
# 4 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino" 2
# 5 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino" 2
# 6 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino" 2

BluetoothSerial bts;
BLEScan* bles;

static bool ifSync = false;
static int scanTime = 10;



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
  BTScanResults *devResults = bts.discover(10000);
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
 Serial.println(foundDevices.getCount());
 bles->clearResults();
}

void btPrint(BTAdvertisedDevice* pDevice) {
 delay(5000);
 Serial.printf("%s\r\n", pDevice->toString().c_str());
}
