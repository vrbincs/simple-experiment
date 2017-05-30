cmake_minimum_required (VERSION 2.6)
project ( engine2d )

include ( FindPkgConfig )

set ( 2drender_VERSION_MAJOR 1 )
set ( 2drender_VERSION_MINOR 0 )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")

pkg_check_modules ( LOG4CPLUS REQUIRED log4cplus )
pkg_check_modules ( GSL       REQUIRED gsl )
pkg_check_modules ( SDL       REQUIRED sdl )

include_directories ( "${PROJECT_SOURCE_DIR}" )
include_directories ( ${SDL_INCLUDE_DIRS} )

add_library ( engine2d cgobject.cpp
                       cdrawingtool.cpp )

target_link_libraries ( engine2d ${LOG4CPLUS_LIBRARIES}
                                 ${GSL_LIBRARIES}
                                 ${SDL_LIBRARIES} )
