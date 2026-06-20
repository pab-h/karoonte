#include "mqtt.hpp"

#include <WiFi.h>
#include <PubSubClient.h>

#include "app/env.hpp"

namespace connection::mqtt {

    static WiFiClient   wifi_client;
    static PubSubClient mqtt_client(wifi_client);

    void topic_callback(char* topic, uint8_t* payload, uint length) {
        
    }

    PubSubClient* get_client() {
        return &mqtt_client;
    }

    void init() {

        mqtt_client.setServer(MQTT_HOST, MQTT_PORT);
        mqtt_client.setCallback(topic_callback);

    }

}

