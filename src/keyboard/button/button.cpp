#include "button.hpp"

#include <Arduino.h>

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "app/globals/queue/queue.hpp"
#include "keyboard/types/types.hpp"

using namespace app::globals;
using namespace keyboard::types;

namespace keyboard::button {

    void IRAM_ATTR button_ISR(void* arg) {
        
        ButtonData* button = static_cast<ButtonData*>(arg);
        
        uint32_t current_time = millis();

        if (current_time - button->last_press_time > 500) {
            
            button->last_press_time = current_time;
            
            BaseType_t xHigherPriorityTaskWoken = pdFALSE;
            
            xQueueSendFromISR(
                queue::get_answer_queue(),
                &(button->key), 
                &xHigherPriorityTaskWoken
            );
            
            if(xHigherPriorityTaskWoken) {
                portYIELD_FROM_ISR();
            }
            
        }

    }

}

