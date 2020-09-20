# Features-Variables

[![GitHub release](https://img.shields.io/github/release/thebigpotatoe/Feature-Variables.svg)](https://github.com/thebigpotatoe/Feature-Variables/releases)
[![arduino-library-badge](https://www.ardu-badge.com/badge/Feature-Variables.svg?)](https://www.ardu-badge.com/Feature-Variables) 
[![PlatformIO Build Status](https://github.com/thebigpotatoe/Feature-Variables/workflows/PlatformIO%20CI/badge.svg)](https://github.com/thebigpotatoe/Feature-Variables/actions?query=workflow%3A%22PlatformIO+CI%22)
[![Arduino Build Status](https://github.com/thebigpotatoe/Feature-Variables/workflows/Arduino/badge.svg)](https://github.com/thebigpotatoe/Feature-Variables/actions?query=workflow%3A%22PlatformIO+CI%22)
[![GitHub License](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/thebigpotatoe/Feature-Variables/blob/master/LICENSE)

Features are persistent event driven variables specifically for use with the popular Arduino boards and Espressif series micro controllers. They simplify everything from loading and saving variable data into flash for persistance over reboots, to firing multiple events when the value of a variable has changed, to simplifying data passing when using ArduinoJSON, all in a few lines of easy to understand code.

The library and examples are supported in the Arduino IDE and platformIO for building. Check out the library.properties or platfomio.ini file for idea on how to build the library in the Arduino IDE or on pio. Included are a heap of examples on how to use each of the advantages of Features in your application fully compatible with both build methods.

If you would like to reach out, this project is open to comments, improvements, or general feedback, so feel free to open an issue or create a pull request with any ideas!

## Quick Start

Starting or migrating a project to Features is easy. Just see this short example of how to create a very basic Feature application storing the value of millis() every second:

``` c++
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
```

## Examples
For a comprehensive understanding of the API and how to use Features check out the examples folder. In there you can find several examples showing:

- [Basic use of Features](examples/Basic_Use/Basic_Use.ino)
- [How to use in a storage container like std::vector](examples/Container_Example/Container_Example.ino)
- [All methods of getting the value from the Feature](examples/Alternate_Get_Methods/Alternate_Get_Methods.ino)
- [All methods of setting the value from the Feature](examples/Alternate_Set_Methods/Alternate_Set_Methods.ino)
- [Delay saving of the value to speed up the application](examples/Delayed_Saving/Delayed_Saving.ino)
- [How to use with ArduinoJSON very easily](examples/Using_ArduinoJson/Using_ArduinoJson.ino)

## Contributing

Contributions of any type are most welcome. Feel free to open an issues with feedback, questions, ideas, or anything else regarding Features or a pull request for new any ideas on code style or implementation.
