#include "buzzer.hpp"

#include <Arduino.h>
#include <driver/ledc.h>

#include "app/pins.hpp"

namespace music::buzzer {

    const uint8_t LEDC_CHANNEL = 0;
    const uint32_t LEDC_FREQ = 2000;
    const uint8_t LEDC_RES = 8;

    void init () {
        
        ledcSetup(LEDC_CHANNEL, LEDC_FREQ, LEDC_RES);
        ledcAttachPin(BUZZER_PIN, LEDC_CHANNEL);

    }

    void play_correct_song() {

        ledcWriteTone(BUZZER_PIN, 523);
        vTaskDelay(pdMS_TO_TICKS(100));
        
        ledcWriteTone(BUZZER_PIN, 659);
        vTaskDelay(pdMS_TO_TICKS(100));
        
        ledcWriteTone(BUZZER_PIN, 784);
        vTaskDelay(pdMS_TO_TICKS(120));
        
        ledcWriteTone(BUZZER_PIN, 1047);
        vTaskDelay(pdMS_TO_TICKS(200));

        ledcWriteTone(BUZZER_PIN, 0);

    }

    void play_incorrect_song() {

        ledcWriteTone(BUZZER_PIN, 392);
        vTaskDelay(pdMS_TO_TICKS(250));
        
        ledcWriteTone(BUZZER_PIN, 277);
        vTaskDelay(pdMS_TO_TICKS(400));

        ledcWriteTone(BUZZER_PIN, 0);

    }
    
}