cmake_minimum_required (VERSION 2.6)
project ( testengine2d )

include ( FindPkgConfig )

set ( testengine2d_VERSION_MAJOR 1 )
set ( testengine2d_VERSION_MINOR 0 )

include_directories ( ${seEngine2d_SOURCE_DIR} )

#set(CMAKE_CXX_FLAGS "-Wall -Wno-long-long -Werror -pedantic -O0")

pkg_check_modules ( GTEST REQUIRED gtest )
pkg_check_modules ( GMOCK REQUIRED gmock )

find_package (Threads REQUIRED)

add_executable ( testengine2d testcgobject.cpp
                              testcrect.cpp
                              testcscene.cpp
                              testcsceneitem.cpp
                              csceneitemtestfactory.cpp )

target_link_libraries ( testengine2d ${GTEST_LIBRARIES}
                                     -lgmock
                                     ${CMAKE_THREAD_LIBS_INIT}
                                     seEngine2d )

include_directories ( ${GTEST_INCLUDE_DIRS}
                      ${GMOCK_INCLUDE_DIRS}
                      ${UUID_INCLUDE_DIRS} )

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
