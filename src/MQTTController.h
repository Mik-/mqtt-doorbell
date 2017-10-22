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

#ifndef MQTTController_h
#define MQTTController_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class MQTTController {
private:
    const char *broker;
    int port;
    const char *clientId;
    const char *username;
    const char *password;

    WiFiClient wifiClient;
    PubSubClient mqttClient;

    bool doConnect();
public:
    MQTTController(const char *broker, const char *clientId);
    void setCredentials(const char *username, const char *password);
    bool publish(const char *topic, const char *payload, bool retained);
    void disconnect();
};

#endif