#include "BluetoothSerial.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

BluetoothSerial SerialBT;

// Declaration for an SSD1306 display connected to I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String receivedData;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Smart Cognitive Glass");

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Smart Cognitive Glass");
  display.display();

  Serial.println("Waiting for a Bluetooth connection...");
}

void loop() {
  if (SerialBT.available()) {
    receivedData = SerialBT.readStringUntil('\n'); 

    
    int delimiterIndex = receivedData.indexOf('|');
    String notification = receivedData.substring(0, delimiterIndex);
    String batteryStatus = receivedData.substring(delimiterIndex + 1, receivedData.indexOf('|', delimiterIndex + 1));
    String timeAndDate = receivedData.substring(receivedData.indexOf('|', delimiterIndex + 1) + 1);

    
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Notification:");
    display.println(notification);
    display.println("Battery Status:");
    display.println(batteryStatus);
    display.println("Time and Date:");
    display.println(timeAndDate);
    display.display();

    receivedData = ""; // Clear the received data string
  }
  delay(100);
}