/*
Copyright 2017 Michael Neuendorf

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <Arduino.h>

extern "C" {
    #include <user_interface.h>
}

#include "user_config.h"
#include "WiFiController.h"
#include "MQTTController.h"

// #define DEBUG
#include "debug.h"

#define BATTERY_VOLTAGE_PIN A0

void setup() {
    // Setup debugging
    DSETUP(); 

    // Distinguish between power on and reset
    rst_info *resetInfo;
    resetInfo = ESP.getResetInfoPtr();

    if (resetInfo->reason == REASON_DEEP_SLEEP_AWAKE) {
        DPRINTLN("");
        DPRINTLN("I'm awake");
    
        WiFiController wifi(WIFI_SSID1, WIFI_PASS1);
        wifi.setTimeout(WIFI_TIMEOUT);
    
        if (wifi.connect()) {
            MQTTController mqtt(MQTT_BROKER, MQTT_CLIENT_ID);
            mqtt.setCredentials(MQTT_USER, MQTT_PASSWORD);
            mqtt.publish(MQTT_TOPIC_BELL, MQTT_PAYLOAD_RING_ON, false);
            delay(500);
            mqtt.publish(MQTT_TOPIC_BELL, MQTT_PAYLOAD_RING_OFF, false);
            
            // Get battery voltage
            // 130k + 220k / 100k -> Max voltage: 4.5V
            int sensorValue = analogRead(BATTERY_VOLTAGE_PIN);
            float batteryVoltage = sensorValue * (4.5 / 1024);
    
            String voltageAsString = String(batteryVoltage, 3);
            mqtt.publish(MQTT_TOPIC_VOLTAGE, voltageAsString.c_str(), true);
            if (batteryVoltage >= BATTERY_LOW_THRESHOLD) {
                mqtt.publish(MQTT_TOPIC_BATTERY, MQTT_PAYLOAD_BATTERY_OK, true);
            } else {
                mqtt.publish(MQTT_TOPIC_BATTERY, MQTT_PAYLOAD_BATTERY_LOW, true);
            }
    
            mqtt.disconnect();
        }
    } else {
        #ifdef DEBUG
        delay(5000);
        DPRINT("Restart reason: ");
        DPRINTLN(ESP.getResetInfo());
        #endif
    }

    DPRINTLN("");
    DPRINTLN("Going into deep sleep.");
   
    ESP.deepSleep(0);
    delay(100);
}

void loop() {
    // no loop code needed
}