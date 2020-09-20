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

#define FEATURE_DEBUG_OBJECT &Serial

#include <ArduinoJson.h>
#include <Effortless_SPIFFS.h>
#include <FeatureVariables.h>

// Random String creator
String get_random_string() {
  char new_string[9] = {'\0'};
  for (int i = 0; i < 8; i++) {
    byte randomChar = random(0, 36);
    char newChar = randomChar + 'a';
    if (randomChar > 25) newChar = (randomChar - 26) + '0';
    new_string[i] = newChar;
  }
  new_string[8] = '\0';
  return String(new_string);
}

// String event callback
void string_callback(String _new_string) {
  Serial.printf("(Global Function) my_string has changed to: \"%s\"\n", _new_string.c_str());
}

void setup() {
  // Start Serial
  Serial.begin(115200);
  Serial.println();
  Serial.println("********** Started Feature Variable Example **********");

  // Create a Feature based on the Arduino String class - opens last value from flash automatically!
  Feature<String> my_string("my_string_name");
  Serial.printf("my_string opened as: \"%s\"\n", my_string.getValue().c_str());

  // There also exists two other constructors to allow you to set without a name for the Feature or set its value and eventFlag on creation
  // Feature<String> my_string;
  // Feature<String> my_string("my_string_name", "default_string", FEATURE_FIRE_EVENTS_SAVE_VALUES);

  // Add as many callbacks as you want to the Features
  my_string.addEventCallback(string_callback);
  my_string.addEventCallback([&](String _new_string) {
    Serial.printf("(Lambda Function) my_string has changed to: \"%s\"\n", _new_string.c_str());
  });

  // Assign the new_string a few values - Watch the events fire and automatically save the values to flash!
  my_string = "Hello";
  my_string.setValue("World");

  // There is a global events flags value that allows you to control how the feature works internally by default. This is accessable through two helper methods.
  my_string.allowEvents(false);
  my_string.allowSaving(false);
  my_string.setValue("No Events or Saving Globally!");

  // There are a few overrides you can provide to the setValues function which temporarily allow you to control the way the feature works
  my_string.setValue("Events and Saving!", FEATURE_FIRE_EVENTS_SAVE_VALUES);
  my_string.setValue("No Events!", FEATURE_DO_NOT_FIRE_EVENTS);
  my_string.setValue("No Saving!", FEATURE_DO_NOT_SAVE_VALUES);
  my_string.setValue("No Events or Saving!", FEATURE_DO_NOT_FIRE_EVENTS_OR_SAVE_VALUES);

  // Create a random 32 byte string for this example to save to flash for reboot
  my_string.allowEvents();
  my_string.allowSaving();
  my_string = get_random_string();

  // End of example
  Serial.println("********** End of Feature Variable Example **********");
  delay(10000);
  ESP.restart();
}

void loop() {}