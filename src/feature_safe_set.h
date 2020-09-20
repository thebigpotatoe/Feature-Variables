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

#ifndef FEATURE_SAFE_SET_h
#define FEATURE_SAFE_SET_h

// std libraries
#include <functional>
#include <string>

// Internal Includes
#include "feature_supported_types.h"
#include "feature_base.h"
#include "feature_impl.h"
#include "feature_safe_cast.h"

namespace FeatureVariables {
  template <class T>
  bool safe_set(FeatureBase* feature, T value, uint8_t _fireEvents = 0xff) {
    Feature<T>* upcast = safe_cast<T>(feature);
    return (upcast) ? upcast->setValue(value, _fireEvents) : false;
  }
}  // namespace FeatureVariables

#endif