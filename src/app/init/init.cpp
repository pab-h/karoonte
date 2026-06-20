#include "init.hpp"

#include <Arduino.h>

#include "app/globals/semaphore/semaphore.hpp"
#include "app/globals/events/events.hpp"

#include "connection/init/init.hpp"

namespace app {

    void init() {

        Serial.begin(115200);

        globals::semaphore::init();
        globals::events::init();

        connection::init();

    }

}