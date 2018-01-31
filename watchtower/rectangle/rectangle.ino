/* Servo turret rectangle */
/* NOTE : bots is bottom servo, tops is top servo */

#include <Servo.h>

#define POT_MAX 1015
#define POT_MIN 5
#define BOTS_MIN 0
#define BOTS_MAX 180
#define TOPS_MIN 0
#define TOPS_MAX 180

const byte botsPin = 5, topsPin = 6;
const byte potA = A7, potB = A6;

Servo bots, tops;

int valA = 0, valB = 0;
byte valADeg = 0, valBDeg = 0;

byte midx = 95, midy = 85;
byte diffx = 10, diffy = 10;
const byte change = 1;

byte x = midx-diffx, y = midy-diffy;

void setup() {
  Serial.begin(9600);
  pinMode(potA, INPUT);
  pinMode(potB, INPUT);
  bots.attach(botsPin);
  tops.attach(topsPin);
}

void loop() {
  // read pots
  valA = analogRead(potA);
  valB = analogRead(potB);
  
  // debouce potentiometer sides
  if (valA < POT_MIN) valA = POT_MIN;
  if (valA > POT_MAX) valA = POT_MAX;
  if (valB < POT_MIN) valB = POT_MIN;
  if (valB > POT_MAX) valB = POT_MAX;

  // map to degrees
  valADeg = map(valA, POT_MIN, POT_MAX, BOTS_MIN, BOTS_MAX);
  valBDeg = map(valB, POT_MIN, POT_MAX, TOPS_MIN, TOPS_MAX);


  // animate inside intervals
  if (x < midx+diffx && y == midy-diffy) x+=change; // bottom
  if (y < midy+diffx && x == midx+diffx) y+=change; // right
  if (x > midx-diffx && y == midy+diffy) x-=change; // top
  if (y > midy-diffy && x == midx-diffx) y-=change; // left

  // detect corners
  if (x == midx-diffx && y == midy-diffy) x+=change; // botleft
  if (x == midx+diffx && y == midy-diffy) y+=change; // bot right
  if (x == midx+diffx && y == midy+diffy) x-=change; // top right
  if (x == midx-diffx && y == midy+diffy) y-=change; // top left

  // write to servos
  bots.write(x);
  tops.write(y);

  // print info
  Serial.println("B:"+String(x) + " T:" + String(y));

  delay(5); // out of love to servos
}
