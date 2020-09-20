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

#ifndef FEATURE_SAFE_GET_h
#define FEATURE_SAFE_GET_h

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
  T safe_get(FeatureBase* feature) {
    Feature<T>* upcast = safe_cast<T>(feature);
    return (upcast) ? upcast->getValue() : T(0x00);
  }

  template <>
  std::string safe_get(FeatureBase* feature) {
    Feature<std::string>* upcast = safe_cast<std::string>(feature);
    return (upcast) ? upcast->getValue() : std::string();
  }

#ifdef ARDUINO
  template <>
  String safe_get(FeatureBase* feature) {
    Feature<String>* upcast = safe_cast<String>(feature);
    return (upcast) ? upcast->getValue() : String();
  }
#endif
}  // namespace FeatureVariables

#endif