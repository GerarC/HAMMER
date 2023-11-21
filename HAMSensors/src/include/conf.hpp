#ifndef CONF_HPP
#define CONF_HPP

// ESP Configuration
const int PORT_SPEED = 9600;

// WiFi parameters
const char* ssid = "GerarC";
const char* password = "Baracunatana";

/// MQTT Configuration
// IP & Thing name
const char* broker_ip = "192.168.146.206"; // IP address of your MQTT 
const char *ID = "sensors";  // Name of our device, must be unique

// Topics
const char *topic_water = "hammer/water_out"; 
const char *topic_temperature = "hammer/temperature_out"; 
const char *topic_humidity = "hammer/humidity_out"; 
const char *topic_light = "hammer/light_out"; 


// Pin configuration
#define DHTTYPE DHT11
const int pin_water = 35;
const int pin_dht = 32;
const int pin_light = 33;

// Pin Input

#endif//CONF_H