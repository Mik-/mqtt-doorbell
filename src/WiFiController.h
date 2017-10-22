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

#ifndef WiFiController_h
#define WiFiController_h

class WiFiController {
private:
    const char *ssid;
    const char *passphrase;
    unsigned long timeoutInSeconds;

public:
    WiFiController(const char *ssid, const char *passphrase);
    void setTimeout(unsigned long timeoutInSeconds);
    bool connect();
};

#endif