cmake_minimum_required (VERSION 2.6)
project ( testengine2d )

include ( FindPkgConfig )

set ( 2d_render_VERSION_MAJOR 1 )
set ( 2d_render_VERSION_MINOR 0 )

include_directories ( "${PROJECT_SOURCE_DIR}/../../engine2d" )

pkg_check_modules ( GTEST REQUIRED gtest )
pkg_check_modules ( SDL   REQUIRED sdl )
pkg_check_modules ( UUID  REQUIRED uuid )

add_executable ( testengine2d testcgobject.cpp )

target_link_libraries ( testengine2d ${GTEST_LIBRARIES}
                                     ${SDL_LIBRARIES}
                                     ${UUID_LIBRARIES} 
                                     -lgtest_main
                                     ${engine2d_BINARY_DIR}/libengine2d.a )

include_directories ( ${GTEST_INCLUDE_DIRS}
                      ${UUID_INCLUDE_DIRS} )

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
