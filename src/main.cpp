#include <Arduino.h>

#include "app/init/init.hpp"

void setup() {

    app::init();

}

void loop() {
    vTaskDelete(NULL);
}