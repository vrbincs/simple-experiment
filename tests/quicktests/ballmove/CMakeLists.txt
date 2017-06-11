cmake_minimum_required (VERSION 2.6)
project ( testballmove )

include ( FindPkgConfig )

set ( testballmove_VERSION_MAJOR 1 )
set ( testballmove_VERSION_MINOR 0 )

include_directories ( ${engine2dcore_SOURCE_DIR} )
include_directories ( ${linuxdevice_SOURCE_DIR} )

pkg_check_modules ( SDL   REQUIRED sdl )
pkg_check_modules ( UUID  REQUIRED uuid )

set(CMAKE_CXX_FLAGS "-Wall -Wno-long-long -Werror -pedantic -O0")

add_executable ( testballmove testballmove.cpp )

get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

target_link_libraries ( testballmove ${SDL_LIBRARIES}
                                     ${UUID_LIBRARIES} 
                                     seEngine2d )

include_directories ( ${UUID_INCLUDE_DIRS} )
