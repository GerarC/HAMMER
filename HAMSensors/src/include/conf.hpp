#ifndef CONF_HPP
#define CONF_HPP

// Esp Configuration
const int PORT_SPEED = 9600;

// WiFi parameters
const char* ssid = "GerarC";
const char* password = "Baracunatana";

/// MQTT Configuration
// IP & Thing name
const char* broker_ip = "192.168.146.206"; // IP address of your MQTT 
const char *ID = "sensors";  // Name of our device, must be unique

// Topics
const char *water_topic = "hammer/water_out"; 
const char *temperature_topic = "hammer/temperature_out"; 
const char *himidity_topic = "hammer/humidity_out"; 
const char *light_topic = "hammer/light_out"; 


// Pin configuration
const int pin_water = 34;
const int pin_temperature = 35;
const int pin_light = 25;

#endif//CONF_H