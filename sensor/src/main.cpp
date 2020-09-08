#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "secrets.h"

#define ONBOARD_LED 2
#define SENSOR_PIN 23
volatile byte state = LOW;

__unused void setup() {
    // Setup serial connection
    Serial.begin(115200);

    // Setup pins
    pinMode(ONBOARD_LED, OUTPUT);
    pinMode(SENSOR_PIN, INPUT);

    // Setup wifi
    WiFi.begin(wifiNetworkName, wifiNetworkPassword);

    unsigned long start = millis();
    while (WiFiClass::status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
        delay(10);
        Serial.print('.');
    }
    Serial.print("Connected to wifi after: ");
    Serial.print(millis() - start);
    Serial.println(" millis");

    Serial.println('\n');
    Serial.println("Connection established!");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
}

void sendHttp(volatile byte state) {
    try {
        HTTPClient http;
        http.begin("http://10.41.33.50:8080/");
        char buf[50];
        int responseCode = http.POST(ltoa(state, buf, 10));
        Serial.print("Response code: ");
        Serial.println(responseCode);

        while (http.connected()) {
            String body = http.getString();
            Serial.println(body);
        }

        http.end();
    } catch (char const* s) {
        Serial.println(s);
    }
}

__unused void loop() {
//    Serial.println("Loop:");

    // Read the current state
    state = digitalRead(SENSOR_PIN);

    // Serial.print("  state: ");
    // Serial.println(state);

    if (state == LOW) digitalWrite(ONBOARD_LED, HIGH);
    else digitalWrite(ONBOARD_LED, LOW);

    sendHttp(state);
    delay(1000);
}


