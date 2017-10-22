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
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// #define DEBUG
#include "debug.h"

#include "MQTTController.h"

MQTTController::MQTTController(const char *broker, const char *clientId) {
    this->broker = broker;
    port = 1883;
    this->clientId = clientId;
    this->username = NULL;
    this->password = NULL;

    this->wifiClient = WiFiClient();
    this->mqttClient = PubSubClient(this->wifiClient);
}

void MQTTController::setCredentials(const char *username, const char *password) {
    this->username = username;
    this->password = password;
}

bool MQTTController::publish(const char *topic, const char *payload, bool retained) {
    if (!mqttClient.connected()) {
        doConnect();
    }

    DPRINT("Publishing topic '");
    DPRINT(topic);
    DPRINT("' with payload '");
    DPRINT(payload);
    DPRINTLN("'");
    
    mqttClient.publish(topic, payload, retained);
}

void MQTTController::disconnect() {
    if (mqttClient.connected()) {
        mqttClient.disconnect();
    }
}

bool MQTTController::doConnect() {
    if (!mqttClient.connected()) {
        DPRINT("Try to connect to MQTT broker ");
        DPRINT(broker);
        DPRINTLN(": ");

        mqttClient.setServer(broker, port);
        bool result;
        if (username != NULL) {
            result = mqttClient.connect(clientId, username, password);
        } else {
            result = mqttClient.connect(clientId);
        }

        DPRINTLN(result ? "connected." : "failed!");

        return result;
    } else {
        return true;
    }
}

