cmake_minimum_required (VERSION 2.6)
project ( testballmove )

include ( FindPkgConfig )

set ( testballmove_VERSION_MAJOR 1 )
set ( testballmove_VERSION_MINOR 0 )

include_directories ( ${seEngine2d_SOURCE_DIR} )

set(CMAKE_CXX_FLAGS "-Wall -Wno-long-long -Werror -pedantic -O0")

add_executable ( testballmove testballmove.cpp )

target_link_libraries ( testballmove seEngine2d )

include_directories ( ${UUID_INCLUDE_DIRS} )
