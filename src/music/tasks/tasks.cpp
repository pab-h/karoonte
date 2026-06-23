#include <Arduino.h>

#include "tasks.hpp"

#include "app/globals/events/events.hpp"
#include "music/buzzer/buzzer.hpp"

using namespace app::globals;

namespace music::tasks {

    void play_music(void* pvParameters) {

        EventBits_t bits;

        const EventBits_t bits_to_watch = IS_ANSWER_CORRECT_BIT | IS_ANSWER_INCORRECT_BIT;

        while(true) {

            bits = xEventGroupWaitBits(
                events::get_karoonte_events(),
                bits_to_watch,
                pdTRUE,        
                pdFALSE,       
                portMAX_DELAY  
            );

            Serial.printf("[DEBUG] Task acordou! Bits detectados: %d\n", bits);

            if ((bits & IS_ANSWER_CORRECT_BIT) != 0) {
                Serial.println("[DEBUG] Tocando som de ACERTO...");
                buzzer::play_correct_song();
            }

            if ((bits & IS_ANSWER_INCORRECT_BIT) != 0) {
                Serial.println("[DEBUG] Tocando som de ERRO...");
                buzzer::play_incorrect_song();
            }
            
        }
    }
}