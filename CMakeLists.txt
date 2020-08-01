cmake_minimum_required(VERSION 3.16)
project(IME VERSION 1.0.0 DESCRIPTION "A simple 2D game engine using modern C++ and SFML")

set(CMAKE_CXX_STANDARD 17)

set(DEFAULT_BUILD_TYPE)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type to build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

#Declare library target
add_library(${PROJECT_NAME} SHARED
        src/IME/core/animation/Animation.cpp
        src/IME/core/animation/Animator.cpp
        src/IME/core/audio/AudioPlayer.cpp
        src/IME/core/audio/MusicPlayer.cpp
        src/IME/core/audio/SoundEffectPlayer.cpp
        src/IME/core/audio/AudioManager.cpp
        src/IME/core/engine/Engine.cpp
        src/IME/core/engine/State.cpp
        src/IME/event/EventEmitter.cpp
        src/IME/event/EventEmitter.inl
        src/IME/factory/GuiFactory.inl
        src/IME/gui/control/UIElement.cpp
        src/IME/gui/control/ClickableUIElement.cpp
        src/IME/gui/control/Button.cpp
        src/IME/gui/control/Caret.cpp
        src/IME/gui/control/TextBlock.cpp
        src/IME/gui/control/TextInput.cpp
        src/IME/gui/drawer/Drawer.cpp
        src/IME/gui/layout/Panel.cpp
        src/IME/gui/layout/StackPanel.cpp
        src/IME/gui/layout/DockPanel.cpp
        src/IME/gui/layout/Canvas.cpp
        src/IME/gui/input/Keyboard.cpp
        src/IME/gui/input/Mouse.cpp
        src/IME/gui/window/Window.cpp
        src/IME/core/resources/FileReader.cpp
        src/IME/core/resources/ResourceHolder.inl
        src/IME/core/resources/ResourceManager.cpp
        src/IME/utility/Scoreboard.cpp
        src/IME/utility/Clock.cpp
        src/IME/core/IEntity.cpp
        src/IME/core/EntityCollisionManager.cpp)

#Set version property
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)

#Declare public API of library (API will be installed for third-party application)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
        include/IME/core/animation/Animation.h
        include/IME/core/animation/Animator.h
        include/IME/core/audio/AudioPlayer.h
        include/IME/core/audio/MusicPlayer.h
        include/IME/core/audio/SoundEffectPlayer.h
        include/IME/core/audio/AudioManager.h
        include/IME/core/engine/Engine.h
        include/IME/core/engine/State.h
        include/IME/core/IEntity.h
        include/IME/core/EntityCollisionManager.h
        include/IME/event/EventEmitter.h
        include/IME/core/exceptions/Exceptions.h
        include/IME/factory/GuiFactory.h
        include/IME/gui/control/UIElement.h
        include/IME/gui/control/ClickableUIElement.h
        include/IME/gui/control/Button.h
        #include/IME/gui/control/Caret.h
        include/IME/gui/control/TextBlock.h
        include/IME/gui/control/TextInput.h
        include/IME/gui/layout/Panel.h
        include/IME/gui/layout/StackPanel.h
        include/IME/gui/layout/Canvas.h
        include/IME/gui/layout/DockPanel.h
        include/IME/gui/drawer/Drawer.h
        include/IME/gui/input/Keyboard.h
        include/IME/gui/input/Mouse.h
        include/IME/gui/window/Window.h
        include/IME/core/resources/FileReader.h
        include/IME/core/resources/ResourceHolder.h
        include/IME/core/resources/ResourceManager.h
        include/IME/utility/Clock.h
        include/IME/utility/Scoreboard.h
        include/IME/utility/Utility.h
        include/IME/utility/NonCopyable.h)

#Add path to cmake include search path
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

#Create install rule
include(GNUInstallDirs)

#
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#
configure_file(IME.pc.in IME.pc @ONLY)

#
install(FILES ${CMAKE_BINARY_DIR}/IME.pc DESTINATION ${CMAKE_DATAROOTDIR}/pkgconfig)

#Change executable output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

#Detect and add SFML
set(SFML_INCLUDE_DIR "C:/SFML-2.5.0/include")
set(SFML_LIBRARY_DIR "C:/SFML-2.5.0/lib")
set(SFML_DIR "C:/SFML-2.5.0/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.0 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    target_link_libraries (${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARY_DIR}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()