#include "tasks.hpp"

#include <Arduino.h>
#include <WiFi.h>
#include <time.h>

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

#include "app/globals/semaphore/semaphore.hpp"
#include "app/globals/events/events.hpp"
#include "app/globals/queue/queue.hpp"

#include "connection/mqtt/mqtt.hpp"
#include "app/env.hpp" 

using namespace app::globals;
using namespace connection;

namespace connection::tasks {

    void publish_answer(void* pvParameters) {

        PubSubClient* client = mqtt::get_client();

        char answer;
        char payload[2];

        while (true) {

            xEventGroupWaitBits(
                events::get_system_events(),
                IS_CONNECTED_BITS,
                pdFALSE,
                pdTRUE,
                portMAX_DELAY
            );

            xEventGroupWaitBits(
                events::get_karoonte_events(),
                IS_GAME_STARTED,
                pdFALSE, 
                pdTRUE,
                portMAX_DELAY
            );

            xQueueReceive(
                queue::get_answer_queue(),
                &answer,
                portMAX_DELAY
            );

            Serial.printf("[CONN] Publish answer: %c\n", answer);

            snprintf(payload, sizeof(payload), "%c", answer);

            xSemaphoreTake(
                semaphore::get_wifi_mutex(), 
                portMAX_DELAY
            );

            client->publish(MQTT_ANSWER_TOPIC, payload);

            xSemaphoreGive(semaphore::get_wifi_mutex());

        }
    }

    void keep_subscription(void* pvParameters) {

        PubSubClient* client = mqtt::get_client();

        while (true) {

            xEventGroupWaitBits(
                events::get_system_events(),
                IS_CONNECTED_BITS | IS_MQTT_TOPIC_NOT_SUBSCRIBED_BIT,
                pdFALSE,
                pdTRUE,
                portMAX_DELAY
            );

            xSemaphoreTake(
                semaphore::get_wifi_mutex(),
                portMAX_DELAY
            );

            client->subscribe(MQTT_RESULT_TOPIC);
            client->subscribe(MQTT_STATUS_TOPIC);

            Serial.printf("[CONN] Subscribed on %s\n", MQTT_RESULT_TOPIC);
            Serial.printf("[CONN] Subscribed on %s\n", MQTT_STATUS_TOPIC);

            xSemaphoreGive(
                semaphore::get_wifi_mutex()
            );

            xEventGroupClearBits(
                events::get_system_events(),
                IS_MQTT_TOPIC_NOT_SUBSCRIBED_BIT
            );

        }

    }

    void keep_wifi_alive(void* pvParameters) {

        unsigned long start_attempt_time;

        while (true) {

            xSemaphoreTake(semaphore::get_wifi_mutex(), portMAX_DELAY);

            if (WiFi.status() == WL_CONNECTED) {

                xSemaphoreGive(semaphore::get_wifi_mutex());
                vTaskDelay(pdMS_TO_TICKS(1000));

                continue;

            }

            Serial.println("[CONN] WiFi disconnected");

            xEventGroupClearBits(
                events::get_system_events(),
                IS_WIFI_ALIVE_BIT
            );

            WiFi.mode(WIFI_STA);
            WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

            start_attempt_time = millis();

            while (
                WiFi.status() != WL_CONNECTED && 
                millis() - start_attempt_time < WIFI_TIMEOUT_MS
            ) {
                vTaskDelay(pdMS_TO_TICKS(100));
            }

            if (WiFi.status() != WL_CONNECTED) {
                
                xSemaphoreGive(semaphore::get_wifi_mutex());
                vTaskDelay(pdMS_TO_TICKS(5000));

                continue;
            
            } 

            Serial.println("[CONN] WiFi connected");

            xEventGroupSetBits(
                events::get_system_events(),
                IS_WIFI_ALIVE_BIT
            );

            xSemaphoreGive(semaphore::get_wifi_mutex());

        }

    }

    void keep_mqtt_alive(void* pvParameters) {

        PubSubClient* client = mqtt::get_client();

        while (true) {

            xEventGroupWaitBits(
                events::get_system_events(),
                IS_WIFI_ALIVE_BIT,
                pdFALSE,
                pdTRUE,
                portMAX_DELAY
            );

            xSemaphoreTake(semaphore::get_wifi_mutex(), portMAX_DELAY);

            if (!client->connected()) {

                xEventGroupClearBits(
                    events::get_system_events(),
                    IS_MQTT_ALIVE_BIT
                );

                xEventGroupSetBits(
                    events::get_system_events(),
                    IS_MQTT_TOPIC_NOT_SUBSCRIBED_BIT
                );

                if (!client->connect(MQTT_CLIENT_ID)) {

                    Serial.println("[CONN] MQTT failed");

                    xSemaphoreGive(semaphore::get_wifi_mutex());
                    vTaskDelay(pdMS_TO_TICKS(1000));

                    continue;

                }

                Serial.println("[CONN] MQTT connected");

                xEventGroupSetBits(
                    events::get_system_events(),
                    IS_MQTT_ALIVE_BIT
                );

            }

            client->loop();

            xSemaphoreGive(semaphore::get_wifi_mutex());

            vTaskDelay(pdMS_TO_TICKS(50));

        }

    }

}
