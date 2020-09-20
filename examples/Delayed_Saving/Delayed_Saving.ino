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

// #include <ArduinoJson.h>
#include <Effortless_SPIFFS.h>
#include <FeatureVariables.h>

String getNewString() {
  char new_string[9] = {'\0'};
  for (int i = 0; i < 8; i++) {
    byte randomChar = random(0, 36);
    char newChar = randomChar + 'a';
    if (randomChar > 25) newChar = (randomChar - 26) + '0';
    new_string[i] = newChar;
  }
  new_string[8] = '\0';
  return (String)new_string;
}

void setup() {
  // Start Serial
  Serial.begin(115200);
  Serial.println();
  Serial.println("********** Started Feature Variable Example **********");

  // Create a Feature based on the Arduino String class - opens last value from flash automatically!
  Feature<String> my_string("my_string_name");
  Serial.printf("my_string opened as: \"%s\"\n", my_string.getValue().c_str());

  // Set the debug output of the feature to Serial
  my_string.setDebugOutput(&Serial);

  // Set the save timeout value in milliseconds
  my_string.setSaveTimeout(1000);

  // Set the feature value and wait for the debug output to show it saved!
  my_string = getNewString();
  Serial.printf("Pausing program for 2 seconds\n");
  delay(2000);
  Serial.printf("Resuming program\n");
  delay(1000);

  // Now try set it a bunch of times and watch the delay on saving the last value
  my_string = getNewString();
  my_string = getNewString();
  my_string = getNewString();
  my_string = getNewString();
  my_string = getNewString();
  Serial.printf("Pausing program for 2 seconds\n");
  delay(2000);
  Serial.printf("Resuming program\n");

  // End of example
  Serial.println("********** End of Feature Variable Example **********");
  delay(10000);
  ESP.restart();
}

void loop() {}