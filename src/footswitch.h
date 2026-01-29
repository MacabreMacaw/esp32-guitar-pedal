#pragma once
#include <Arduino.h>

void footswitch_init();
void footswitch_update();

bool footswitch_pressed();      // short press event
bool footswitch_long_pressed(); // long press event
