#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

namespace app::globals::semaphore {

    void init();

    SemaphoreHandle_t get_wifi_mutex();

}
