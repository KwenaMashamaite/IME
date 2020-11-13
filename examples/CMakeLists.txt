set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(Driver main.cpp)
target_link_libraries(Driver PRIVATE ime tgui sfml-graphics sfml-window sfml-system sfml-audio)