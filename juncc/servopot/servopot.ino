#include <Servo.h>

Servo s;
int val = 0;
void setup() {
  // put your setup code here, to run once:
  s.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = map(1024-analogRead(A0), 400, 600, 44, 80);
  if (val > 82) val = 82;
  if (val < 42) val = 42;
  s.write(val);
}
