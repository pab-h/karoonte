#pragma once

#define WIFI_SSID       "WiFi_Legal"
#define WIFI_PASSWORD   "SenhaForte"
#define WIFI_TIMEOUT_MS 5000

#define MQTT_HOST         "broker.hivemq.com"
#define MQTT_PORT         1883
#define MQTT_TOPIC_PREFIX "karoonte"
#define MQTT_CLIENT_ID    "aladdin"

#define MQTT_ANSWER_TOPIC MQTT_TOPIC_PREFIX "/" MQTT_CLIENT_ID "/" "answer"
#define MQTT_RESULT_TOPIC MQTT_TOPIC_PREFIX "/" MQTT_CLIENT_ID "/" "result"
#define MQTT_STATUS_TOPIC MQTT_TOPIC_PREFIX "/" "status"