#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "iPhone";
const char* password = "135792468";

const char* mqtt_server = "thesoshi.com";
const int mqtt_port = 2424;

const char* clientId = "salam";

const char* target_topic_control = "microlab/light/control";
const char* target_topic_mode = "microlab/light/mode";
const char* target_topic_ldr = "microlab/light/ldr";

unsigned long LastTry;
const int ledPin = 2;  // GPIO pin where the LED is connected
const int ldrPin = A5; // Analog pin where the LDR is connected

WiFiClient espClient;
PubSubClient client(espClient);

bool automaticMode = false;
int ldrValue = 0;

void setup_wifi();
void callback(char* topic, byte* message, unsigned int length);
void setLED(bool state);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);  // Initialize the LED pin as an output
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  LastTry = millis();
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  String messageTemp = String((char*)message).substring(0, length);
  Serial.println(messageTemp);

  if (String(topic) == target_topic_control) {
    if (!automaticMode) { // Only handle manual control if not in automatic mode
      if (messageTemp == "on") {
        setLED(true);
      } else if (messageTemp == "off") {
        setLED(false);
      }
    }
  } else if (String(topic) == target_topic_mode) {
    if (messageTemp == "automatic") {
      automaticMode = true;
    } else if (messageTemp == "manual") {
      automaticMode = false;
    }
    Serial.print("Mode set to: ");
    Serial.println(automaticMode ? "Automatic" : "Manual");
  }
}

void reconnect() {
  if (millis() - LastTry >= 2000) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientId)) {
      Serial.println("connected");
      client.subscribe(target_topic_control, 1); // Use QoS 1 for subscription
      client.subscribe(target_topic_mode, 1);    // Use QoS 1 for subscription
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
    }
    LastTry = millis();
  }
}

void setLED(bool state) {
  digitalWrite(ledPin, state ? HIGH : LOW);
  Serial.println(state ? "LED turned ON" : "LED turned OFF");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  } else {
    client.loop();

    if (automaticMode) {
      // Read LDR value
      ldrValue = analogRead(ldrPin);
      // Adjust LED brightness based on LDR value
      int ledBrightness = map(ldrValue, 0, 4095, 0, 255);
      analogWrite(ledPin, ledBrightness);
      Serial.print("LDR value: ");
      Serial.print(ldrValue);
      Serial.print(" -> LED brightness: ");
      Serial.println(ledBrightness);

      // Publish LDR value to MQTT
      char ldrStr[8];
      itoa(ldrValue, ldrStr, 10);
      client.publish(target_topic_ldr, ldrStr, true);
      delay(1000);
    } else {
      // Publish LDR value to MQTT
      char ldrStr[8];
      itoa(ldrValue, ldrStr, 10);
      client.publish(target_topic_ldr, ldrStr, true);
      delay(1000); // Delay to avoid spamming the loop in manual mode
    }
  }
}
