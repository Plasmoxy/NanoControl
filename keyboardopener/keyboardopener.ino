#include "DigiKeyboard.h"
#define DOT 0x37

void setup() {
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  delay(500);
  print("chrome");
  stroke(DOT);
  print("exe gzmlipanz");
  stroke(DOT);
  print("edupage");
  stroke(DOT);
  print("org");
  stroke(KEY_ENTER);
}

void stroke(byte s) {
  DigiKeyboard.sendKeyStroke(s);
}

void print(char *str) {
  char c = str[0];
  byte i = 0;
  DigiKeyboard.update();
  DigiKeyboard.sendKeyStroke(0); //this is generally not necessary but with some older systems it seems to prevent missing the first character after a delay
  while (c != 0) {
    if (c==' ')
      DigiKeyboard.sendKeyStroke(KEY_SPACE);
    if (c>='A' && c<='Z')
      DigiKeyboard.sendKeyStroke(KEY_A+(c-'A'), MOD_SHIFT_LEFT);
    if (c>='a' && c<='z')
      DigiKeyboard.sendKeyStroke(KEY_A+(c-'a'));
    if (c=='0')
      DigiKeyboard.sendKeyStroke(KEY_0);
    if (c>='1' && c<='9')
      DigiKeyboard.sendKeyStroke(KEY_1+(c-'1'));
    i++;
    c = str[ i ];
  }
}

void println (char *str) {
  print(str);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
}

void loop() {
}
