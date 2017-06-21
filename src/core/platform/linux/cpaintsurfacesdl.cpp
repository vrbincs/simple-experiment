#include <SDL.h>

#include "logging.h"
#include "cpaintsurfacesdl.h"
#include "cvideodevicesdl.h"

CPaintSurfaceSDL::CPaintSurfaceSDL(CVideoDeviceSDL *videoDevice,
                                   SDL_Surface *surface)
   : m_videoDevice(videoDevice),
     m_sdlSurface(surface),
     m_sdlTexture(NULL),
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
}

bool CPaintSurfaceSDL::allocateFromBuffer(uint8_t *pixelBuffer, 
                                          uint32_t width, 
                                          uint32_t height,
                                          uint8_t bpp)
{
   freeSurface();
   
   m_bpp = bpp;
   m_width = width;
   m_height = height;
   m_pixelBuffer = pixelBuffer;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
   uint32_t rmask = 0xFF000000;
   uint32_t gmask = 0x00FF0000;
   uint32_t bmask = 0x0000FF00;
   uint32_t amask = 0x000000FF;
#else
   uint32_t rmask = 0x000000FF;
   uint32_t gmask = 0x0000FF00;
   uint32_t bmask = 0x00FF0000;
   uint32_t amask = 0xFF000000;
#endif
   
   uint32_t pitch = 0;
   int8_t depth = 1;
   
   if(m_bpp > 8)
   {
      depth = (m_bpp/8);
   }
   
   pitch = (m_width * depth);
   
   m_sdlSurface = SDL_CreateRGBSurfaceFrom((void *)pixelBuffer,
                                           width,
                                           height,
                                           m_bpp,
                                           pitch,
                                           rmask,
                                           gmask,
                                           bmask,
                                           amask);

   if(m_sdlSurface == NULL)
   {
      LOGGER_ERROR("Unable to create SDL surface. sdlError=" << SDL_GetError() << ", pixelFormat=" << (int)m_bpp);
   }
   else
   {
      createTexture();
   }
   
   return m_sdlSurface;
}

bool CPaintSurfaceSDL::allocateFromFile(const std::string &fileName,
                                        const std::string &type)
{
   freeSurface();
   
   if(type == "bmp")
   {
      m_sdlSurface = SDL_LoadBMP(fileName.c_str());
      if(m_sdlSurface)
      {
         m_width = m_sdlSurface->w;
         m_height = m_sdlSurface->h;
         m_bpp = m_sdlSurface->format->BitsPerPixel;
         
         createTexture();
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

SDL_Texture *CPaintSurfaceSDL::getSDLTexture() const
{
   return m_sdlTexture;
}

void CPaintSurfaceSDL::freeSurface()
{
   if(m_sdlSurface)
   {
      SDL_FreeSurface(m_sdlSurface);
   }
   
   if(m_sdlTexture)
   {
      SDL_DestroyTexture(m_sdlTexture);
   }
   
   if(m_pixelBuffer)
   {
      delete [] m_pixelBuffer;
   }
   
   m_sdlSurface = NULL;
   m_sdlTexture = NULL;
   m_pixelBuffer = NULL;
   m_width = m_height = m_bpp = 0;
}

bool CPaintSurfaceSDL::createTexture()
{
   m_sdlTexture = SDL_CreateTextureFromSurface(m_videoDevice->getSDLRenderer(),
                                               m_sdlSurface);

   if(m_sdlTexture == NULL)
   {
      LOGGER_ERROR("Unable to create SDL texture. sdlError=" << SDL_GetError());
      return false;
   }
   
   return true;
}
