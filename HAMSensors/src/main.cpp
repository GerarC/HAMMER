#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <Arduino.h>
#include <include/conf.hpp>
#include <PubSubClient.h>

// Functions

// Wifi
void setup_wifi();


// Mqtt
void mqttConnect(PubSubClient mqttClient);
void callback(char* topic, byte* message, unsigned int length);

// Wifi
WiFiClient wifiClient;

// MQTT
PubSubClient mqttClient(wifiClient); 

void setup() {
  //pinMode(pirPIN, INPUT);

  Serial.begin(PORT_SPEED);
  // Setup wifi
  setup_wifi();

  // MQTT setup
  mqttClient.setServer(broker_ip, 1883);
  mqttClient.setCallback(callback);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// WIFI
void setup_wifi() {
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); // Connect to network

  while (WiFi.status() != WL_CONNECTED) { // Wait for connection
    delay(500);
    Serial.print(".");
    WiFi.disconnect();
    delay(2000);
    WiFi.begin(ssid, password); 
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}



// MQTT
void mqttConnect(PubSubClient mqttClient) {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqttClient.connect(ID)) {
      Serial.println("OK");
      // It doesn't subscribe to anything
    } 
    else {     
      // Retry connection
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);    
    }
  }
}

void callback(char* topic, byte* message, unsigned int length){}
