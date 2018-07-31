// rili frikin cool potentiometer rgb controller for neopixels ;))) by Plasmoxy

#include <Adafruit_NeoPixel.h>
#include "hsvcolors.h"

// pins
#define PIN 6
#define NUMPIXELS 16
#define BRIGHTNESS A7
#define HUE A6
#define SLEEP_THRESHOLD 25

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int hueVal = 0;
int newHueVal = 0;

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

void setup() {
  pixels.begin();
  //Serial.begin(9600);
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
  
  brightnessVal = newBrightnessVal/1024.0;

  newHueVal = map(analogRead(HUE), 0, 1024, 0, 360); // read hue
  // debounce hue
  if (newHueVal > hueVal + 6 || newHueVal < hueVal - 6) {
    hueVal = newHueVal;
  }

  // convert to rgb int[3], get pointer
  int* rgb = hsvToRgb(hueVal, 1.0, brightnessVal);

  // set values on pixels
  setPixels(rgb[0], rgb[1], rgb[2]);

  // some smoothing delay
  delay(50);
}
