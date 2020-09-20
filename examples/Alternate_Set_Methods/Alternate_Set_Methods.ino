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

// Get random float method
float get_random_float() {
  float new_float;
  new_float = (float)random(1, 1000) / (float)random(1, 1000);
  return new_float;
}

// String event callback
void float_callback(float _new_float) {
  Serial.printf("(Global Function) my_float has changed to: \"%.6f\"\n", _new_float);
}

void setup() {
  // Start Serial
  Serial.begin(115200);
  Serial.println();
  Serial.println("********** Started Feature Variable Example **********");

  // Create a Feature based on a float
  Feature<float> my_float("my_float_name");
  my_float.addEventCallback(float_callback);

  // Assign the my_float a few values using the standard methods
  Serial.println("\n********** Standard Methods **********");
  my_float = get_random_float();
  my_float.setValue(get_random_float());

  // There are a few overrides you can provide to the set values function depending on what you want to do
  Serial.println("\n********** Events and Saving Control **********");
  my_float.setValue(get_random_float(), FEATURE_FIRE_EVENTS_SAVE_VALUES);
  my_float.setValue(get_random_float(), FEATURE_DO_NOT_FIRE_EVENTS);
  my_float.setValue(get_random_float(), FEATURE_DO_NOT_SAVE_VALUES);
  my_float.setValue(get_random_float(), FEATURE_DO_NOT_FIRE_EVENTS_OR_SAVE_VALUES);

  // Features also offer the operator() overloaded to set values
  Serial.println("\n********** Operator () Overloaded **********");
  my_float(get_random_float());
  my_float(get_random_float(), FEATURE_DO_NOT_FIRE_EVENTS_OR_SAVE_VALUES);

  // If you are using Arduino JSON you can set the value directly as a key value pair within an object
#if defined ARDUINOJSON_VERSION_MAJOR && ARDUINOJSON_VERSION_MAJOR == 6
  // Create new JSON Document and parse a string
  DynamicJsonDocument json(1024);
  JsonObject          jsonObject = json.to<JsonObject>();
  json["my_float_name"] = get_random_float();

  // Set relevent features in container using the same methods but passing a JsonObject
  Serial.println("\n********** ArduinoJSON **********");
  my_float.fromJson(jsonObject);
  // my_float.setValue(jsonObject, FEATURE_DO_NOT_FIRE_EVENTS);
  // my_float.setValue(jsonObject, FEATURE_DO_NOT_SAVE_VALUES);
  // my_float.setValue(jsonObject, FEATURE_DO_NOT_FIRE_EVENTS_OR_SAVE_VALUES);
#endif
}

void loop() {}