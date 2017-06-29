cmake_minimum_required(VERSION 2.6)

project (simple-experiment-engine-2d)

set(CMAKE_BUILD_TYPE Release)
if(${build} STREQUAL debug)
   set(CMAKE_BUILD_TYPE Debug)
   message(STATUS "The projects will be build in debug mode")
endif()

add_subdirectory(src/core)
add_subdirectory(tests/gtest/engine2d)
add_subdirectory(tests/quicktests/ballmove)
add_subdirectory(tests/quicktests/rotatingballs)
