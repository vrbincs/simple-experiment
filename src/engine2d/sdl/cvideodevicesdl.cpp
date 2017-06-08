#include <SDL.h>

#include "logging.h"
#include "cpaintsurfacesdl.h"
#include "cpaintdevicesdl.h"
#include "cvideodevicesdl.h"

static CPaintSurfaceSDL *l_screenSurface = NULL;

CVideoDeviceSDL::CVideoDeviceSDL(const CSizeI &resolution)
{
   if(l_screenSurface == NULL)
   {
      SDL_Init(SDL_INIT_EVERYTHING);
      
      SDL_Surface *surface = SDL_SetVideoMode(resolution.getWidth(), 
                                              resolution.getHeight(),
                                              32,
                                              SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_NOFRAME);

      if(surface)
      {
         l_screenSurface = new CPaintSurfaceSDL(surface);
      }
   }
   else
   {
      LOGGER_ERROR("SDL screen has already been initialized.");
   }
}

CVideoDeviceSDL::~CVideoDeviceSDL()
{
   delete l_screenSurface;
   SDL_Quit();
}

IVideoDevice::DeviceType CVideoDeviceSDL::type() const
{
   return DeviceTypeSdl;
}

IPaintSurface *CVideoDeviceSDL::createPaintSurface() const
{
   return new CPaintSurfaceSDL();
}

IPaintDevice *CVideoDeviceSDL::createPaintDevice(CPixmap *pixmap) const
{
   return new CPaintDeviceSDL(pixmap);
}

IPaintDevice *CVideoDeviceSDL::getPaintDevice()
{
   return NULL;
}

bool CVideoDeviceSDL::start()
{
   return false;
}

bool CVideoDeviceSDL::end()
{
   return false;
}
