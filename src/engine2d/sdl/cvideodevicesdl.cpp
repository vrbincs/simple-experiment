#include <SDL.h>

#include "cpaintdevicesdl.h"
#include "cvideodevicesdl.h"

CVideoDeviceSDL::CVideoDeviceSDL(const CSizeI &resolution)
   : m_paintDevice(NULL)
{
   SDL_Init(SDL_INIT_EVERYTHING);
   
   SDL_Surface *surface = SDL_SetVideoMode(resolution.getWidth(), 
                                           resolution.getHeight(),
                                           32,
                                           SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_NOFRAME);

   

   if(surface)
   {
      
   }
}

CVideoDeviceSDL::~CVideoDeviceSDL()
{
   SDL_Quit();
}

IVideoDevice::DeviceType CVideoDeviceSDL::type() const
{
   return DeviceTypeSdl;
}

IPaintDevice *CVideoDeviceSDL::getPaintDevice()
{
   return m_paintDevice;
}

