cmake_minimum_required (VERSION 2.6)
project ( seEngine2d )

include ( FindPkgConfig )

set ( seEngine2d_VERSION_MAJOR 1 )
set ( seEngine2d_VERSION_MINOR 0 )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")

pkg_check_modules ( LOG4CPLUS REQUIRED log4cplus )
pkg_check_modules ( GSL       REQUIRED gsl )
pkg_check_modules ( SDL2      REQUIRED sdl2 )

include_directories ( "${PROJECT_SOURCE_DIR}" )
 

set ( SOURCES cengine2d.cpp
              celement.cpp
              cpainttool.cpp
              cpixmap.cpp
              csceneitem.cpp
              cscene.cpp
              csceneview.cpp
              ccolour.cpp
              cevent.cpp
              ctransform.cpp
              input/ckeylistener.cpp
              extra/cspritequeue.cpp
              extra/cspriteitem.cpp
              )

set ( SOURCES ${SOURCES} tools/cdigitool.cpp
                         tools/cdigitsbitmap.cpp
                         tools/cxbmloader.cpp )

if (UNIX)
   include_directories ( ${SDL2_INCLUDE_DIRS} )
   include_directories ( platform/linux/ )
   
   set ( SOURCES ${SOURCES} platform/linux/cenginedevicelinux.cpp
                            platform/linux/cpaintdevicesdl.cpp
                            platform/linux/ctexturesdl.cpp
                            platform/linux/cvideodevicesdl.cpp
                            platform/linux/crenderdevicesdl.cpp
                            platform/linux/ckeyeventfactorysdl.cpp
                            platform/linux/cvideodevicepseudo.cpp
                            platform/linux/cpaintsurfacepseudo.cpp
                            platform/linux/cpaintdevicepseudo.cpp)
   
   set ( LINK_LIBS ${LINK_LIBS}
                   ${SDL2_LIBRARIES}
                   -lSDL2_ttf )
endif (UNIX)


add_library(seEngine2d SHARED ${SOURCES})

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

target_link_libraries ( seEngine2d ${LINK_LIBS} )
