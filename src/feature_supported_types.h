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

#pragma once

#ifndef FEATURE_SUPPORTED_TYPES_h
#define FEATURE_SUPPORTED_TYPES_h

namespace FeatureVariables {
  // Supported types
  enum class SupportedTypes {
    BOOL,
    FLOAT,
    DOUBLE,
    SIGNED_CHAR,
    SIGNED_INT,
    SIGNED_SHORT,
    SIGNED_LONG,
    UNSIGNED_CHAR,
    UNSIGNED_INT,
    UNSIGNED_SHORT,
    UNSIGNED_LONG,
    CHAR_PTR,
    CONST_CHAR_PTR,
    STRING,
    STD_STRING,
    UNSUPPORTED
  };
}  // namespace FeatureVariables

#endif