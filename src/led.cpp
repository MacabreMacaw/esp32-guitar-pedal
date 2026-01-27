#include "led.h"

#define LED_PIN 25
#define LED_CH  0

void led_init() {
  ledcSetup(LED_CH, 5000, 8);   // 5 kHz, 8-bit PWM
  ledcAttachPin(LED_PIN, LED_CH);
}

void led_set_brightness(int value) {
  ledcWrite(LED_CH, value);
}
