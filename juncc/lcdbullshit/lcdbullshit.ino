#include <U8glib.h>
#include <Servo.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

Servo servo;

int val = 0;
int newVal = 0;
const int pot = A0;
const int h = 64;
long t = 0;
int servoVal = 0;

String st[] = {" -[ Plasmoxy ]- ", "", "", "", ""};

void setup() {  
  u8g.setFont(u8g_font_unifont);
  u8g.setColorIndex(1); 
  pinMode(A0, 0);
  servo.attach(9);
  Serial.begin(9600);
}

void loop() {
  newVal = analogRead(A0);
  if ( abs(newVal-val) > 2 ) val = newVal; // jitter filter

  servoVal = map(val, 0, 1024, 4, 175);
  servo.write(servoVal);

  String valString(val);
  st[1] = "A0 = " + valString;
  
  st[2] = "servo = " + String(servoVal) + " deg";
  st[3] = "[ " + String((val/1023.0)*100) + "% ]";
  
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

    u8g.drawBox(0, 58, (val-1)/8, 6);
    
  } while( u8g.nextPage() );
}
