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

// #define DEBUG
#include "debug.h"

#include "WiFiController.h"

WiFiController::WiFiController(const char *ssid, const char *passphrase) {
    this->ssid = ssid;
    this->passphrase = passphrase;
    timeoutInSeconds = 20;
}

void WiFiController::setTimeout(unsigned long timeoutInSeconds) {
    this->timeoutInSeconds = timeoutInSeconds;
}

bool WiFiController::connect() {
    delay(10);
    
    DPRINTLN();
    DPRINT("Connecting to ");
    DPRINTLN(ssid);

    if (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, passphrase);
    }

    unsigned long wifiConnectStart = millis();

    while (WiFi.status() != WL_CONNECTED) {
        if (WiFi.status() == WL_CONNECT_FAILED) {
            DPRINTLN("Please verify credentials.");
            delay(timeoutInSeconds * 1000);
        }

        delay(500);
        DPRINT(".");

        // Check for timeout
        if (millis() - wifiConnectStart > timeoutInSeconds * 1000) {
            DPRINTLN("Failed to connect to Wifi (timeout)!");
            return false;
        }
    }
    
    DPRINTLN("");
    DPRINTLN("WiFi connected");
    DPRINT("IP address: ");
    DPRINTLN(WiFi.localIP());

    return true;
}