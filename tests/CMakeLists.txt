# Include doctest unit testing framework
include_directories(${PROJECT_SOURCE_DIR}/extlibs/doctest)

# Set test source root directory
set(SRC_ROOT ${CMAKE_CURRENT_LIST_DIR}/src)

# Set unit tests source files
set(SRC_FILES
        ${SRC_ROOT}/unitTestsMain.cpp
    )

# Change executable output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Create test executable
add_executable(tests ${SRC_FILES})

# Link IME, TGUI and SFML
target_link_libraries(tests PRIVATE tgui sfml-graphics sfml-window sfml-system sfml-audio ime)