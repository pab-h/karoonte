#include "tasks.hpp"

#include <Arduino.h>
#include <WiFi.h>
#include <time.h>

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

#include "app/env.hpp"
#include "app/globals/semaphore/semaphore.hpp"
#include "app/globals/events/events.hpp"

using namespace app::globals;

namespace connection::tasks {

    void keep_wifi_alive(void* pvParameters) {

        unsigned long start_attempt_time;

        while (true) {

            xSemaphoreTake(semaphore::get_wifi_mutex(), portMAX_DELAY);

            if (WiFi.status() == WL_CONNECTED) {

                xSemaphoreGive(semaphore::get_wifi_mutex());
                vTaskDelay(pdMS_TO_TICKS(1000));

                Serial.println("[CONN] WiFi still connected");

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

}
