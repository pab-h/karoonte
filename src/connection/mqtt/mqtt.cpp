#include "mqtt.hpp"

#include <WiFi.h>
#include <PubSubClient.h>

#include "app/globals/events/events.hpp"
#include "app/env.hpp"
#include "app/config.hpp"

using namespace app::globals;

namespace connection::mqtt {

    static WiFiClient   wifi_client;
    static PubSubClient mqtt_client(wifi_client);

    static char payload[8];    

    void topic_callback(char* topic, uint8_t* buffer, uint length) {
        
        memcpy(payload, buffer, length);
        payload[length] = '\0';

        Serial.printf("Recv: %s on %s\n", topic, payload);

        if (strcmp(topic, MQTT_ANSWER_TOPIC) == 0) {

            if (strcmp(payload, CORRECT_SIGNAL_PAYLOAD) == 0) {

                xEventGroupSetBits(
                    events::get_karoonte_events(),
                    IS_ANSWER_CORRECT_BIT
                );

            }

            if (strcmp(payload, INCORRECT_SIGNAL_PAYLOAD) == 0) {

                xEventGroupSetBits(
                    events::get_karoonte_events(),
                    IS_ANSWER_INCORRECT_BIT
                );

            }

        }

    }

    PubSubClient* get_client() {
        return &mqtt_client;
    }

    void init() {

        mqtt_client.setServer(MQTT_HOST, MQTT_PORT);
        mqtt_client.setCallback(topic_callback);

    }

}

