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

#ifndef FEATURE_SAFE_CAST_h
#define FEATURE_SAFE_CAST_h

// std libraries
#include <functional>
#include <string>

// Internal Includes
#include "feature_supported_types.h"
#include "feature_base.h"
#include "feature_impl.h"

namespace FeatureVariables {
  // Safe cast base template
  template <class T>
  Feature<T>* safe_cast(FeatureBase* feature) {
    return nullptr;
  }

  // Safe cast boolean specialisation
  template <>
  Feature<bool>* safe_cast<bool>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::BOOL) ? static_cast<Feature<bool>*>(feature) : nullptr;
  }

  // Safe cast floating point specialisations
  template <>
  Feature<float>* safe_cast<float>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::FLOAT) ? static_cast<Feature<float>*>(feature) : nullptr;
  }
  template <>
  Feature<double>* safe_cast<double>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::DOUBLE) ? static_cast<Feature<double>*>(feature) : nullptr;
  }

  // Safe cast signed specialisations
  template <>
  Feature<signed char>* safe_cast<signed char>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::SIGNED_CHAR) ? static_cast<Feature<signed char>*>(feature) : nullptr;
  }
  template <>
  Feature<signed int>* safe_cast<signed int>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::SIGNED_INT) ? static_cast<Feature<signed int>*>(feature) : nullptr;
  }
  template <>
  Feature<signed short>* safe_cast<signed short>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::SIGNED_SHORT) ? static_cast<Feature<signed short>*>(feature) : nullptr;
  }
  template <>
  Feature<signed long>* safe_cast<signed long>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::SIGNED_LONG) ? static_cast<Feature<signed long>*>(feature) : nullptr;
  }

  // Safe cast unsigned specialisations
  template <>
  Feature<unsigned char>* safe_cast<unsigned char>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::UNSIGNED_CHAR) ? static_cast<Feature<unsigned char>*>(feature) : nullptr;
  }
  template <>
  Feature<unsigned int>* safe_cast<unsigned int>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::UNSIGNED_INT) ? static_cast<Feature<unsigned int>*>(feature) : nullptr;
  }
  template <>
  Feature<unsigned short>* safe_cast<unsigned short>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::UNSIGNED_SHORT) ? static_cast<Feature<unsigned short>*>(feature) : nullptr;
  }
  template <>
  Feature<unsigned long>* safe_cast<unsigned long>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::UNSIGNED_LONG) ? static_cast<Feature<unsigned long>*>(feature) : nullptr;
  }

  // Safe cast string like specialisations
  template <>
  Feature<char*>* safe_cast<char*>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::CHAR_PTR) ? static_cast<Feature<char*>*>(feature) : nullptr;
  }
  template <>
  Feature<const char*>* safe_cast<const char*>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::CONST_CHAR_PTR) ? static_cast<Feature<const char*>*>(feature) : nullptr;
  }
  template <>
  Feature<std::string>* safe_cast<std::string>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::STD_STRING) ? static_cast<Feature<std::string>*>(feature) : nullptr;
  }

#ifdef ARDUINO
  template <>
  Feature<String>* safe_cast<String>(FeatureBase* feature) {
    return (feature->getType() == SupportedTypes::STRING) ? static_cast<Feature<String>*>(feature) : nullptr;
  }
#endif
}  // namespace FeatureVariables

#endif