/*
Copyright (c) 2020 thebigpotatoe

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/

#include <Effortless_SPIFFS.h> // Optional
#include <FeatureVariables.h>

// Create a Global Feature - opens value from flash automatically when using Effortless_SPIFFS!
Feature<unsigned long> current_millis;

// Create a callback
void string_callback(unsigned long _current_millis) {
  Serial.printf("my_string has changed to: \"%u\"\n", _current_millis);
}

void setup() {
  // Add callback to Feature
  current_millis.addEventCallback(string_callback);
}

void loop() {
  // Assign millis() to Feature every second - saves value automatically when using Effortless_SPIFFS!
  current_millis = millis();
  delay(1000);
}