#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>

#define IS_WIFI_ALIVE_BIT    BIT0
#define IS_MQTT_ALIVE_BIT    BIT1
#define HAS_DATA_TO_SEND_BIT BIT2

#define IS_CONNECTED_BITS IS_WIFI_ALIVE_BIT | IS_MQTT_ALIVE_BIT

namespace app::globals::events {

    void init();

    EventGroupHandle_t get_system_events();

}
