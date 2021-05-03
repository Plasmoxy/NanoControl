// rili frikin cool potentiometer rgb controller for neopixels ;))) by Plasmoxy
// MOD 2021 FOR WEMOS D1
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>
#include "hsvcolors.h"
#include "wifi_password.h" // assign ssid and password char* vars
#include "page.h"

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

// direct pixel rgb vals
int directPixels[3*16] = {0, 255, 230, 0, 255, 230, 0, 255, 230, 0, 255, 230, 0, 255, 230, 0, 255, 230, 0, 255, 230, 0, 255, 230, 255, 0, 221, 255, 0, 221, 255, 0, 221, 255, 0, 221, 255, 0, 221, 255, 0, 221, 255, 0, 221, 255, 0, 221};
bool directPixelsEnabled = true;

void setPixels(int r, int g, int b) {
  uint32_t color = pixels.Color(r, g, b); // pack to 32bit RGB
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}

String IpAddress2String(const IPAddress& ipAddress)
{
    return String(ipAddress[0]) + String(".") +
           String(ipAddress[1]) + String(".") +
           String(ipAddress[2]) + String(".") +
           String(ipAddress[3]);
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void handleRoot() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "*");
  server.send(200, "text/html", getPage(IpAddress2String(WiFi.localIP())));
}

void handleSet() {

  if (server.arg("direct") != NULL) {
    directPixelsEnabled = server.arg("direct") == "true";
  }

  if (server.arg("pixels") != NULL) {
    Serial.println("Pixels loading");
    Serial.println(server.arg("pixels"));

    // KOKOT
    for (int i = 0; i < 3*16; i++) {
      directPixels[i] = (byte) getValue(server.arg("pixels"), '.', i).toInt();
    }
  }

  if (server.arg("hue") != NULL) {
    hueVal = server.arg("hue").toInt();
  }

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "*");
  server.send(200, "text/plain", "OK");
}

void setup() {
  
  pixels.begin();
  Serial.begin(9600);
  pinMode(A0, INPUT);

  delay(1000);

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
  if (directPixelsEnabled) {
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(brightnessVal*directPixels[3*i], brightnessVal*directPixels[3*i+1], brightnessVal*directPixels[3*i+2]));
    }
    pixels.show();
  } else {
    setPixels(rgb[0], rgb[1], rgb[2]);
  }

  // some smoothing delay
  delay(1000);
}
