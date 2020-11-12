#include the macros
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Macros.cmake)

# Set a default build type
ime_set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release)")

# Set cmake version
cmake_minimum_required(VERSION 3.17)

# Project name, version and description
project(IME VERSION 1.0.0 DESCRIPTION "A state-based 2D game engine using modern C++ and SFML")

# IME uses the paths from the cmake GNUInstallDirs module as defaults
# (https://cmake.org/cmake/help/v3.0/module/GNUInstallDirs.html)
include(GNUInstallDirs)

# Include the configuration file
include(${PROJECT_SOURCE_DIR}/cmake/Config.cmake)

# Add an option for choosing the build type (shared or static)
if(IME_OS_WINDOWS)
    if(DEFINED BUILD_SHARED_LIBS)
        set(IME_SHARED_LIBS ${BUILD_SHARED_LIBS} BOOL "TRUE to build IME as a shared library, FALSE to build it as a static library")
    else()
        ime_set_option(IME_SHARED_LIBS TRUE BOOL "TRUE to build IME as a shared library, FALSE to build it as a static library")
    endif()
endif()

# Add option to build the examples
ime_set_option(IME_BUILD_EXAMPLES FALSE BOOL "TRUE to build the IME examples, FALSE to ignore them")

# Add options to build the tests
ime_set_option(IME_BUILD_TESTS FALSE BOOL "TRUE to build the IME tests")

# Add option to build the documentation
ime_set_option(IME_BUILD_DOC FALSE BOOL "TRUE to generate the API documentation, FALSE to ignore it")

    # Set CXX Standard
ime_set_option(IME_CXX_STANDARD "17" STRING "C++ standard version to build IME with. Possible values: 17 or 20. Projects using IME must use a version equal or higher to this")

# At least C++17 has to be used
if(IME_CXX_STANDARD LESS "17")
    message(FATAL_ERROR "IME_CXX_STANDARD has to be at least 17")
endif()

# Define the install directory for miscellaneous files
if(IME_OS_WINDOWS)
    set(DEFAULT_INSTALL_MISC_DIR .)
endif()
ime_set_option(IME_MISC_INSTALL_PREFIX "${DEFAULT_INSTALL_MISC_DIR}" PATH "Prefix installation path for miscellaneous files")
mark_as_advanced(IME_MISC_INSTALL_PREFIX)

# Don't Install pkg-config files by default
ime_set_option(IME_INSTALL_PKGCONFIG_FILES FALSE BOOL "TRUE to automatically install pkg-config files so other projects can find IME")

if (IME_INSTALL_PKGCONFIG_FILES)
    ime_set_option(IME_PKGCONFIG_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/${IME_PKGCONFIG_DIR}" PATH "Install directory for IME's pkg-config .pc files")

    configure_file("pkgconfig/ime.pc.in" "pkgconfig/ime.pc" @ONLY)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pkgconfig/ime.pc" DESTINATION "${IME_PKGCONFIG_INSTALL_PREFIX}")
endif()

# Define an option for choosing between static and dynamic C runtime
if(IME_OS_WINDOWS)
    ime_set_option(IME_USE_STATIC_STD_LIBS FALSE BOOL "TRUE to statically link to the standard libraries, FALSE to use them as DLLs. This option has to match with the one from SFML.")

    # The following combination of flags is not valid
    if(IME_SHARED_LIBS AND IME_USE_STATIC_STD_LIBS)
        message(FATAL_ERROR "IME_SHARED_LIBS and IME_USE_STATIC_STD_LIBS cannot be used together")
    endif()
endif()

# Add an option to choose whether PDB debug symbols should be generated for Visual Studio
if(IME_COMPILER_MSVC)
    ime_set_option(IME_GENERATE_PDB TRUE BOOL "True to generate PDB debug symbols, FALSE otherwise.")
endif()

# Apply the IME_USE_STATIC_STD_LIBS option on windows when using VC++
# This can't be done in the ime_set_stdlib macro because it is too late to change these variables by then
if(IME_OS_WINDOWS AND IME_COMPILER_MSVC AND IME_USE_STATIC_STD_LIBS)
    foreach(flag
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if(${flag} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
        endif()
    endforeach()
endif()

# Set the path for the libraries
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

# Add source directory
add_subdirectory(src/IME)

# Build the documentation when requested
if(IME_BUILD_DOC)
    add_subdirectory(docs)
endif()

# Build the examples if requested
if(IME_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Build the tests if requested
if(IME_BUILD_TESTS)
    if(NOT ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        message(WARNING "IME_BUILD_TESTS is ON but CMAKE_BUILD_TYPE isn't Debug")
    endif()

    add_subdirectory(tests)
endif()

## Set up install rules

# Install include files
install(DIRECTORY include
        DESTINATION .
        COMPONENT devel
        FILES_MATCHING PATTERN "*.h" PATTERN "*.inl")

if(IME_GENERATE_PDB)
        install(DIRECTORY "${PROJECT_BINARY_DIR}/lib"
        DESTINATION .
        COMPONENT devel
        FILES_MATCHING PATTERN "*.pdb")
endif()

# Install miscellaneous files
install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_DOCDIR})
install(FILES README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
