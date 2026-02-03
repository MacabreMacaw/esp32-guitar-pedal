#include <Arduino.h>
#include "footswitch.h"
#include "led.h"


static LedMode led_mode = LedMode::Off;
static LedMode last_mode = LedMode::On;

void setup() {
    footswitch_init(27);   // example pin
    led_init(25, 34, 0);           // onboard LED
}

void loop() {
    FootswitchEvent ev = footswitch_update();
    led_mode = led_get_mode();

    if (ev == FootswitchEvent::ShortPress) {
        if (led_mode == LedMode::Off) {
            led_set_mode(last_mode);
        } else {
            last_mode = led_mode;
            led_set_mode(LedMode::Off);
        }
    }

    if (ev == FootswitchEvent::LongPress) {
      if (led_mode == LedMode::Blink){
        led_set_mode(LedMode::On);
        } else if (led_mode == LedMode::On) {
        led_set_mode(LedMode::Blink);
        }
    }

    
    led_update();
}
