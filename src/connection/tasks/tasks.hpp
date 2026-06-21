#pragma once

namespace connection::tasks {

    void keep_wifi_alive(void* pvParameters);
    void keep_mqtt_alive(void* pvParameters);
    void keep_subscription(void* pvParameters);

}
