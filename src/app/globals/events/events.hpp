#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>

// System events

#define IS_WIFI_ALIVE_BIT                BIT0
#define IS_MQTT_ALIVE_BIT                BIT1
#define IS_MQTT_TOPIC_NOT_SUBSCRIBED_BIT BIT2

#define IS_CONNECTED_BITS IS_WIFI_ALIVE_BIT | IS_MQTT_ALIVE_BIT

// Karronte events

#define IS_ANSWER_CORRECT_BIT   BIT0
#define IS_ANSWER_INCORRECT_BIT BIT1

namespace app::globals::events {

    void init();

    EventGroupHandle_t get_system_events();
    EventGroupHandle_t get_karoonte_events();

}
