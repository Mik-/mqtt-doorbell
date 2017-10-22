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

#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

#ifdef DEBUG
    #define DSETUP() Serial.begin(115200); while (!Serial) { }
    #define DPRINT(...) Serial.print(__VA_ARGS__)
    #define DPRINTLN(...) Serial.println(__VA_ARGS__)
#else
    #define DSETUP()
    #define DPRINT(...) 
    #define DPRINTLN(...) 
#endif

#endif