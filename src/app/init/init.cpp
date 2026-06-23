#include "init.hpp"

#include <Arduino.h>

#include "app/globals/semaphore/semaphore.hpp"
#include "app/globals/events/events.hpp"
#include "app/globals/queue/queue.hpp"

#include "connection/init/init.hpp"
#include "keyboard/init/init.hpp"

namespace app {

    void init() {

        Serial.begin(115200);

        globals::queue::init();
        globals::semaphore::init();
        globals::events::init();

        connection::init();
        keyboard::init();

    }

}