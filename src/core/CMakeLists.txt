cmake_minimum_required (VERSION 2.6)
project ( engine2dcore )

include ( FindPkgConfig )

set ( engine2dcore_VERSION_MAJOR 1 )
set ( engine2dcore_VERSION_MINOR 0 )




cmake_minimum_required (VERSION 2.6)
project ( seEngine2d )

include ( FindPkgConfig )

set ( 2drender_VERSION_MAJOR 1 )
set ( 2drender_VERSION_MINOR 0 )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")

pkg_check_modules ( LOG4CPLUS REQUIRED log4cplus )
pkg_check_modules ( GSL       REQUIRED gsl )
pkg_check_modules ( SDL       REQUIRED sdl )

include_directories ( "${PROJECT_SOURCE_DIR}" )
include_directories ( ${SDL_INCLUDE_DIRS} )
 

set ( SOURCES cengine2d.cpp
              cpainttool.cpp
              cpixmap.cpp
              cevent.cpp
              csceneitem.cpp
              cscene.cpp )

if (UNIX)
   include_directories ( platform/linux/ )
   set ( SOURCES ${SOURCES} platform/linux/cenginedevicelinux.cpp
                            platform/linux/cpaintdevicesdl.cpp
                            platform/linux/cpaintsurfacesdl.cpp
                            platform/linux/cvideodevicesdl.cpp )
endif (UNIX)


add_library(seEngine2d SHARED ${SOURCES})
