#include <SDL.h>

#include "cpixelbuffersdl.h"

CPixelBufferSDL::CPixelBufferSDL(SDL_Surface *surface)
   : CPixelBuffer(NULL),
     m_sdlSurface(surface)
{
   
}

CPixelBufferSDL::CPixelBufferSDL(uint32_t width, uint32_t height, uint8_t bpp)
   : CPixelBuffer(NULL)
{
   m_sdlSurface = SDL_CreateRGBSurface(0,
                                       width,
                                       height,
                                       depth,
                                       0xFF000000,
                                       0x00FF0000,
                                       0x0000FF00,
                                       0x000000FF);
}

CPixelBufferSDL::~CPixelBufferSDL()
{
   release();
}

void CPixelBufferSDL::*getBuffer()
{
   if(m_sdlSurface)
   {
      return m_sdlSurface->pixels;
   }
}

void *CPixelBufferSDL::release()
{
   if(m_sdlSurface)
   {
      SDL_FreeSurface(m_sdlSurface);
      m_sdlSurface = NULL;
   }
   
   return NULL;
}

void CPixelBufferSDL::lock()
{
   if(m_sdlSurface)
   {
      SDL_LockSurface(surface);
   }
}

void CPixelBufferSDL::unlock()
{
   if(m_sdlSurface)
   {
      SDL_UnlockSurface(surface);
   }
}

SDL_Surface *CPixelBufferSDL::getSurface()
{
   return m_sdlSurface;
}
