#include <BluetoothSerial.h>

// Your ESP32 will act as RFCOMM Server device
// In RoboRemo tap Menu -> CONNECT -> Bluetooth (RFCOMM) -> ESP32-RFCOMM
// (Device must be paired first from Android Bluetooth Settings)
BluetoothSerial SerialBT; 

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Starting Bluetooth RFCOMM server...");

  if (!SerialBT.begin("ESP32-RFCOMM")) {
    Serial.println("An error occurred initializing Bluetooth");
    return;
  }
  Serial.println("Bluetooth device is ready to pair");
}

void loop() {

  if (SerialBT.hasClient()) {
    Serial.println("Client connected");
    String command = "";
    while (SerialBT.connected()) {
      if (SerialBT.available()) {
        char c = SerialBT.read();
        if (c == '\n') {
          // End of command
          Serial.println("Received: " + command);
          // Example: toggle an onboard LED or parse commands
          // For now, just echo back
          SerialBT.println("Received: " + command);
        
          // Clear command buffer
          command = "";
        } else {
          command += c;
        }
      }
    }
    Serial.println("Client disconnected");
  }
}
