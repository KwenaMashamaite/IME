set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
add_executable(Driver main.cpp)
target_link_libraries(Driver PRIVATE ime)