#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

namespace app::globals::queue {

    void init();

    QueueHandle_t get_answer_queue();

}
