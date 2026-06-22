#pragma once

#include <Arduino.h>

namespace keyboard::types {

    struct ButtonData {
        char              key;
        volatile uint32_t last_press_time;
    };

}
