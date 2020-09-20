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

#ifndef FEATURE_INTERNAL_h
#define FEATURE_INTERNAL_h

// Ease of use macros
#define FEATURE_ENABLE_IF(type1, type2) Feature_Internal::enable_if<type1, type2>::type
#define FEATURE_IS_SAME(type1, type2) Feature_Internal::is_same<type1, type2>::value

namespace FeatureVariables {
  // Internal feature name class for std::library implementations
  namespace Feature_Internal {
    // std:: enable_if implementation
    template <bool B, class T = void>
    struct enable_if {
    };

    template <class T>
    struct enable_if<true, T> {
      typedef T type;
    };

    // std::is_same implementation
    template <typename A, typename B>
    struct is_same {
      static const bool value = false;
    };
    template <typename A>
    struct is_same<A, A> {
      static const bool value = true;
    };
  }  // namespace Feature_Internal
}  // namespace FeatureVariables

#endif