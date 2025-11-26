#include <DHT.h>
#include "EspMQTTClient.h"
#include <Wire.h>
#include <U8g2lib.h>

// ===== OLED (U8g2 SH1106 / SSD1306 Auto Works) =====
U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

// ===== DHT =====
#define DHTPIN 19
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ===== Relay & Fan =====
#define RELAY_PIN 18
bool fanOn = false;

// ===== PIR & LEDs =====
#define PIR_PIN 2
#define LEDS_PIN 15
bool ledsOn = false;
bool motionDetected = false;

// ===== MQTT =====
EspMQTTClient client(
  "Redmi 12 5G",
  "bhakti1234",
  "broker.hivemq.com",
  "",
  "",
  "ESP32_CLIENT_987",
  1883
);

void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LEDS_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);

  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LEDS_PIN, LOW);

  display.begin();
  display.clearBuffer();
  display.sendBuffer();

  client.enableDebuggingMessages();
}

void onConnectionEstablished() {

  // ==== LED CONTROL ====
  client.subscribe("home/room1/leds/control", [&](const String &msg) {
    if (msg == "on") {
      digitalWrite(LEDS_PIN, HIGH);
      ledsOn = true;
    } else {
      digitalWrite(LEDS_PIN, LOW);
      ledsOn = false;
    }
    client.publish("home/room1/leds/status", ledsOn ? "ON" : "OFF");
  });

  // ==== FAN CONTROL ====
  client.subscribe("home/room1/fan/control", [&](const String &msg) {
    if (msg == "on") {
      digitalWrite(RELAY_PIN, HIGH);
      fanOn = true;
    } else {
      digitalWrite(RELAY_PIN, LOW);
      fanOn = false;
    }
    client.publish("home/room1/fan/status", fanOn ? "ON" : "OFF");
  });
}

void loop() {
  client.loop();

  // ==== PIR =====
  motionDetected = digitalRead(PIR_PIN);

  // ==== DHT =====
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(t)) client.publish("home/room1/temperature", String(t));
  if (!isnan(h)) client.publish("home/room1/humidity", String(h));

  client.publish("home/room1/motion", motionDetected ? "Detected" : "None");

  // ===== OLED Display =====
  display.clearBuffer();
  display.setFont(u8g2_font_6x10_tf); 

  display.setCursor(0, 14);
  display.print("Temp: ");
  display.print(t);
  display.print("C");

  display.setCursor(0, 32);
  display.print("Hum : ");
  display.print(h);
  display.print("%");

  display.setCursor(0, 50);
  display.print("LED:");
  display.print(ledsOn ? "ON" : "OFF");
  display.print(" Fan:");
  display.print(fanOn ? "ON" : "OFF");

  display.sendBuffer();

  delay(1500);
}
