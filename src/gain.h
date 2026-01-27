#pragma once
#include <Arduino.h>

void gain_init();
int gain_read_raw();
float gain_read_smooth();
