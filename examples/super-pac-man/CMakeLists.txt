file(GLOB_RECURSE SUPER_PACMAN_SRC_ROOT ${PROJECT_SOURCE_DIR}/examples/super-pac-man/src *.cpp)
file(GLOB_RECURSE CMAKE_MAIN "cmake-build-debug/*")
list(REMOVE_ITEM IN SUPER_PACMAN_SRC_ROOT ${CMAKE_MAIN})

#Change executable output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(SuperPacMan ${SUPER_PACMAN_SRC_ROOT})
target_link_libraries(SuperPacMan PRIVATE ime)