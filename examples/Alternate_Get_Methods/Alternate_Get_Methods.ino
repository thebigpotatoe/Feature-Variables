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

  // Features offer the operator () overloaded to get values
  float float_value = my_float;
  Serial.printf("[setup] - float_value is \"%.6f\"\n", float_value);

  // There also exists a get method to get the value and previous values of the Feature
  my_float = get_random_float();
  float current_value = my_float.getValue();
  float previous_value = my_float.getPreviousValue();
  Serial.printf("[setup] - current_value is \"%.6f\"\n", current_value);
  Serial.printf("[setup] - previous_value was \"%.6f\"\n", previous_value);

  // For convenience the value is can be converted to a string
  Serial.printf("[setup] - my_float as string is \"%s\"\n", my_float.toString().c_str());

  // The name of the feature is accessable using its get method
  const char* feature_name = my_float.getName();
  Serial.printf("[setup] - Name of feature is \"%s\"\n", feature_name);

  // You can also get the filename where the data is being stored.
  char filename[32];
  my_float.getFilename(filename);
  Serial.printf("[setup] - Filename is \"%s\"\n", filename);

  // Features of the same type can be assigned from one to another safely also transfering all callbacks
  Feature<float> my_float_2 = my_float;
  Feature<float> my_float_3(my_float);
  Serial.printf("[setup] - %s value is \"%.6f\"\n", my_float_2.getName(), my_float_2.getValue());
  Serial.printf("[setup] - %s value is \"%.6f\"\n", my_float_3.getName(), my_float_3.getValue());

// As a further convenience, ArduinoJson Objects can be passed to the feature to inject a new key value pair
// of the name and value of the feature within the object
#if defined ARDUINOJSON_VERSION_MAJOR && ARDUINOJSON_VERSION_MAJOR == 6
  // Create new JSON Document and parse a string
  DynamicJsonDocument json(1024);
  JsonObject          jsonObject = json.to<JsonObject>();
  jsonObject["value1"] = 65403654.65464;
  jsonObject["value2"] = "hello world";

  // Set the key value pair in the JSON Object
  bool retval = my_float.toJson(jsonObject);

  // Print the result
  if (retval) {
    Serial.print("[setup] - Successfully set the JSON key value pair in object: \n");
    serializeJsonPretty(json, Serial);
    Serial.println();
  } else {
    Serial.println("[setup] - Failed to set JSON key pair values in object");
  }
#endif
}

void loop() {
}