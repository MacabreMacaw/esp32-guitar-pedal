#include <Arduino.h>
#include "led.h"
#include "gain.h"
#include "footswitch.h"

static bool bypass = true;
static bool led_mode = true;
static bool blink_state;
static unsigned long last_blink_time;


void setup() {
  led_init();
  gain_init();
  footswitch_init();
}


void update_blink() {
  if (millis() - last_blink_time >= 100) {
    last_blink_time = millis();
    blink_state = !blink_state;
  }
}


void loop() {
  footswitch_update();
  update_blink();

  if (footswitch_pressed()) {
    bypass = !bypass;
  }

  if (footswitch_long_pressed() && !bypass) {
    led_mode = !led_mode;
  }

  float gain = gain_read_smooth();

  if (bypass) {
    led_set_brightness(0);
  }
  else if (led_mode) {
    led_set_brightness(blink_state ? 0:255);
  } 
  else {
    int brightness = map(gain, 0, 4095, 0, 255);
    led_set_brightness(brightness);
  }
}
