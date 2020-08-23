include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE IME_SRC_FILES ${PROJECT_SOURCE_DIR}/src *.cpp *.inl)
file(GLOB_RECURSE CMAKE_MAIN "cmake-build-debug/*")
list(REMOVE_ITEM IN IME_SRC_FILES ${CMAKE_MAIN})

add_library(ime SHARED ${IME_SRC_FILES})
target_include_directories(ime PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(ime PRIVATE ${CMAKE_SOURCE_DIR}/src)

# set the output directory for IME libraries
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

#Set version and soversion for the target
set_target_properties(ime PROPERTIES VERSION ${IME_VERSION_MAJOR}.${IME_VERSION_MINOR}.${IME_VERSION_PATCH})
set_target_properties(ime PROPERTIES SOVERSION 1)

#Find and add SFML
set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/extlibs/SFML/include")
set(SFML_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/extlibs/SFML/lib")
set(SFML_DIR "${PROJECT_SOURCE_DIR}/extlibs/SFML/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics audio)

if(SFML_FOUND)
    target_link_libraries (ime PUBLIC sfml-graphics sfml-window sfml-system sfml-audio)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARY_DIR}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

file(GLOB_RECURSE IME_PUBLIC_HEADERS ${PROJECT_SOURCE_DIR}/include *.h)
file(GLOB_RECURSE CMAKE_MAIN "cmake-build-debug/*" )
list(REMOVE_ITEM IN IME_PUBLIC_HEADERS ${CMAKE_MAIN})
set_target_properties(ime PROPERTIES PUBLIC_HEADER "${IME_PUBLIC_HEADERS}")

install(TARGETS ime
        LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/IME
        ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/IME/lib
        PUBLIC_HEADER DESTINATION ${PROJECT_BINARY_DIR}/IME/include)

install(TARGETS ime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
