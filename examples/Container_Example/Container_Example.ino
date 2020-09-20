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
// #include <vector.h>

// Feature Container
std::vector<FeatureBase*> feature_vector;

// Helpful methods
float get_random_float() {
  float new_float;
  new_float = (float)random(1, 1000) / (float)random(1, 1000);
  return new_float;
}

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

// Callbacks
void float_callback(float _new_float) {
  Serial.printf("(Global Function) my_float has changed to: \"%.6f\"\n", _new_float);
}

void string_callback(String _new_string) {
  Serial.printf("(Global Function) my_string has changed to: \"%s\"\n", _new_string.c_str());
}

void double_callback(double _new_double) {
  Serial.printf("(Global Function) my_double has changed to: \"%.6f\"\n", _new_double);
}

void setup() {
  // Start Serial
  Serial.begin(115200);
  Serial.println();
  Serial.println("********** Started Feature Variable Example **********");

  // Create a few features
  Feature<String> my_string("my_string_name");
  Feature<double> my_double("my_double_name");
  Feature<float>  my_float("my_float_name");

  // Set some event callbacks
  my_string.addEventCallback(string_callback);
  my_double.addEventCallback(double_callback);
  my_float.addEventCallback(float_callback);

  // Add the Features to the container
  feature_vector.push_back(&my_string);
  feature_vector.push_back(&my_double);
  feature_vector.push_back(&my_float);

  // When using Features in a container two methods to get or modify the feature exist depending on the use of ArduinoJSON.
  // The first is using inbuilt safe casting, the second leverages the ArduinoJSON library to syncronise the value of a JSON object
  // and the Feature.

  // Modify relevent features in container using safe casting methods
  for (auto feature : feature_vector) {
    // Cast feature safely - will only work for string types in this example, ignoring the other types
    Feature<String>* my_string_ptr = FeatureVariables::safe_cast<String>(feature);
    Serial.println("\n********** Pointer Safe Cast **********");
    Serial.printf("Cast for feature named \"%s\" %s\n", feature->getName(), (my_string_ptr) ? "succeeded" : "failed");

    // An example of how to use the pointer safely would be to check if it was null and check the name
    if (my_string_ptr && strcmp(my_string_ptr->getName(), "my_string_name") == 0) {
      my_string_ptr->setValue("Updated from safely cast pointer");
    }

    // Without casting directly, you can get the value safe and easy using safe_get<T>()
    // This will return the value if the cast succeeded or a null value of the type attempted to cast to
    String my_string_value = FeatureVariables::safe_get<String>(feature);
    Serial.println("********** Pointer Safe Get **********");
    Serial.printf("Value for feature named \"%s\" was \"%s\"\n", feature->getName(), (my_string_value.length()) ? my_string_value.c_str() : "EMPTY");

    // Without casting directly, you can set the value safe and easy using safe_set<T>()
    // This will set the value if the types requested and the feature's type match
    Serial.println("********** Pointer Safe Set **********");
    FeatureVariables::safe_set<String>(feature, "Saving with Events!");
    FeatureVariables::safe_set<String>(feature, "Saving Only!", FEATURE_DO_NOT_FIRE_EVENTS);
    FeatureVariables::safe_set<String>(feature, "Events Only!", FEATURE_DO_NOT_SAVE_VALUES);
    FeatureVariables::safe_set<String>(feature, "No Saving or Events!", FEATURE_DO_NOT_FIRE_EVENTS_OR_SAVE_VALUES);
  }


#if defined ARDUINOJSON_VERSION_MAJOR && ARDUINOJSON_VERSION_MAJOR == 6
  // Create new JSON Document and parse a string
  DynamicJsonDocument json(1024);
  const char*         jsonString = "{\"my_string_name\": 65403654.65464}";
  deserializeJson(json, jsonString);
  JsonObject jsonObject = json.to<JsonObject>();

  // Set relevent features in container using the same methods but passing a JsonObject
  for (auto feature : feature_vector) {
    feature->fromJson(jsonObject);
    // feature->setValue(jsonObject, FEATURE_DO_NOT_FIRE_EVENTS);
    // feature->setValue(jsonObject, FEATURE_DO_NOT_SAVE_VALUES);
    // feature->setValue(jsonObject, FEATURE_DO_NOT_FIRE_EVENTS_OR_SAVE_VALUES);
  }
#endif
}

void loop() {}