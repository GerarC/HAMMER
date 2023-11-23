#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <Arduino.h>
#include <include/conf.hpp>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <sstream>
#include "DHT.h"

using std::stringstream;

// Needed Objects
// Wifi
WiFiClient wifiClient;
// MQTT
PubSubClient mqttClient(wifiClient);
// Sensors
DHT dht(pin_dht, DHTTYPE);


// Functions
// Wifi
void setup_wifi();
// Mqtt
void mqttConnect();
void callback(char* topic, byte* message, unsigned int length);
//Sensors
void readWaterSensor();
void readDHTTemperature();
void readDHTHumidity();
void readLightSensor();
 

void setup() {
  Serial.begin(PORT_SPEED);
  // Initialize PINS
  pinMode(pin_water, INPUT);
  // Setup wifi
  setup_wifi();
  // MQTT setup
  mqttClient.setServer(broker_ip, 1883);
  mqttClient.setCallback(callback);
  //DHT Setup
  dht.begin();
}

void loop() {
  if (!mqttClient.connected()) {
    mqttConnect();
  }

  // Let PubSubClient library do his magic
  mqttClient.loop();
  readWaterSensor();
  readDHTTemperature();
  readDHTHumidity();
  readLightSensor();
  delay(1000 * 10);
}

// WIFI
void setup_wifi() {
  Serial.print("\nConnecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); // Connect to network
  while (WiFi.status() != WL_CONNECTED) { // Wait for connection
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


// MQTT
void mqttConnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqttClient.connect(ID)) Serial.println("OK");
    else { // Retry connection    
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);    
    }
  }
}

void callback(char* topic, byte* message, unsigned int length){}

// Sensors
void readWaterSensor(){
  int water_data =  analogRead(pin_water);
  stringstream ss;
  ss << "water:" << water_data;
  mqttClient.publish(topic_water, ss.str().c_str());
  Serial.println(ss.str().c_str());
}

void readDHTTemperature(){
  float temperature_data = dht.readTemperature();
  stringstream ss;
  ss << "temperature:" << temperature_data;
  mqttClient.publish(topic_water, ss.str().c_str());
  Serial.println(ss.str().c_str());
}

void readDHTHumidity(){
  float humidity_data = dht.readHumidity();
  stringstream ss;
  ss << "humidity:" << humidity_data;
  mqttClient.publish(topic_water, ss.str().c_str());
  Serial.println(ss.str().c_str());
}

void readLightSensor(){
  delay(10);
  int light_data = analogRead(pin_light);
  stringstream ss;
  ss << "light:" << light_data;
  mqttClient.publish(topic_water, ss.str().c_str());
  Serial.println(ss.str().c_str());
}