#include "init.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "music/buzzer/buzzer.hpp"
#include "music/tasks/tasks.hpp"

namespace music {

    void init() {

        buzzer::init();

        xTaskCreate(
            tasks::play_music,
            "Play music",
            4096,
            NULL,
            1,
            NULL
        );

    }

}