#include "events.hpp"

namespace app::globals::events {

    static EventGroupHandle_t system_events; 
    static EventGroupHandle_t karoonte_events; 

    void init() {
        system_events   = xEventGroupCreate();
        karoonte_events = xEventGroupCreate();
    }

    EventGroupHandle_t get_karoonte_events() {
        return karoonte_events;
    }

    EventGroupHandle_t get_system_events() {
        return system_events;
    }

}

