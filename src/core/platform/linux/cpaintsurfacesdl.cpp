#include <SDL.h>

#include "logging.h"
#include "cpaintsurfacesdl.h"
#include "cvideodevicesdl.h"

CPaintSurfaceSDL::CPaintSurfaceSDL(CVideoDeviceSDL *videoDevice,
                                   SDL_Surface *surface)
   : m_videoDevice(videoDevice),
     m_sdlSurface(surface),
     m_width(0),
     m_height(0)
{
   if(m_sdlSurface)
   {
      m_width = m_sdlSurface->w;
      m_height = m_sdlSurface->h;
      m_bpp = m_sdlSurface->format->BitsPerPixel;
   }
}

CPaintSurfaceSDL::~CPaintSurfaceSDL()
{
   freeSurface();
}

bool CPaintSurfaceSDL::allocate(uint32_t width, 
                                uint32_t height,
                                uint8_t bpp)
{
   freeSurface();
   
   m_width = width;
   m_height = height;
   m_bpp = bpp;
   
   if(m_bpp == 32)
   {
   
      m_sdlSurface = SDL_CreateRGBSurface(0,
                                          width,
                                          height,
                                          bpp,
                                          0xFF000000,
                                          0x00FF0000,
                                          0x0000FF00,
                                          0x000000FF);

      m_sdlTexture = SDL_CreateTexture(m_videoDevice->getSDLRenderer(),
                                       SDL_PIXELFORMAT_RGBA8888,
                                       SDL_TEXTUREACCESS_STREAMING, // note that STREAMING is a hint that tells the renderer to upate the pixels frequently
                                       width,
                                       height);
   }
   else
   {
      LOGGER_WARN("The requested depth for the surface not supported. depth=" << m_bpp);
   }

   return m_sdlSurface;
}

uint8_t CPaintSurfaceSDL::getBitsPerPixels() const
{
   return m_bpp;
}

uint32_t CPaintSurfaceSDL::getHeight() const
{
   return m_height;
}

uint32_t CPaintSurfaceSDL::getWidth() const
{
   return m_width;
}

void CPaintSurfaceSDL::lock()
{
   if(m_sdlSurface)
   {
      SDL_LockSurface(m_sdlSurface);
   }
}

void CPaintSurfaceSDL::unlock()
{
   if(m_sdlSurface)
   {
      SDL_UnlockSurface(m_sdlSurface);
   }
}

SDL_Surface *CPaintSurfaceSDL::getSDLSurface()
{
   return m_sdlSurface;
}

void CPaintSurfaceSDL::freeSurface()
{
   m_width = m_height = m_bpp = 0;
   
   SDL_FreeSurface(m_sdlSurface);
   SDL_DestroyTexture(m_sdlTexture);
}
