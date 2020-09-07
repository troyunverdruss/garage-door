#include <Arduino.h>

#define ONBOARD_LED 2
#define SENSOR_PIN 23
volatile byte state = LOW;
int lastState = 0;

__unused void setup() {
    Serial.begin(115200);
    pinMode(ONBOARD_LED, OUTPUT);
    pinMode(SENSOR_PIN, INPUT);
}

__unused void loop() {
//    Serial.println("Loop:");

    // Read the current state
    state = digitalRead(SENSOR_PIN);

    // Serial.print("  state: ");
    // Serial.println(state);

    if (state == LOW) digitalWrite(ONBOARD_LED, HIGH);
    else digitalWrite(ONBOARD_LED, LOW);
}