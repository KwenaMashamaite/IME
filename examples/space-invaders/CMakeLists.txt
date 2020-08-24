file(GLOB_RECURSE SPACE_INVADERS_SRC_FILES ${PROJECT_SOURCE_DIR}/examples/space-invaders/src *.cpp)
file(GLOB_RECURSE CMAKE_MAIN "cmake-build-debug/*")
list(REMOVE_ITEM IN SPACE_INVADERS_SRC_FILES ${CMAKE_MAIN})

#Change executable output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(SpaceInvaders ${SPACE_INVADERS_SRC_FILES})
target_link_libraries(SpaceInvaders PRIVATE ime)