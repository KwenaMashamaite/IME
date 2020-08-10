include_directories(${CMAKE_SOURCE_DIR}/src)
set(EXAMPLES_SRC_ROOT "${PROJECT_SOURCE_DIR}/examples")

file(GLOB_RECURSE IME_EXAMPLE_SRC_FILES ${PROJECT_SOURCE_DIR}/examples/space-invaders *.cpp *.inl)
file(GLOB_RECURSE CMAKE_MAIN "cmake-build-debug/*")
list(REMOVE_ITEM IN IME_EXAMPLE_SRC_FILES ${CMAKE_MAIN})

#Change executable output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(SpaceInvaders ${IME_EXAMPLE_SRC_FILES})
target_link_libraries(SpaceInvaders PRIVATE ime)