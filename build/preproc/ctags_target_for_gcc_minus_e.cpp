# 1 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
# 2 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino" 2


BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("com");
}

void loop() {
 while (true) {
  BTScanResults *pResults = SerialBT.discover(10000);

  if (pResults)
   pResults->dump(&Serial);
  else
   Serial.println("no results");
 }
}

void btDevFound(BTAdvertisedDevice* dev) {
 Serial.printf("%s", dev->toString().c_str());
}
