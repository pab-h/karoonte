#include "mqtt.hpp"

#include <WiFi.h>
#include <PubSubClient.h>

#include "app/globals/events/events.hpp"
#include "app/env.hpp"

using namespace app::globals;

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

        xEventGroupSetBits(
            events::get_system_events(),
            IS_MQTT_TOPIC_NOT_SUBSCRIBED_BIT
        );

    }

}

