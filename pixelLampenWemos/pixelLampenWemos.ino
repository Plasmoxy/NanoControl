// rili frikin cool potentiometer rgb controller for neopixels ;))) by Plasmoxy
// MOD 2021 FOR WEMOS D1
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>
#include "hsvcolors.h"
#include "wifi_password.h" // assign ssid and password char* vars

// pins
#define PIN D2
#define NUMPIXELS 16
#define BRIGHTNESS A0
#define SLEEP_THRESHOLD 25

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
ESP8266WebServer server ( 80 );
int hueVal = 0;
int newBrightnessVal = 0;
float brightnessVal = 0;
bool sleeping = false;

void setPixels(int r, int g, int b) {
  uint32_t color = pixels.Color(r, g, b); // pack to 32bit RGB
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}

void handleRoot() {
  server.send(200, "text/plain", "RUNNING");
}

void handleSet() {
  hueVal = server.arg("hue").toInt();
  server.send(200, "text/plain", "OK");
}

void setup() {
  pixels.begin();
  Serial.begin(9600);
  pinMode(A0, INPUT);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // routing
  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.begin();
  Serial.println("server started");
}

void loop() {
  newBrightnessVal = analogRead(BRIGHTNESS);
  //Serial.println(newBrightnessVal);
  
  if (newBrightnessVal < SLEEP_THRESHOLD) {
    sleeping = true;
    setPixels(0, 0, 0);
  } else {
    sleeping = false;
  }

  if (sleeping) {
    delay(1000);
    return;
  }

  // not sleeping, server
  server.handleClient();

  // brightness
  brightnessVal = newBrightnessVal/1024.0;
  
  // convert to rgb int[3], get pointer
  int* rgb = hsvToRgb(hueVal, 1.0, brightnessVal);

  // set values on pixels
  setPixels(rgb[0], rgb[1], rgb[2]);

  // some smoothing delay
  delay(1000);
}
