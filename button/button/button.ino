#include <Button.h>

Button btn(4);
bool toggle = false;

void setup() {
  btn.begin();
  Serial.begin(9600);
}

void loop() {
  if (btn.pressed()) {
    toggle = !toggle;
    Serial.println(toggle);
  }
}
