#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h> // 서버를 위한 헤더
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h> // Neopixel 헤더

#include <PubSubClient.h> // mqtt 헤더

#define NEO_led   15
#define led_state 16
#define ledNum    72

Adafruit_NeoPixel pixels;

void neo_pixel(int R, int G, int B) {
  for (int i = 0; i < ledNum; i++) {
    pixels.setPixelColor(i, pixels.Color(R,G,B));
  }
  pixels.show();
}

void neo() {
  int R = 0;
  int B = 0;
  int G = 0;
  for (int i = 0; i <255; i++) {
    if (i % 30 == 0) {
      R = i;
    } else if (i % 30 == 10) {
      B = i;
    } else if (i % 30 == 20) {
      G = i;
    }
    for (int j = 0; j < ledNum; j++) {
      pixels.setPixelColor(j, pixels.Color(R,G,B));
    }
    pixels.show();
  }
}

void setup() {
  // put your setup code here, to run once:
  pixels = Adafruit_NeoPixel(ledNum, NEO_led, NEO_RGB + NEO_KHZ800);

  Serial.begin(115200);
  pixels.begin();
  delay(500);
  Serial.println("starting");

}

void loop() {
  // put your main code here, to run repeatedly:
  neo(); 
}