# Hide all symbols by default
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

set(IME_SRC
    common/Property.cpp
    common/PropertyContainer.cpp
    common/Transform.cpp
    common/Object.cpp
    core/animation/Animation.cpp
    core/animation/Animator.cpp
    core/audio/Audio.cpp
    core/audio/Music.cpp
    core/audio/SoundEffect.cpp
    core/game_object/GameObject.cpp
    core/event/EventEmitter.cpp
    core/event/EventDispatcher.cpp
    core/input/Keyboard.cpp
    core/input/Mouse.cpp
    core/engine/Engine.cpp
    core/audio/AudioManager.cpp
    core/input/InputManager.cpp
    core/resources/ResourceManager.cpp
    core/resources/ResourceHolder.cpp
    core/path/AdjacencyList.cpp
    core/path/BFS.cpp
    core/path/DFS.cpp
    core/path/IGridPathFinder.cpp
    core/physics/rigid_body/Body.cpp
    core/physics/rigid_body/colliders/Collider.cpp
    core/physics/rigid_body/colliders/CircleCollider.cpp
    core/physics/rigid_body/colliders/PolygonCollider.cpp
    core/physics/rigid_body/colliders/BoxCollider.cpp
    core/physics/rigid_body/colliders/EdgeCollider.cpp
    core/physics/rigid_body/joints/Joint.cpp
    core/physics/rigid_body/joints/JointDefinition.cpp
    core/physics/rigid_body/joints/DistanceJoint.cpp
    core/physics/rigid_body/AABB.cpp
    core/physics/tilemap/GridMover.cpp
    core/physics/tilemap/TargetGridMover.cpp
    core/physics/tilemap/KeyboardControlledGridMover.cpp
    core/physics/tilemap/RandomGridMover.cpp
    core/physics/ContactListener.cpp
    core/physics/World.cpp
    core/scene/Scene.cpp
    core/scene/SceneManager.cpp
    core/scene/RenderLayer.cpp
    core/scene/RenderLayerContainer.cpp
    core/scene/GameObjectContainer.cpp
    core/scene/GridMoverContainer.cpp
    core/tilemap/Index.cpp
    core/tilemap/TileMap.cpp
    core/tilemap/TileMapParser.cpp
    core/time/Clock.cpp
    core/time/Timer.cpp
    core/time/TimerManager.cpp
    core/time/Time.cpp
    ui/renderers/BoxLayoutRenderer.cpp
    ui/renderers/ButtonRenderer.cpp
    ui/renderers/CheckBoxRenderer.cpp
    ui/renderers/ChildWindowRenderer.cpp
    ui/renderers/EditBoxRenderer.cpp
    ui/renderers/LabelRenderer.cpp
    ui/renderers/ProgressBarRenderer.cpp
    ui/renderers/SliderRenderer.cpp
    ui/renderers/RadioButtonRenderer.cpp
    ui/renderers/PanelRenderer.cpp
    ui/renderers/ScrollablePanelRenderer.cpp
    ui/renderers/TabsRenderer.cpp
    ui/renderers/PictureRenderer.cpp
    ui/renderers/SeparatorRenderer.cpp
    ui/renderers/SpinButtonRenderer.cpp
    ui/renderers/MenuBarRenderer.cpp
    ui/renderers/MessageBoxRenderer.cpp
    ui/widgets/Widget.cpp
    ui/widgets/WidgetContainer.cpp
    ui/widgets/ClickableWidget.cpp
    ui/widgets/BitmapButton.cpp
    ui/widgets/Button.cpp
    ui/widgets/ToggleButton.cpp
    ui/widgets/CheckBox.cpp
    ui/widgets/EditBox.cpp
    ui/widgets/Label.cpp
    ui/widgets/ProgressBar.cpp
    ui/widgets/Slider.cpp
    ui/widgets/RadioButton.cpp
    ui/widgets/Panel.cpp
    ui/widgets/ScrollablePanel.cpp
    ui/widgets/ChildWindow.cpp
    ui/widgets/IBoxLayout.cpp
    ui/widgets/VerticalLayout.cpp
    ui/widgets/HorizontalLayout.cpp
    ui/widgets/Tabs.cpp
    ui/widgets/TabsContainer.cpp
    ui/widgets/Picture.cpp
    ui/widgets/Separator.cpp
    ui/widgets/SpinControl.cpp
    ui/widgets/MenuBar.cpp
    ui/widgets/MessageBox.cpp
    ui/GuiContainer.cpp
    graphics/Texture.cpp
    graphics/Sprite.cpp
    graphics/Colour.cpp
    graphics/Tile.cpp
    graphics/Window.cpp
    graphics/WindowImpl.cpp
    graphics/SpriteSheet.cpp
    graphics/SpriteSheetContainer.cpp
    graphics/shapes/Shape.cpp
    graphics/shapes/RectangleShape.cpp
    graphics/shapes/CircleShape.cpp
    graphics/shapes/ConvexShape.cpp
    graphics/DebugDrawer.cpp
    graphics/Camera.cpp
    graphics/SpriteImage.cpp
    graphics/TextureAtlas.cpp
    utility/ConfigFileParser.cpp
    utility/ConsoleLogger.cpp
    utility/DiskFileLogger.cpp
    utility/DiskFileReader.cpp
    utility/Helpers.cpp
    utility/Utils.cpp)

# Optimize single build
if(IME_OPTIMIZE_SINGLE_BUILD)
    list(LENGTH IME_SRC fileCount)
    if(IME_OPTIMIZE_SINGLE_BUILD_THREADS)
        set(threads ${IME_OPTIMIZE_SINGLE_BUILD_THREADS})
    else()
        include(ProcessorCount)
        ProcessorCount(threads)
    endif()

    if(${threads} LESS ${fileCount})
        math(EXPR threads "(${threads} / 2) + 1")
        math(EXPR fileCountMinusOne "${fileCount} - 1")
        math(EXPR threadsMinusOne "${threads} - 1")

        set(NEW_IME_SRC "")
        foreach(i RANGE 0 ${threadsMinusOne})
            set(OutputFile "${CMAKE_CURRENT_SOURCE_DIR}/CombinedSources-${i}.cpp")
            file(WRITE "${OutputFile}" "")
            foreach(j RANGE ${i} ${fileCountMinusOne} ${threads})
                list(GET IME_SRC ${j} inputFile)
                file(READ ${inputFile} CONTENTS)
                file(APPEND "${OutputFile}" "${CONTENTS}")
                list(APPEND NEW_IME_SRC "${OutputFile}")
            endforeach()
        endforeach()

        set(IME_SRC ${NEW_IME_SRC})
    endif()
endif()

# Create library and determine suffixes depending on static/shared configuration
if(IME_SHARED_LIBS)
    add_library(ime SHARED ${IME_SRC})
    set_target_properties(ime PROPERTIES DEFINE_SYMBOL IME_EXPORTS)
    set_target_properties(ime PROPERTIES DEBUG_POSTFIX -d)

    # Set the version of the target
    set_target_properties(ime PROPERTIES VERSION ${IME_VERSION_MAJOR}.${IME_VERSION_MINOR}.${IME_VERSION_PATCH})

    # on Windows/gcc get rid of "lib" prefix for shared libraries,
    # and transform the ".dll.a" suffix into ".a" for import libraries
    if(IME_OS_WINDOWS AND IME_COMPILER_GCC)
        set_target_properties(ime PROPERTIES PREFIX "")
        set_target_properties(ime PROPERTIES IMPORT_SUFFIX ".a")
    endif()

else()
    add_library(ime STATIC ${IME_SRC})
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

if(IME_OPTIMIZE_SINGLE_BUILD AND IME_COMPILER_MSVC)
    target_compile_options(ime PRIVATE /bigobj)
endif()

# Add <project>/include as public include directory
target_include_directories(ime PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_include_directories(ime INTERFACE $<INSTALL_INTERFACE:include>)

# Link TGUI and SFML
target_link_libraries(ime PRIVATE box2d::box2d tgui sfml-graphics sfml-window sfml-system sfml-audio)

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
ime_export_target(IMEConfigExport)
