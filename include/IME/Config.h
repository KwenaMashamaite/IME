////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef IME_CONFIG_HPP
#define IME_CONFIG_HPP

// This file is generated by CMake and must not be edited directly.

// Detect the platform, to enable platform-specific code
#if defined(_WIN32)
    #define IME_SYSTEM_WINDOWS // Windows
#endif

// Define a portable debug macro
#if !defined(NDEBUG)

#define IME_DEBUG

#endif

// IME will link in the same way as SFML and TGUI, unless IME_DYNAMIC or IME_STATIC is defined
#if !defined(IME_DYNAMIC) && !defined(IME_STATIC)
    #ifdef SFML_STATIC
        #define IME_STATIC
    #endif
#endif

#ifndef IME_STATIC
    #ifdef IME_SYSTEM_WINDOWS
        // Windows compilers need specific (and different) keywords for export and import
        #ifdef IME_EXPORTS
            #define IME_API __declspec(dllexport)
        #else
            #define IME_API __declspec(dllimport)
        #endif

        // For Visual C++ compilers, we also need to turn off this annoying C4251 warning
        #ifdef _MSC_VER

            #pragma warning(disable: 4251)

        #endif
    #endif
#else
    // Static build doesn't need import/export macros
    #define IME_API
#endif

#if !defined(NDEBUG) && !defined(IME_NO_RUNTIME_WARNINGS)
#include <iostream>
#define IME_PRINT_WARNING(msg) { std::cerr << "IME warning: " << msg << "\n"; }
#else
#define IME_PRINT_WARNING(msg)
#endif

#if !defined(NDEBUG) && !defined(IME_DISABLE_ASSERTS)
#include <iostream>
#include <cassert>
#define IME_ASSERT(condition, msg) { if (!(condition)) { std::cerr << "IME assertion: " << msg << "\n"; assert(condition); } }
#else
#define IME_ASSERT(condition, msg)
#endif

// Portable macro that suppress unused parameter warnings
#define IME_UNUSED(x) (void)(x)

// Define portable fixed-size types
namespace ime {
    // All "common" platforms use the same size for char, short and int
    // (basically there are 3 types for 3 sizes, so no other match is possible),
    // we can use them without doing any kind of check

    // 8 bits integer types
    typedef signed   char Int8;
    typedef unsigned char Uint8;

    // 16 bits integer types
    typedef signed   short Int16;
    typedef unsigned short Uint16;

    // 32 bits integer types
    typedef signed   int Int32;
    typedef unsigned int Uint32;

    // 64 bits integer types
#if defined(_MSC_VER)
    typedef signed   __int64 Int64;
    typedef unsigned __int64 Uint64;
#else
    typedef signed   long long Int64;
    typedef unsigned long long Uint64;
#endif
} // namespace ime

// Version of the library
#define IME_VERSION_MAJOR 2
#define IME_VERSION_MINOR 1
#define IME_VERSION_PATCH 0

#endif // IME_CONFIG_H
