/* Servo turret calibration by Plasmoxy */
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
byte topsDeg = 0, botsDeg = 0;

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
  botsDeg = map(valA, POT_MIN, POT_MAX, BOTS_MIN, BOTS_MAX);
  topsDeg = map(valB, POT_MIN, POT_MAX, TOPS_MIN, TOPS_MAX);

  // write to servos
  bots.write(botsDeg);
  tops.write(topsDeg);

  // print info
  Serial.println("B:"+String(botsDeg) + " T:" + String(topsDeg));
}
