#include <U8glib.h>

#define pot A7

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

int val = 0;
int newVal = 0;
const int h = 64;
long t = 0;

String st[] = {" -[POTMONITOR]- ", "", "", "", ""};

void setup() {  
  u8g.setFont(u8g_font_unifont);
  u8g.setColorIndex(1); 
  pinMode(pot, 0);
  pinMode(3, 1);
}

void loop() {
  newVal = analogRead(pot);
  if ( abs(newVal-val) > 2 ) val = newVal; // jitter filter
  if ( val > 1015 ) val = 1024; // cut sides
  if ( val < 6 ) val = 0;

  analogWrite(3, map(val, 0, 1024, 0, 255));

  String valString(val);
  st[1] = "A7 = " + valString;
  st[3] = "[ " + String((val/1024.0)*100) + "% ]";
  draw();
}  

void draw(){
  u8g.firstPage();
  do {
    
    u8g.drawStr(0, 12, st[0].c_str());
    for ( int i = 0; i <= 3; i++)
    {
      u8g.drawStr(0, h-i*12-1, st[4-i].c_str());
    }

    u8g.drawBox(0, 58, map(val, 0, 1024, 0, 128), 6);
    u8g.drawCircle(106, 34, map(val, 0, 1024, 0, 18));

    if ( val == 0 ) u8g.drawStr(96, 58, "OFF");
    if ( val == 1024 ) u8g.drawStr(99, 40, "ON");
    
  } while( u8g.nextPage() );
}
