# 1 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
# 2 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino" 2

BluetoothSerial bts;
static bool ifSync = false;



void setup() {
  Serial.begin(115200);
  bts.begin("Com");

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
  delay(100);
}

void btPrint(BTAdvertisedDevice* pDevice) {
 delay(5000);
 Serial.printf("%s\r\n", pDevice->toString().c_str());
}
