include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/extlibs/doctest/")

file(GLOB_RECURSE IME_TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/src *.cpp *.hpp)
file(GLOB_RECURSE CMAKE_MAIN "cmake-build-debug/*")
list(REMOVE_ITEM IN IME_TEST_SRC_FILES ${CMAKE_MAIN})

#Change executable output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(ime-tests ${IME_TEST_SRC_FILES})
target_link_libraries(ime-tests PRIVATE ime)
