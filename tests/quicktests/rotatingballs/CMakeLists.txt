cmake_minimum_required (VERSION 2.6)
project ( rotatingballs )

include ( FindPkgConfig )

set ( rotatingballs_VERSION_MAJOR 1 )
set ( rotatingballs_VERSION_MINOR 0 )

include_directories ( ${seEngine2d_SOURCE_DIR} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -Werror -pedantic -O0")

add_executable ( rotatingballs rotatingballs.cpp )

target_link_libraries ( rotatingballs seEngine2d )
