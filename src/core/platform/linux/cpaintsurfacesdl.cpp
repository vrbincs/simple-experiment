#include <SDL.h>

#include "logging.h"
#include "cpaintsurfacesdl.h"
#include "cvideodevicesdl.h"

CPaintSurfaceSDL::CPaintSurfaceSDL(CVideoDeviceSDL *videoDevice,
                                   SDL_Surface *surface)
   : m_videoDevice(videoDevice),
     m_sdlSurface(surface),
     m_width(0),
     m_height(0),
     m_pixelBuffer(NULL)
{
   if(m_sdlSurface)
   {
      m_width = m_sdlSurface->w;
      m_height = m_sdlSurface->h;
      m_bpp = m_sdlSurface->format->BitsPerPixel;
      
      createTexture();
   }
}

CPaintSurfaceSDL::~CPaintSurfaceSDL()
{
   freeSurface();
   delete [] m_pixelBuffer;
}

bool CPaintSurfaceSDL::allocateFromBuffer(uint8_t *pixelBuffer, 
                                          uint32_t width, 
                                          uint32_t height,
                                          uint8_t bpp)
{
   freeSurface();
   
   m_width = width;
   m_height = height;
   m_bpp = bpp;
   m_pixelBuffer = pixelBuffer;
   
   if(m_bpp == 32)
   {
      uint32_t pitch = (width * 4);
      m_sdlSurface = SDL_CreateRGBSurfaceFrom((void *)pixelBuffer,
                                              width,
                                              height,
                                              bpp,
                                              pitch,
                                              0xFF000000,
                                              0x00FF0000,
                                              0x0000FF00,
                                              0x000000FF);

      createTexture();
   }
   else
   {
      LOGGER_WARN("The requested depth for the surface not supported. depth=" << m_bpp);
   }

   return m_sdlSurface;
}

bool CPaintSurfaceSDL::allocateFromFile(const std::string &fileName,
                                        const std::string &type)
{
   if(type == "bmp")
   {
      m_sdlSurface = SDL_LoadBMP(fileName.c_str());
      if(m_sdlSurface)
      {
         m_width = m_sdlSurface->w;
         m_height = m_sdlSurface->h;
         m_bpp = m_sdlSurface->format->BitsPerPixel;
      }
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

IVideoDevice *CPaintSurfaceSDL::getVideoDevice() const
{
   return m_videoDevice;
}

SDL_Surface *CPaintSurfaceSDL::getSDLSurface() const
{
   return m_sdlSurface;
}

void CPaintSurfaceSDL::freeSurface()
{
   m_width = m_height = m_bpp = 0;
   
   if(m_sdlSurface)
   {
      SDL_FreeSurface(m_sdlSurface);
   }
   
   if(m_sdlTexture)
   {
      SDL_DestroyTexture(m_sdlTexture);
   }
}

bool CPaintSurfaceSDL::createTexture()
{
   m_sdlTexture = SDL_CreateTexture(m_videoDevice->getSDLRenderer(),
                                    SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_STREAMING, // note that STREAMING is a hint that tells the renderer to upate the pixels frequently
                                    m_width,
                                    m_height);

   if(m_sdlTexture == NULL)
   {
      LOGGER_ERROR("Unable to create SDL texture");
      return false;
   }
   
   return true;
}
