#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const byte pot = A0;

int val = 0, prev = 0, thres = 4;
byte mod = 0, prevMod = 0;

void setup()
{
    MIDI.begin();
    Serial.begin(115200);
    pinMode(pot, INPUT);
}

void loop()
{
  val = analogRead(pot);
  
  if ( (abs(val-prev) < 20) && (val > prev+thres || val < prev-thres )) {
    mod = map(val, 0, 1020, 0, 127);
    if (mod < 0) mod=0; if (mod > 127) mod=127;
    
    if (mod != prevMod) {
      MIDI.sendControlChange(1, mod, 1);
      prevMod = mod;
    }
    
    prev = val;
  }
}
