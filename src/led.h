#pragma once
#include <Arduino.h>

enum class LedMode {
    Off,
    On,
    Blink
};

void led_init(int led_pin, int pot_pin, int pwm_channel);
void led_set_mode(LedMode mode);
LedMode led_get_mode();
void led_update();
