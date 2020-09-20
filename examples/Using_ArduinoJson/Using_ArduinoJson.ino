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

void setup() {
  // Start Serial
  Serial.begin(115200);
  Serial.println();
  Serial.println("********** Started Feature Variable Example **********");

  // Create a Feature based on a float
  Feature<float> my_float("my_float_name", get_random_float());

  // Create new JSON Document and fill it with data
  DynamicJsonDocument json(1024);
  JsonObject          jsonObject = json.to<JsonObject>();
  jsonObject["value1"] = get_random_float();
  jsonObject["value2"] = "hello world";

  // Set the key value pair in the JSON Object
  bool retval = my_float.toJson(jsonObject);
  if (retval) {
    Serial.print("[setup] - Successfully set the JSON key value pair in object: \n");
    serializeJsonPretty(json, Serial);
    Serial.println();
  } else {
    Serial.print("[setup] - Failed to set JSON value from Feature value\n");
  }

  // Let's change the value in the JSON object so we can use it to set the value of teh Feature
  Serial.print("\n[setup] - New JSON object values: \n");
  jsonObject["my_float_name"] = get_random_float();
  serializeJsonPretty(json, Serial);
  Serial.println();

  // Set the Feature from the JSON object
  Serial.print("\n[setup] - Setting Feature value from JSON object:\n");
  retval = my_float.fromJson(jsonObject);
  if (retval) {
    Serial.printf("[setup] - Successfully set Feature value from JSON object as: %.6f\n", my_float.getValue());
  } else {
    Serial.print("[setup] - Failed to set Feature value from JSON object\n");
  }
}

void loop() {
}