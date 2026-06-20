#pragma once

#include <PubSubClient.h>

namespace connection::mqtt {

    void topic_callback(char* topic, uint8_t* message, uint length);
    void init();

    PubSubClient* get_client();

}