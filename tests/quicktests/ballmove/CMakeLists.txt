cmake_minimum_required (VERSION 2.6)
project ( testballmove )

include ( FindPkgConfig )

set ( testballmove_VERSION_MAJOR 1 )
set ( testballmove_VERSION_MINOR 0 )

include_directories ( "${PROJECT_SOURCE_DIR}/../../../src/engine2d" )

pkg_check_modules ( GTEST REQUIRED gtest )
pkg_check_modules ( SDL   REQUIRED sdl )
pkg_check_modules ( UUID  REQUIRED uuid )

set(CMAKE_CXX_FLAGS "-Wall -Wno-long-long -Werror -pedantic")

add_executable ( testballmove testballmove.cpp )

target_link_libraries ( testballmove ${GTEST_LIBRARIES}
                                     ${SDL_LIBRARIES}
                                     ${UUID_LIBRARIES} 
                                     ${engine2d_BINARY_DIR}/libengine2d.a )

include_directories ( ${GTEST_INCLUDE_DIRS}
                      ${UUID_INCLUDE_DIRS} )
