cmake_minimum_required(VERSION 3.12)
project(duel-invaders)

set(CMAKE_CXX_STANDARD 17)

include_directories(game-source-code)

set(SOURCE_FILES game-source-code/main/main.cpp)

#add the doctest unit testing framework
include_directories(C:/doctest-1.2.9/doctest)

#Detect and add SFML 2.5.0
set(SFML_INCLUDE_DIR "C:/SFML-2.5.0/include")
set(SFML_LIBRARY_DIR "C:/SFML-2.5.0/lib")
set(SFML_DIR "C:/SFML-2.5.0/lib/cmake/SFML")

#Change the executable name
Set(EXECUTABLE_NAME "duel-invaders")

#Change executable output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/executables)

add_executable(duel-invaders ${SOURCE_FILES} game-source-code/main/main.cpp)

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.0 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    target_link_libraries (duel-invaders sfml-graphics sfml-window sfml-system sfml-audio)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()