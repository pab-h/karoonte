#include "events.hpp"

namespace app::globals::events {

    static EventGroupHandle_t system_events; 

    void init() {
        system_events = xEventGroupCreate();
    }

    EventGroupHandle_t get_system_events() {
        return system_events;
    }

}

