#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <WiFiClient.h>

WiFiClient client;

#define WIFI_SSID "esp32"
#define WIFI_PASSWORD "india1234"
#define THINGSPEAK_API_KEY "AJAHECVS1K2N98D4"
#define THINGSPEAK_CHANNEL_ID 2475696  // apikey: IUD256CYE87PWFII

int count = 0;
int value = 0;
long duration, distance;
const int led = 2;

#define TRIGGER_PIN 23
#define ECHO_PIN 22
#define LED_PIN_1 15
#define LED_PIN_2 4
#define LED_PIN_3 5
#define LED_PIN_4 18
#define LED_PIN_5 19
#define LED_PIN_6 21

#define MAX_DISTANCE_CM 40
#define MIN_DISTANCE_CM 4
#define LED_ON HIGH
#define LED_OFF LOW

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  pinMode(led, OUTPUT);
  WiFi.mode(WIFI_STA);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Blink LED to indicate WiFi connection
  for (int i = 0; i < 2; i++) {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
  }

  ThingSpeak.begin(client);
  Serial.println("Initializing...");

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
  pinMode(LED_PIN_5, OUTPUT);
  pinMode(LED_PIN_6, OUTPUT);

  digitalWrite(LED_PIN_1, LED_OFF);
  digitalWrite(LED_PIN_2, LED_OFF);
  digitalWrite(LED_PIN_3, LED_OFF);
  digitalWrite(LED_PIN_4, LED_OFF);
  digitalWrite(LED_PIN_5, LED_OFF);
  digitalWrite(LED_PIN_6, LED_OFF);
}

void loop() {
  // Trigger ultrasonic sensor
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  value = distance * 4;
  if (value > 100) value = 100;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // LED logic based on distance
  digitalWrite(LED_PIN_1, distance < 5 ? LED_ON : LED_OFF);
  digitalWrite(LED_PIN_2, distance < 10 ? LED_ON : LED_OFF);
  digitalWrite(LED_PIN_3, distance < 15 ? LED_ON : LED_OFF);
  digitalWrite(LED_PIN_4, distance < 20 ? LED_ON : LED_OFF);
  digitalWrite(LED_PIN_5, distance < 25 ? LED_ON : LED_OFF);
  digitalWrite(LED_PIN_6, distance < MAX_DISTANCE_CM ? LED_ON : LED_OFF);

  if (distance < MIN_DISTANCE_CM || distance > MAX_DISTANCE_CM) {
    digitalWrite(LED_PIN_1, LED_OFF);
    digitalWrite(LED_PIN_2, LED_OFF);
    digitalWrite(LED_PIN_3, LED_OFF);
    digitalWrite(LED_PIN_4, LED_OFF);
    digitalWrite(LED_PIN_5, LED_OFF);
    digitalWrite(LED_PIN_6, LED_OFF);
  }

  count++;
  delay(500);

  if (count > 32) {
    count = 0;
    uploadData();
  }
}

void uploadData() {
  ThingSpeak.setField(1, value);
  int statusCode = ThingSpeak.writeFields(THINGSPEAK_CHANNEL_ID, THINGSPEAK_API_KEY);
  if (statusCode == 200) {
    Serial.println("Data sent to ThingSpeak successfully.");
  } else {
    Serial.print("Error sending data to ThingSpeak. HTTP error code: ");
    Serial.println(statusCode);
  }
}
