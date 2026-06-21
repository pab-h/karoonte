#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "init.hpp"

#include "connection/tasks/tasks.hpp"
#include "connection/mqtt/mqtt.hpp"

namespace connection {

    void init() {

        mqtt::init();

        xTaskCreate(
            tasks::keep_wifi_alive,
            "Keep wifi alive",
            4096,
            NULL,
            1,
            NULL
        );

        xTaskCreate(
            tasks::keep_mqtt_alive,
            "Keep mqtt alive",
            4096,
            NULL,
            1,
            NULL
        );

        xTaskCreate(
            tasks::keep_subscription,
            "Keep subscription",
            4096,
            NULL,
            1,
            NULL
        );

    }

}