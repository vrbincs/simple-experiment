#include <SDL.h>

#include "cpaintsurfacesdl.h"
#include "cpaintdevicesdl.h"
#include "cvideodevicesdl.h"

CVideoDeviceSDL::CVideoDeviceSDL(const CSizeI &resolution)
   : m_basePaintSurface(NULL),
     m_window(NULL),
     m_renderer(NULL)
{
   SDL_Init(SDL_INIT_EVERYTHING);
   SDL_CreateWindowAndRenderer(resolution.getWidth(), 
                               resolution.getHeight(),
                               0,
                               &m_window,
                               &m_renderer);
   
   SDL_Surface *surface = SDL_SetVideoMode(resolution.getWidth(), 
                                           resolution.getHeight(),
                                           32,
                                           SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_NOFRAME);

   

   if(surface)
   {
      m_basePaintSurface = new CPaintSurfaceSDL(surface);
   }
}

CVideoDeviceSDL::~CVideoDeviceSDL()
{
   SDL_DestroyRenderer(m_renderer);
   SDL_DestroyWindow(m_window);
   SDL_Quit();
}

IVideoDevice::DeviceType CVideoDeviceSDL::type() const
{
   return DeviceTypeSdl;
}

IPaintSurface *CVideoDeviceSDL::createPaintSurface() const
{
   return new CPaintSurfaceSDL(this);
}

IPaintDevice *CVideoDeviceSDL::createPaintDevice(IPaintSurface *surface const
{
   return new CPaintDeviceSDL(surface);
}

IPaintDevice *CVideoDeviceSDL::getPaintDevice()
{
   return m_paintDevice;
}

bool CVideoDeviceSDL::start()
{
   return false;
}

bool CVideoDeviceSDL::end()
{
   return false;
}
