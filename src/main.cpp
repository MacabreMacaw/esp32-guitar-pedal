#include <Arduino.h>

constexpr int LED_PIN = 2;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  Serial.println("LED ON");
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
