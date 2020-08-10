cmake_minimum_required(VERSION 3.16)
project(IME LANGUAGES CXX VERSION 1.0.0 DESCRIPTION "A simple 2D game engine using modern C++ and SFML")

set(CMAKE_CXX_STANDARD 17)

#Create install rule
include(GNUInstallDirs)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/IME)
add_subdirectory(${PROJECT_SOURCE_DIR}/examples)