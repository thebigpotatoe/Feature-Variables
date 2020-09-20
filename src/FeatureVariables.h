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

// c++ compiler check
#ifndef __cplusplus
#error Feature Variables require a C++ compiler
#endif

// Version Macros
#define FEATURE_VARIABLES_VERSION_MAJOR 1
#define FEATURE_VARIABLES_VERSION_MINOR 0
#define FEATURE_VARIABLES_VERSION_PATCH 0

// Arduino Framework Libraries
#ifdef ARDUINO
#include <Print.h>
#include <Ticker.h>
#else
#warning "Feature Variables uses Arduino for some functionality. Compile with the Arduino framework for these features"
#endif

// Internal includes
#include "feature_macros.h"
#include "feature_internal.h"
#include "feature_supported_types.h"
#include "feature_base.h"
#include "feature_impl.h"
#include "feature_safe_cast.h"
#include "feature_safe_get.h"
#include "feature_safe_set.h"

// Use relevant classes
using FeatureVariables::Feature;
using FeatureVariables::FeatureBase;