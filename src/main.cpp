#include <Arduino.h>

constexpr int BUTTON_PIN = 4;
constexpr int LED_PIN = 2;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

bool lastButtonState = HIGH;
bool bypass = true;

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    bypass = !bypass;
    Serial.println(bypass ? "BYPASS" : "EFFECT ON");
    digitalWrite(LED_PIN, !bypass);
  }

  lastButtonState = currentButtonState;
}
