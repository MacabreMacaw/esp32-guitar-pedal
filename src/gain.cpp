#include "gain.h"

#define GAIN_PIN 34

void gain_init() {
  pinMode(GAIN_PIN, INPUT);
}

int gain_read_raw() {
  return analogRead(GAIN_PIN);
}

static float smoothed = 0.0f;

float gain_read_smooth() {
  int raw = analogRead(GAIN_PIN);

  // Exponential moving average
  smoothed = 0.9f * smoothed + 0.1f * raw;

  return smoothed;
}

