#pragma once
#include <Arduino.h>

enum class FootswitchEvent {
    None,
    ShortPress,
    LongPress
};

void footswitch_init(uint8_t pin);
FootswitchEvent footswitch_update();
