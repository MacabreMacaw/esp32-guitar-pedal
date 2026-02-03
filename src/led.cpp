#include "led.h"

static int ledPin;
static int potPin;
static int pwmChannel;

static LedMode currentMode = LedMode::Off;

/* Blink state */
static bool blinkState = false;
static unsigned long lastBlinkMs = 0;
static const unsigned long BLINK_INTERVAL_MS = 100;

/* Brightness */
static int brightness = 0;

void led_init(int led_pin, int pot_pin, int pwm_channel) {
    ledPin = led_pin;
    potPin = pot_pin;
    pwmChannel = pwm_channel;

    ledcSetup(pwmChannel, 5000, 8);
    ledcAttachPin(ledPin, pwmChannel);
}

void led_set_mode(LedMode mode) {
    if (mode == currentMode) {
        return; // prevent restart
    }

    currentMode = mode;

    // Reset blink timing ONLY when entering blink
    if (currentMode == LedMode::Blink) {
        lastBlinkMs = millis();
        blinkState = false;
    }
}

LedMode led_get_mode() {
    return currentMode;
}

void led_update() {
    unsigned long now = millis();

    switch (currentMode) {
        case LedMode::Off:
            ledcWrite(pwmChannel, 0);
            break;

        case LedMode::On:
            brightness = analogRead(potPin) >> 4; // 0–255
            ledcWrite(pwmChannel, brightness);
            break;

        case LedMode::Blink:
            if (now - lastBlinkMs >= BLINK_INTERVAL_MS) {
                lastBlinkMs = now;
                blinkState = !blinkState;
            }

            ledcWrite(pwmChannel, blinkState ? 255 : 0);
            break;
    }
}
