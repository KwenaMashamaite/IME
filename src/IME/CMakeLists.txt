set(IME_SRC_FILES
    common/Dimensions.cpp
    common/Position.cpp
    common/Property.cpp
    common/PropertiesContainer.cpp
    core/animation/Animation.cpp
    core/animation/Animator.cpp
    core/audio/AudioPlayer.cpp
    core/audio/MusicPlayer.cpp
    core/audio/SoundEffectPlayer.cpp
    core/entity/Entity.cpp
    core/event/EventEmitter.cpp
    core/event/EventDispatcher.cpp
    core/input/Keyboard.cpp
    core/input/Mouse.cpp
    core/loop/Engine.cpp
    core/managers/AudioManager.cpp
    core/managers/InputManager.cpp
    core/managers/ResourceManager.cpp
    core/path/AdjacencyList.cpp
    core/path/BFS.cpp
    core/path/DFS.cpp
    core/path/IGridPathFinder.cpp
    core/physics/CollisionDetector.cpp
    core/physics/GridMover.cpp
    core/physics/KeyboardControlledGridMover.cpp
    core/physics/RandomGridMover.cpp
    core/physics/TargetGridMover.cpp
    core/states/State.cpp
    core/states/StateManager.cpp
    core/tilemap/TileMap.cpp
    core/tilemap/TileMapParser.cpp
    core/time/Clock.cpp
    graphics/ui/layout/ChildWindow.cpp
    graphics/ui/layout/VerticalLayout.cpp
    graphics/ui/layout/HorizontalLayout.cpp
    graphics/ui/renderers/BoxLayoutRenderer.cpp
    graphics/ui/renderers/ButtonRenderer.cpp
    graphics/ui/renderers/CheckBoxRenderer.cpp
    graphics/ui/renderers/ChildWindowRenderer.cpp
    graphics/ui/renderers/EditBoxRenderer.cpp
    graphics/ui/renderers/LabelRenderer.cpp
    graphics/ui/renderers/ProgressBarRenderer.cpp
    graphics/ui/renderers/SliderRenderer.cpp
    graphics/ui/widgets/BitmapButton.cpp
    graphics/ui/widgets/Button.cpp
    graphics/ui/widgets/CheckBox.cpp
    graphics/ui/widgets/EditBox.cpp
    graphics/ui/widgets/Label.cpp
    graphics/ui/widgets/ProgressBar.cpp
    graphics/ui/widgets/Slider.cpp
    graphics/ui/GuiContainer.cpp
    graphics/Sprite.cpp
    graphics/AnimatableSprite.cpp
    graphics/Colour.cpp
    graphics/Tile.cpp
    graphics/Window.cpp
    utility/ConfigFileParser.cpp
    utility/ConsoleLogger.cpp
    utility/DiskFileLogger.cpp
    utility/DiskFileReader.cpp
    utility/Helpers.cpp
)

# Create library and determine suffixes depending on static/shared configuration
if(IME_SHARED_LIBS)
    add_library(ime SHARED ${IME_SRC_FILES})
    set_target_properties(ime PROPERTIES DEFINE_SYMBOL IME_EXPORTS)
    set_target_properties(ime PROPERTIES DEBUG_POSTFIX -d)

    # Set the version and soversion of the target
    set_target_properties(ime PROPERTIES SOVERSION ${IME_VERSION_MAJOR}.${IME_VERSION_MINOR}.${IME_VERSION_PATCH})
    set_target_properties(ime PROPERTIES VERSION ${IME_VERSION_MAJOR}.${IME_VERSION_MINOR}.${IME_VERSION_PATCH})

    # on Windows/gcc get rid of "lib" prefix for shared libraries,
    # and transform the ".dll.a" suffix into ".a" for import libraries
    if(IME_OS_WINDOWS AND IME_COMPILER_GCC)
        set_target_properties(ime PROPERTIES PREFIX "")
        set_target_properties(ime PROPERTIES IMPORT_SUFFIX ".a")
    endif()

else()
    add_library(ime STATIC ${IME_SRC_FILES})
    set_target_properties(ime PROPERTIES DEBUG_POSTFIX -s-d)
    set_target_properties(ime PROPERTIES RELEASE_POSTFIX -s)
    set_target_properties(ime PROPERTIES MINSIZEREL_POSTFIX -s)
    set_target_properties(ime PROPERTIES RELWITHDEBINFO_POSTFIX -s)
endif()

# Define either IME_STATIC or IME_DYNAMIC
if(IME_SHARED_LIBS)
    target_compile_definitions(ime PUBLIC IME_DYNAMIC)
else()
    target_compile_definitions(ime PUBLIC IME_STATIC)
endif()

ime_set_global_compile_flags(ime)
ime_set_stdlib(ime)

# Add <project>/include as public include directory
target_include_directories(ime PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_include_directories(ime INTERFACE $<INSTALL_INTERFACE:include>)

# Find SFML
set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/extlibs/SFML/include")
set(SFML_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/extlibs/SFML/lib")
set(SFML_DIR "${PROJECT_SOURCE_DIR}/extlibs/SFML/lib/cmake/SFML")

find_package(SFML 2.5.1 REQUIRED COMPONENTS system window graphics audio)
message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARY_DIR}")
message(STATUS "SFML_VERSION: ${SFML_VERSION}")

# Find TGUI
set(TGUI_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/extlibs/TGUI-0.9/include")
set(TGUI_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/extlibs/TGUI-0.9/lib")
set(TGUI_DIR "${PROJECT_SOURCE_DIR}/extlibs/TGUI-0.9/lib/cmake/TGUI")

if(IME_CXX_STANDARD EQUAL "17")
    ime_set_option(TGUI_USE_CPP17 TRUE BOOL "TRUE to compile TGUI with C++17, otherwise FALSE")
endif()

find_package(TGUI 0.9.0 REQUIRED)
message(STATUS "TGUI_INCLUDE_DIR: ${TGUI_INCLUDE_DIR}")
message(STATUS "TGUI_LIBRARIES: ${TGUI_LIBRARY_DIR}")
message(STATUS "TGUI_VERSION: ${TGUI_VERSION}")

# Link TGUI and SFML
target_link_libraries(ime PRIVATE tgui sfml-graphics sfml-window sfml-system sfml-audio)

# define IME_USE_CPP17 if requested
if(IME_USE_CPP17)
    target_compile_definitions(ime PUBLIC IME_USE_CPP17)
endif()

# For Visual Studio on Windows, export debug symbols (PDB files) to lib directory
if(IME_GENERATE_PDB)
    # PDB files are only generated in Debug and RelWithDebInfo configurations, find out which one
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(IME_PDB_POSTFIX "-d")
    else()
        set(IME_PDB_POSTFIX "")
    endif()

    if(IME_SHARED_LIBS)
        # DLLs export debug symbols in the linker PDB (the compiler PDB is an intermediate file)
        set_target_properties(ime PROPERTIES
                PDB_NAME "ime${IME_PDB_POSTFIX}"
                PDB_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
    else()
        # Static libraries have no linker PDBs, thus the compiler PDBs are relevant
        set_target_properties(ime PROPERTIES
                COMPILE_PDB_NAME "ime-s${IME_PDB_POSTFIX}"
                COMPILE_PDB_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
    endif()
endif()

# Install library
install(TARGETS ime EXPORT IMEConfigExport
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT bin
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT devel
        FRAMEWORK DESTINATION "." COMPONENT bin
        )

# Generate the IMEConfig.cmake file
# This has to happen here instead of in the root CMakeLists.txt because otherwise
# it might try to write to the macOS framework before the framework is installed.
# This is because the order of install rules is undefined between directories.
ime_export_target(IMEConfigExport)
