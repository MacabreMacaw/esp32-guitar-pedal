#include "gain.h"
#include "led.h"

void setup() {
  Serial.begin(9600);
  gain_init();
  led_init();
}

void loop() {
  int raw = gain_read_raw();
  Serial.println(raw);
  float gain = gain_read_smooth();

  // Map 0–4095 → 0–255
  int brightness = map(gain, 0, 4095, 0, 255);

  led_set_brightness(brightness);

  delay(50);
}
