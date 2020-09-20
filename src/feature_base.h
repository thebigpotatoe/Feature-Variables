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

#ifndef FEATURE_BASE_h
#define FEATURE_BASE_h

// std libraries
#include <functional>
#include <string>

// Arduino Framework Libraries
#ifdef ARDUINO
#include <Print.h>
#include <Ticker.h>
#else
#warning "Feature Variables uses Arduino for some functionality. Compile with the Arduino framework for these features"
#endif

// Internal Includes
#include "feature_macros.h"
#include "feature_internal.h"
#include "feature_supported_types.h"

namespace FeatureVariables {
  // Base Class
  class FeatureBase {
   public:  // supported types
   public:  // Constructors
    FeatureBase() {
      // Assign a random name on init
      char newName[33] = {'\0'};
      for (int i = 0; i < 32; i++) {
        char randomChar = rand() % 37;
        char newChar = randomChar + 'a';
        if (randomChar > 25) newChar = (randomChar - 26) + '0';
        newName[i] = newChar;
      }
      newName[32] = '\0';
      setName(newName);
    };
    FeatureBase(const char* _name) {
      setName(_name);
    };
    virtual ~FeatureBase(){};

   public:  // Name Methods
    const char* getName() {
      return name;
    }
    bool setName(const char* _name) {
      if (_name && snprintf(name, 32, "%s", _name) > 0) return true;
      return false;
    }

   public:  // Public Get type methods
    SupportedTypes getType() {
      return type;
    }

   protected:  // Internal set type methods
    // Bool setType implimentation
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, bool), void) setType() {
      type = SupportedTypes::BOOL;
    }

    // Floating point setType implimentation
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, float), void) setType() {
      type = SupportedTypes::FLOAT;
    }
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, double), void) setType() {
      type = SupportedTypes::DOUBLE;
    }

    // Signed setType implimentation
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, signed char), void) setType() {
      type = SupportedTypes::SIGNED_CHAR;
    }
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, signed int), void) setType() {
      type = SupportedTypes::SIGNED_INT;
    }
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, signed short), void) setType() {
      type = SupportedTypes::SIGNED_SHORT;
    }
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, signed long), void) setType() {
      type = SupportedTypes::SIGNED_LONG;
    }

    // Unsigned setType implimentation
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, unsigned char), void) setType() {
      type = SupportedTypes::UNSIGNED_CHAR;
    }
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, unsigned int), void) setType() {
      type = SupportedTypes::UNSIGNED_INT;
    }
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, unsigned short), void) setType() {
      type = SupportedTypes::UNSIGNED_SHORT;
    }
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, unsigned long), void) setType() {
      type = SupportedTypes::UNSIGNED_LONG;
    }

    // String type setType implimentation
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, char*), void) setType() {
      type = SupportedTypes::CHAR_PTR;
    }
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, const char*), void) setType() {
      type = SupportedTypes::CONST_CHAR_PTR;
    }
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, std::string), void) setType() {
      type = SupportedTypes::STD_STRING;
    }

#ifdef ARDUINO
    // Arduino String setType implimentation
    template <class T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(T, String), void) setType() {
      type = SupportedTypes::STRING;
    }
#endif

#if defined ARDUINOJSON_VERSION_MAJOR && ARDUINOJSON_VERSION_MAJOR == 6
   public:  // Arduino JSON Get and Set
    virtual bool toJson(JsonObject& json) = 0;
    virtual bool fromJson(JsonObject& json, uint8_t _fireEvents = FEATURE_FIRE_EVENTS_SAVE_VALUES) = 0;
#endif

   protected:  // Public type storage
    SupportedTypes type = SupportedTypes::UNSUPPORTED;

   protected:  // Internal name storage
    char name[33];
  };

}  // namespace FeatureVariables

#endif