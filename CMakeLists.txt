cmake_minimum_required(VERSION 3.12)
project(duel-invaders)

set(CMAKE_CXX_STANDARD 17)

include_directories(game-source-code)
include_directories(test-source-code)

set(SOURCE_FILES
        game-source-code/gui/window/Window.cpp
        game-source-code/gui/window/Window.h
        game-source-code/globals/Globals.h
        game-source-code/main/main.cpp
        game-source-code/resources/ResourceHolder.h
        game-source-code/resources/ResourceHolder.inl
        game-source-code/resources/ResourceManager.cpp
        game-source-code/resources/ResourceManager.h
        game-source-code/exceptions/Exceptions.h
        game-source-code/event/EventEmitter.inl
        game-source-code/event/EventEmitter.cpp
        game-source-code/event/EventEmitter.h
        game-source-code/event/IdHolder.cpp
        game-source-code/event/IdHolder.h
        game-source-code/audio/IAudioPlayer.h
        game-source-code/audio/SoundEffectPlayer.cpp
        game-source-code/audio/SoundEffectPlayer.h
        game-source-code/audio/MusicPlayer.cpp
        game-source-code/audio/MusicPlayer.h
        game-source-code/gui/control/UIElement.cpp
        game-source-code/gui/control/UIElement.h
        game-source-code/gui/control/TextBlock.cpp
        game-source-code/gui/control/TextBlock.h
        game-source-code/gui/layout/Panel.cpp
        game-source-code/gui/layout/Panel.h
        game-source-code/gui/layout/StackPanel.cpp
        game-source-code/gui/layout/StackPanel.h
        game-source-code/gui/control/Button.cpp
        game-source-code/gui/control/Button.h
        game-source-code/utility/FileReader.h
        game-source-code/utility/FileReader.cpp
        game-source-code/scoreboard/Scoreboard.h
        game-source-code/scoreboard/Scoreboard.cpp
        game-source-code/input/Keyboard.h
        game-source-code/input/Keyboard.cpp
        game-source-code/input/Mouse.h
        game-source-code/input/Mouse.cpp)

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

add_executable(duel-invaders ${SOURCE_FILES})

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.0 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    target_link_libraries (duel-invaders sfml-graphics sfml-window sfml-system sfml-audio)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()