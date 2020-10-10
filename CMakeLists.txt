cmake_minimum_required(VERSION 3.17)
project(IME LANGUAGES CXX VERSION 1.0.0 DESCRIPTION "A simple 2D game engine using modern C++ and SFML")

set(CMAKE_CXX_STANDARD 20)

#Create install rule
include(GNUInstallDirs)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/IME)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
add_subdirectory(${PROJECT_SOURCE_DIR}/examples)