#include <Adafruit_NeoPixel.h>
#include "hsvcolors.h"

#define PIN 6
#define NUMPIXELS 16
#define BRIGHTNESS A7
#define HUE A6

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int hueVal = 0;
int newHueVal = 0;

float brightnessVal = 0;

void setup() {
  pixels.begin();
}

void loop() {
  newHueVal = map(analogRead(HUE), 0, 1024, 0, 360);
  brightnessVal = analogRead(BRIGHTNESS)/1024.0;

  if (newHueVal > hueVal + 6 || newHueVal < hueVal - 6) {
    hueVal = newHueVal;
  }
  
  int* rgb = hsvToRgb(hueVal, 1.0, brightnessVal);
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(rgb[0], rgb[1], rgb[2]));
  }
  pixels.show();
  delay(50);
}
