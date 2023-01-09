# 1 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino"
# 2 "/home/ash/esp32_bl_infra/esp32_bl_infra.ino" 2


BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("com");
}

void loop() {
 while (true) {
  Serial.print("Start async. mode");
  if (SerialBT.discoverAsync(btDevFound)) {
   delay(999999999);
  }
 }
}

void btDevFound(BTAdvertisedDevice* dev) {
 Serial.printf("%s", dev->toString().c_str());
}
