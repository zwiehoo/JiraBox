#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "wifi.h"
#include "bitmaps.h"

#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT == 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void blinkSpartexLogo() {
  display.clearDisplay();
    display.drawBitmap(16, 0, spartexLogo, 32, 32, WHITE);
    display.display();
    delay(500);
    display.clearDisplay();
    display.display();
    delay(500);
}

void blinkBambus() {
  display.clearDisplay();
  display.drawBitmap(16, 0, spartexLogo, 32, 32, WHITE);
    display.drawBitmap(80, 0, bambus, 32, 32, WHITE);
    display.display();
    delay(500);
    display.clearDisplay();
    display.drawBitmap(16, 0, spartexLogo, 32, 32, WHITE);
    display.display();
    delay(500);
}

void allConnected() {
  display.clearDisplay();
display.drawBitmap(16, 0, spartexLogo, 32, 32, WHITE);
    display.drawBitmap(80, 0, bambus, 32, 32, WHITE);
  display.display();
}

void setup() {
  delay(1000);
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("You will be connected...");
  display.display();

  //delay(3000);

  for (int i = 0; i < 5; i++) {
    //blinkSpartexLogo();
  }

  while (WiFi.status() != WL_CONNECTED)
  {
    blinkSpartexLogo();
  }

  for (int i = 0; i < 5; i++) {
    //blinkBambus();
  }

  allConnected();

  //delay(2000);
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("http begin");
  IPAddress ip = WiFi.localIP();
  display.println(ip.toString());
  display.display();

  HTTPClient http;
  http.begin("http://192.168.0.149:8080/testing");
  int httpCode = http.GET();
  display.println(http.errorToString(-1));
  display.display();
  http.end();
  delay(3000);
}