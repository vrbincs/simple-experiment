#include <SDL.h>

#include "cpixelbuffersdl.h"
#include "cpaintdevicesdl.h"
#include "cvideodevicesdl.h"


CVideoDeviceSDL::CVideoDeviceSDL(const CSizeI &resolution)
   : m_basePixelBuffer(NULL),
     m_paintDevice(NULL)
{
   SDL_Init(SDL_INIT_EVERYTHING);
   
   SDL_Surface *surface = SDL_SetVideoMode(resolution.getWidth(), 
                                           resolution.getHeight(),
                                           32,
                                           SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_NOFRAME);

   

   if(surface)
   {
      m_basePixelBuffer = new CPixelBufferSDL(surface);
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

CPixelBuffer *CVideoDeviceSDL::allocatePixmap(uint32_t width, 
                                              uint32_t height,
                                              uint8_t depth)
{
   return new CPixelBufferSDL(width, height, depth);
}
