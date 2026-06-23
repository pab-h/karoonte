#include "mqtt.hpp"

#include <WiFi.h>
#include <PubSubClient.h>

#include "app/globals/events/events.hpp"
#include "app/env.hpp"

using namespace app::globals;

namespace connection::mqtt {

    static WiFiClient   wifi_client;
    static PubSubClient mqtt_client(wifi_client);
    
    static char payload[16];

    void subscriber_callback(char* topic, byte* buffer, unsigned int length) {
        
        memcpy(payload, buffer, length);
        payload[length] = '\0';

        if (strcmp(topic, MQTT_STATUS_TOPIC) == 0) {

            if (strcmp(payload, "START") == 0) {

                xEventGroupSetBits(
                    events::get_karoonte_events(),
                    IS_GAME_STARTED
                );

            } 
            
            if (strcmp(payload, "TIMEOUT") == 0) {

                xEventGroupClearBits(
                    events::get_karoonte_events(),
                    IS_GAME_STARTED
                );

            }

        }

    }

    PubSubClient* get_client() {
        return &mqtt_client;
    }

    void init() {

        mqtt_client.setServer(MQTT_HOST, MQTT_PORT);
        mqtt_client.setCallback(subscriber_callback);

        xEventGroupSetBits(
            events::get_system_events(),
            IS_MQTT_TOPIC_NOT_SUBSCRIBED_BIT
        );

    }

}

