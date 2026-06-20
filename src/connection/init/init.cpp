#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "init.hpp"

#include "connection/tasks/tasks.hpp"

namespace connection {

    void init() {

        xTaskCreate(
            tasks::keep_wifi_alive,
            "Keep wifi alive",
            4096,
            NULL,
            1,
            NULL
        );

    }

}