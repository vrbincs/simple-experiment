cmake_minimum_required (VERSION 2.6)
project ( testengine2d )

include ( FindPkgConfig )

set ( testengine2d_VERSION_MAJOR 1 )
set ( testengine2d_VERSION_MINOR 0 )

include_directories ( ${seEngine2d_SOURCE_DIR} )

pkg_check_modules ( GTEST REQUIRED gtest )
pkg_check_modules ( SDL2  REQUIRED sdl2 )
pkg_check_modules ( UUID  REQUIRED uuid )

add_executable ( testengine2d testcgobject.cpp
                              testcrect.cpp )

target_link_libraries ( testengine2d ${GTEST_LIBRARIES}
                                     ${SDL2_LIBRARIES}
                                     ${UUID_LIBRARIES} 
                                     -lgtest_main
                                     seEngine2d )

include_directories ( ${GTEST_INCLUDE_DIRS}
                      ${UUID_INCLUDE_DIRS} )

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
