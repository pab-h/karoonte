#include "semaphore.hpp"

namespace app::globals::semaphore {

    static SemaphoreHandle_t wifi_mutex;

    void init() {

        wifi_mutex  = xSemaphoreCreateMutex();

    }

    SemaphoreHandle_t get_wifi_mutex() {
        return wifi_mutex;
    }

}

