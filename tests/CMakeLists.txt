# Include doctest unit testing framework
include_directories("${PROJECT_SOURCE_DIR}/extlibs/doctest")

# Set unit tests source files
set(IME_TEST_SRC
        Test_Main.cpp
        Test_Colour.cpp
        Test_Vector2.cpp
        Test_Keyboard.cpp
        Test_Mouse.cpp
        Test_Timer.cpp
        Test_Property.cpp
        Test_Rect.cpp)

# Change executable output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Create test executable
add_executable(tests ${IME_TEST_SRC})
target_include_directories(tests PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(tests PRIVATE ime)

ime_set_global_compile_flags(tests)
ime_set_stdlib(tests)