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

void setup() {
  // Start Serial
  Serial.begin(115200);
  Serial.println();
  Serial.println("********** Started Feature Variable Example **********");

  // Booleans
  Feature<bool> Boolean("Bool");

  // Floating Points
  Feature<float>  Float("Float");
  Feature<double> Double("double");

  // Signed Integers
  Feature<signed char>  signedchar("signed char");
  Feature<signed int>   signedint("signed int");
  Feature<signed short> signedshort("signed short");
  Feature<signed long>  signedlong("signed long");

  // Unsigned Integers
  Feature<unsigned char>  unsignedchar("unsigned char");
  Feature<unsigned int>   unsignedint("unsigned int");
  Feature<unsigned short> unsignedshort("unsigned short");
  Feature<unsigned long>  unsignedlong("unsigned long");

  // Character Types
  Feature<char *>       Char("char");
  Feature<const char *> constchar("const char");
  Feature<String>       Stringy("String");
  Feature<std::string>  stdString("std::string");

  // Debug
  Serial.println("********** Setting New Values **********");

  // Boolean
  Serial.println(Boolean.getName());
  Serial.println(Boolean.getValue());
  Boolean = true;
  Serial.println(Boolean.getValue());
  Serial.println();

  // Floats
  Serial.println(Float.getName());
  Serial.println(Float.getValue());
  Float = 10.102;
  Serial.println(Float.getValue());
  Serial.println();

  Serial.println(Double.getName());
  Serial.println(Double.getValue());
  Double = 10.102;
  Serial.println(Double.getValue());
  Serial.println();

  // Signed
  Serial.println(signedchar.getName());
  Serial.println((signedchar.getValue()));
  signedchar = 10;
  Serial.println((signedchar.getValue()));
  Serial.println();

  Serial.println(signedint.getName());
  Serial.println((signedint.getValue()));
  signedint = 10;
  Serial.println((signedint.getValue()));
  Serial.println();

  Serial.println(signedshort.getName());
  Serial.println((signedshort.getValue()));
  signedshort = 10;
  Serial.println((signedshort.getValue()));
  Serial.println();

  Serial.println(signedlong.getName());
  Serial.println((signedlong.getValue()));
  signedlong = 10;
  Serial.println((signedlong.getValue()));
  Serial.println();

  // Unsigned
  Serial.println(unsignedchar.getName());
  Serial.println((unsignedchar.getValue()));
  unsignedchar = 10;
  Serial.println((unsignedchar.getValue()));
  Serial.println();

  Serial.println(unsignedint.getName());
  Serial.println((unsignedint.getValue()));
  unsignedint = 10;
  Serial.println((unsignedint.getValue()));
  Serial.println();

  Serial.println(unsignedshort.getName());
  Serial.println((unsignedshort.getValue()));
  unsignedshort = 10;
  Serial.println((unsignedshort.getValue()));
  Serial.println();

  Serial.println(unsignedlong.getName());
  Serial.println((unsignedlong.getValue()));
  unsignedlong = 10;
  Serial.println((unsignedlong.getValue()));
  Serial.println();

  // Char*
  Serial.println(Char.getName());
  Serial.println(Char.getValue());
  Char = "Test";
  Serial.println(Char.getValue());
  Serial.println();

  // const char*
  Serial.println(constchar.getName());
  Serial.println(constchar.getValue());
  Serial.write(constchar.getValue());
  constchar = "Test";
  Serial.println(constchar.getValue());
  Serial.println();

  // Arduino String
  Serial.println(Stringy.getName());
  Serial.println(Stringy.getValue());
  Stringy = "Test";
  Serial.println(Stringy.getValue());
  Serial.println();

  // std::string
  Serial.println(stdString.getName());
  Serial.println((stdString.getValue().c_str()));
  stdString = "Test";
  Serial.println((stdString.getValue().c_str()));
  Serial.println();

  // End of example
  Serial.println("********** End of Feature Variable Example **********");
}

void loop() {}