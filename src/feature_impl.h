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

#ifndef FEATURE_IMPL_h
#define FEATURE_IMPL_h

// std libraries
#include <functional>
#include <string>
#include <vector>

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
#include "feature_base.h"

namespace FeatureVariables {
  // Feature Template Class
  template <class T>
  class Feature : public FeatureBase {
   private:  // Typedefs
    typedef std::function<void(T)>                  eventCallback;
    typedef std::vector<eventCallback>              eventCallbackVector;
    typedef std::function<bool(const T&, const T&)> filterCallback;
    typedef std::vector<filterCallback>             filterCallbackVector;
    typedef std::function<void(T&)>                 modifierCallback;
    typedef std::vector<modifierCallback>           modifierCallbackVector;

   public:  // Constructors
    Feature() : FeatureBase(), value(), previousValue() { init(nullptr); }
    Feature(const char* _name) : FeatureBase(_name), value(), previousValue() { init(nullptr); }
    Feature(const char* _name, T _value, uint8_t _eventSettings = true) : FeatureBase(_name), value(_value), previousValue(_value), eventFlags(_eventSettings) { init(&_value); }
    Feature(const Feature& other) {
      value = other.value;
      previousValue = other.previousValue;
      eventFlags = other.eventFlags;
      saveDelay = other.saveDelay;
      eventsVector = other.eventsVector;
      filtersVector = other.filtersVector;
    }
    ~Feature() {}

   protected:  // Initialisation
    void init(T* init_value) {
      // Set the type for the base class
      setType<T>();

      // Set the default parity filter
      addFilter([=](T _value, T _previousValue) { return _value != _previousValue; });

#if defined EFFORTLESS_SPIFFS_VERSION_MAJOR && EFFORTLESS_SPIFFS_VERSION_MAJOR == 2
#if defined ARDUINO
      // Add debug to the SPIFFS class
      fileSystem.setDebugOutput(logger);
#endif

      // Open values from flash if set to
      if (!init_value && eventFlags & FEATURE_SAVE_MASK) openValue();
#endif
    }

   public:  // Operators
    operator T() {
      return value;
    }
    bool operator()(const T _value) {
      return setValue(_value);
    }
    bool operator()(const T _value, uint8_t _fireEvents) {
      return setValue(_value, _fireEvents);
    }
    Feature& operator=(Feature other) {
      std::swap(other.value, value);
      std::swap(other.previousValue, previousValue);
      std::swap(other.eventFlags, eventFlags);
      std::swap(other.saveDelay, saveDelay);
      eventsVector.swap(other.eventsVector);
      return *this;
    }

    template <typename U = T>
    void operator=(const T _value) {
      setValue(_value);
    }

   public:  // Setters and Getters
    virtual T getValue() {
      return value;
    };
    virtual T getPreviousValue() {
      return previousValue;
    };
    virtual bool setValue(T _value, uint8_t _fireEvents = 0xff) {
      // Cycle through the modifiers first before filtering
      for (auto modifier : modifiersVector) {
        modifier(_value);
      }

      //  Run through filters
      bool filterBool = true;
      for (auto filter : filtersVector) {
        if (!filter(_value, value)) return false;
      }

      // Check if the incoming value is different
      // if (!valueCmp(_value)) {
      if (filterBool) {
        // Store the new and last value
        previousValue = value;
        value = _value;

        // Debug output
        if (logger) logger->printf("[%s] - Value set to \"%s\"\n", name, toString().c_str());

        // Override current storage settings
        if (_fireEvents == 0xFF) _fireEvents = eventFlags;

        // Call the event callbacks
        if (_fireEvents & FEATURE_EVENTS_MASK) fireEventCallbacks();

#if defined EFFORTLESS_SPIFFS_VERSION_MAJOR && EFFORTLESS_SPIFFS_VERSION_MAJOR == 2
        // Save value
        if (_fireEvents & FEATURE_SAVE_MASK) saveValue();
#endif

        // Return true
        return true;
      } else {
        if (logger) logger->printf("[%s] - Values were the same\n", name);
      }
      return false;
    }

   public:  // Filters
    virtual void addFilter(filterCallback _callback) {
      if (_callback) filtersVector.push_back(_callback);
    }
    virtual void clearFilters() {
      filtersVector.clear();
    }

   public:  // Modifiers
    virtual void addModifier(modifierCallback _callback) {
      if (_callback) modifiersVector.push_back(_callback);
    }
    virtual void clearModifiers() {
      modifiersVector.clear();
    }

   protected:  // Value Comparisson Methods
    template <class U = T>
    typename FEATURE_ENABLE_IF(!FEATURE_IS_SAME(U, char*) && !FEATURE_IS_SAME(U, const char*), bool) valueCmp(T _value) {
      return (_value == value);
    }
    template <class U = T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(U, char*) || FEATURE_IS_SAME(U, const char*), bool) valueCmp(T _value) {
      if (_value && value) {
        return strcmp(_value, value) == 0;
      } else if (_value && !value) {
        return false;
      } else {
        return true;
      }
    }

#ifdef ARDUINO
   public:  // To String Methods
    template <class U = T>
    typename FEATURE_ENABLE_IF(!FEATURE_IS_SAME(U, std::string), String) toString() {
      return String(value);
    }
    template <class U = T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(U, std::string), String) toString() {
      return String(value.c_str());
    }
#else
   public:  // To String Methods
    template <class U = T>
    typename FEATURE_ENABLE_IF(!FEATURE_IS_SAME(U, std::string), std::string) toString() {
      return std::string(value);
    }
#endif

#if defined ARDUINOJSON_VERSION_MAJOR && ARDUINOJSON_VERSION_MAJOR == 6
   public:  // JSON Setters and Getters
    virtual bool toJson(JsonObject& json) override {
      json[name] = getJsonSafeValue();
      return true;
    }
    virtual bool fromJson(JsonObject& json, uint8_t _fireEvents = 0xFF) override {
      if (json.containsKey(name)) {
        // Set the current value using the JSON object
        T _value = getValueFromJson(json);
        return setValue(_value, _fireEvents);
      }
      return false;
    }

   protected:  // Convert value to arduino json safe value
    template <class U = T>
    typename FEATURE_ENABLE_IF(!FEATURE_IS_SAME(U, std::string), T)
        getJsonSafeValue() {
      return value;
    }
    template <class U = T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(U, std::string), const char*)
        getJsonSafeValue() {
      return value.c_str();
    }

   private:  // JSON Template Setters
    template <class U = T>
    typename FEATURE_ENABLE_IF(!FEATURE_IS_SAME(U, std::string) && !FEATURE_IS_SAME(U, char*), U)
        getValueFromJson(JsonObject& jsonObject) {
      return jsonObject[name].as<U>();
    }
    template <class U = T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(U, std::string), U)
        getValueFromJson(JsonObject& jsonObject) {
      return jsonObject[name].as<const char*>();
    }
    template <class U = T>
    typename FEATURE_ENABLE_IF(FEATURE_IS_SAME(U, char*), char*)
        getValueFromJson(JsonObject& jsonObject, U _value = nullptr) {
      size_t valueSize = strlen(_value);
      snprintf(_value, valueSize, "%s", jsonObject[name].as<char*>());
      return _value;
    }
#endif

#if defined EFFORTLESS_SPIFFS_VERSION_MAJOR && EFFORTLESS_SPIFFS_VERSION_MAJOR == 2
   public:  // SPIFFS Methods
    void allowSaving(bool _saveValues = true) {
      (_saveValues) ? eventFlags |= FEATURE_SAVE_MASK : eventFlags &= FEATURE_SAVE_MASK;
    }
    void setSaveTimeout(uint32_t _delay) {
      saveDelay = _delay;
    }
    virtual inline void getFilename(char* _outputString) {
      char filename[32] = "/";
      strncat(filename, name, 30);
      strcpy(_outputString, filename);
    }
    virtual bool openValue() {
      // Get the file name
      char filename[32];
      getFilename(filename);  // 80us

      // Open the value from teh filesystem
      T    openedValue;
      bool retval = fileSystem.openFromFile(filename, openedValue);

      // Set the value from the contents from the filesystem
      if (retval) {
        if (logger) logger->printf("[%s] - Opened value from \"%s\"\n", name, filename);
        return setValue(openedValue, FEATURE_DO_NOT_SAVE_VALUES);
      } else {
        if (logger) logger->printf("[%s] - Failed to open value from \"%s\"\n", name, filename);
      }

      // Return status
      return retval;
    };
    virtual bool saveValue() {
#ifdef TICKER_H
      saveTimer.detach();
      saveTimer.once_ms<Feature<T>*>(
          saveDelay, [=](Feature<T>* _this) {
            // Get filename
            char filename[32];
            _this->getFilename(filename);

            // Save to file
            if (_this->fileSystem.saveToFile(filename, _this->value)) {
              if (_this->logger) _this->logger->printf("[%s] - Saving value to \"%s\"\n", _this->name, filename);
            } else {
              if (_this->logger) _this->logger->printf("[%s] - Failed to save value to \"%s\"\n", _this->name, filename);
            }
          },
          this);
      delay(1);

      return true;
#else
      // Create a file name
      char filename[32];
      getFilename(filename);

      // Save to file
      bool retval = fileSystem.saveToFile(filename, value);

      // Log events
      if (retval) {
        if (logger) logger->printf("[%s] - Saving value to \"%s\"\n", name, filename);
      } else {
        if (logger) logger->printf("[%s] - Failed to save value to \"%s\"\n", name, filename);
      }

      // Return status
      return retval;
#endif
    };
#endif

   public:  // Event Callback Methods
    void allowEvents(bool _fireEvents = true) {
      (_fireEvents) ? eventFlags |= FEATURE_EVENTS_MASK : eventFlags &= FEATURE_EVENTS_MASK;
    }
    void addEventCallback(eventCallback _callback) {
      eventsVector.push_back(_callback);
    }
    bool removeLastCallback() {
      eventsVector.pop_back();
      return true;
    }
    bool removeSpecificCallback(uint32_t _offset) {
      if (_offset < eventsVector.size()) {
        eventsVector.erase(eventsVector.begin() + _offset);
        return true;
      } else {
        return false;
      }
    }
    bool removeAllCallbacks() {
      eventsVector.clear();
      return true;
    }

   protected:  // Event Callback Execution
    void fireEventCallbacks() {
      if (logger) logger->printf("[%s] - Firing events\n", name);
      for (auto& callback : eventsVector) {
        callback(value);
      }
    }

#ifdef ARDUINO
   public:  // Debug Callback Methods
    void setDebugOutput(Print* _callback) {
      if (_callback) logger = _callback;
    }
#endif

   protected:  // Private Stored Data
    T                      value;
    T                      previousValue;
    uint8_t                eventFlags = FEATURE_FIRE_EVENTS_SAVE_VALUES;
    uint32_t               saveDelay = 0;
    eventCallbackVector    eventsVector;
    filterCallbackVector   filtersVector;
    modifierCallbackVector modifiersVector;

#ifdef ARDUINO
    Print* logger = FEATURE_DEBUG_OBJECT;
#endif

#ifdef TICKER_H
    Ticker saveTimer;
#endif

#if defined EFFORTLESS_SPIFFS_VERSION_MAJOR && EFFORTLESS_SPIFFS_VERSION_MAJOR == 2
    eSPIFFS fileSystem;
#endif
  };
}  // namespace FeatureVariables

#endif
