#include "footswitch.h"

static uint8_t fs_pin;
static bool last_state = HIGH;
static unsigned long press_time = 0;
static bool long_fired = false;

static const unsigned long LONG_PRESS_MS = 600;
static const unsigned long DEBOUNCE_MS = 25;

void footswitch_init(uint8_t pin) {
    fs_pin = pin;
    pinMode(fs_pin, INPUT_PULLUP);
}

FootswitchEvent footswitch_update() {
    bool current = digitalRead(fs_pin);
    unsigned long now = millis();

    if (last_state == HIGH && current == LOW) {
        // button pressed
        press_time = now;
        long_fired = false;
    }

    if (now-press_time > DEBOUNCE_MS) {
      if (current == LOW && !long_fired && (now - press_time >= LONG_PRESS_MS)) {
          long_fired = true;
          last_state = current;
          return FootswitchEvent::LongPress;
      }

      if (last_state == LOW && current == HIGH) {
          // button released
          if (!long_fired) {
              last_state = current;
              return FootswitchEvent::ShortPress;
          }
      }
    }
    last_state = current;
    return FootswitchEvent::None;
}
