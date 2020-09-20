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

#ifndef FEATURE_MACROS_h
#define FEATURE_MACROS_h

// Feature Events Macros
#define FEATURE_FIRE_EVENTS_SAVE_VALUES 0x81
#define FEATURE_DO_NOT_FIRE_EVENTS_OR_SAVE_VALUES 0x00
#define FEATURE_DO_NOT_SAVE_VALUES 0x80
#define FEATURE_DO_NOT_FIRE_EVENTS 0x01
#define FEATURE_SAVE_MASK 0x01
#define FEATURE_EVENTS_MASK 0x80

// Print Debugger Macro
#ifndef FEATURE_DEBUG_OBJECT
#define FEATURE_DEBUG_OBJECT nullptr
#endif

// New Features macro - for any member space
#define NEW_MEMBER_FEATURE_NO_SAVE_ARG(name, type) \
  Feature<type> name { #name, (type)(0x00), FEATURE_FIRE_EVENTS_SAVE_VALUES }
#define NEW_MEMBER_FEATURE_SAVE_ARG(name, type, save_file) \
  Feature<type> name { #name, (type)(0x00), save_file }
#define GET_SAVE_ARG(name, type, save_file, command, ...) command
#define NEW_MEMBER_FEATURE_MACRO_SELECTOR(...) GET_SAVE_ARG(__VA_ARGS__, NEW_MEMBER_FEATURE_SAVE_ARG, NEW_MEMBER_FEATURE_NO_SAVE_ARG, )
#define NEW_FEATURE(...)                         \
  NEW_MEMBER_FEATURE_MACRO_SELECTOR(__VA_ARGS__) \
  (__VA_ARGS__)

#endif