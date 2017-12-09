#include <Servo.h>

Servo s;
int val;
void setup() {
  // put your setup code here, to run once:
  s.attach(9);
  pinMode(A0, 0);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(A0);
  Serial.println(val);
  s.write(val);
}
