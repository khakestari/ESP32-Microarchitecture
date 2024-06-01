#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "iPhone";
const char* password = "135792468";

const char* mqtt_server = "thesoshi.com";
const int mqtt_port = 2424;

const char* target_topic = "microlab/light";

unsigned long LastTry;
const int ledPin = 2;  // GPIO pin where the LED is connected

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi();
void callback(char* topic, byte* message, unsigned int length);

void setup() {
  Serial.begin(9600);
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

  if (String(topic) == target_topic) {
    if (messageTemp == "on") {
      digitalWrite(ledPin, HIGH);  // Turn LED on
      Serial.println("LED turned ON");
    } else if (messageTemp == "off") {
      digitalWrite(ledPin, LOW);  // Turn LED off
      Serial.println("LED turned OFF");
    } else {
      Serial.println("Unknown command");
    }
  }
}

void reconnect() {
  if (millis() - LastTry >= 2000) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe(target_topic, 1); // Use QoS 1 for subscription
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
    }
    LastTry = millis();
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  } else {
    client.loop();
  }
}

// /*------------------------------------------PUB----------------------------------------*/

// #include <WiFi.h>
// #include <PubSubClient.h>

// #define MSG_BUFFER_SIZE (50)

// const char* ssid = "iphone";
// const char* password = "135792468";

// const char* mqtt_server = "thesoshi.com";
// const int mqtt_port = 2424;

// WiFiClient espClient;
// PubSubClient client(espClient);

// unsigned long lastMsg = 0;
// char msg[MSG_BUFFER_SIZE];
// int value = 0;

// void setup() {
//  Serial.begin(115200);
//  setup_wifi();
//  client.setServer(mqtt_server, mqtt_port);
// }

// void setup_wifi() {
//  delay(10);
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);

//  WiFi.begin(ssid, password);

//  while (WiFi.status() != WL_CONNECTED) {
//  delay(500);
//  Serial.print(".");
//  }

//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
// }

// void reconnect() {
//  if(millis() - LastTry >= 5000){

//  Serial.print("Attempting MQTT connection...");
//  if (client.connect("ESP32Client")) {
//  Serial.println("connected");
//  client.subscribe(target_topic, 1); // Use QoS 1 for subscription
//  } else {
//  Serial.print("failed, rc=");
//  Serial.print(client.state());
//  Serial.println(" try again in 5 seconds");
//  LastTry = millis();
//  }
//  }
// }

// void loop() {
//  if (!client.connected()) {
//  reconnect();
//  }
//  else{
//  client.loop();

//  unsigned long now = millis();
//  if (now - lastMsg > 2000) {
//  lastMsg = now;
//  ++value;
//  snprintf (msg, MSG_BUFFER_SIZE, "hello world #%d", value);
//  Serial.print("Publish message: ");
//  Serial.println(msg);
//  client.publish("outTopic", msg, true);
//  }
//  }
// }
