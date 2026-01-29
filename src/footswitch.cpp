#include "footswitch.h"

#define FOOTSWITCH_PIN 27
#define DEBOUNCE_MS 30
#define LONG_PRESS_MS 600

static bool last_reading = HIGH;
static bool stable_state = HIGH;

static unsigned long last_change_time = 0;
static unsigned long press_start_time = 0;

static bool short_press_event = false;
static bool long_press_event = false;
static bool long_press_fired = true;

void footswitch_init() {
  pinMode(FOOTSWITCH_PIN, INPUT_PULLUP);
}

void footswitch_update() {
  short_press_event = false;
  long_press_event = false;

  bool reading = digitalRead(FOOTSWITCH_PIN);

  if (reading != last_reading) {
    last_change_time = millis();
  }

  if ((millis() - last_change_time) > DEBOUNCE_MS) {
    if (reading != stable_state) {
      stable_state = reading;
      
      if (stable_state == LOW) {
        press_start_time = millis();
        long_press_fired = false;
      } else {
        unsigned long press_duration =
          millis() - press_start_time;
        long_press_fired = true;

        if (press_duration < LONG_PRESS_MS) {
          short_press_event = true;
        }
      }
    }
  
  if ((millis() - press_start_time) > LONG_PRESS_MS && !long_press_fired){
    long_press_event = true;
    long_press_fired = true;
  }
}

  last_reading = reading;
}

bool footswitch_pressed() {
  return short_press_event;
}

bool footswitch_long_pressed() {
  return long_press_event;
}
