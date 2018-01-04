#include <memory>
#include <SDL.h>

#include "logging.h"
#include "ctexturesdl.h"
#include "cvideodevicesdl.h"
#include "ccolour.h"

CTextureSDL::CTextureSDL(CVideoDeviceSDL *videoDevice,
                                   SDL_Surface *surface)
   : m_videoDevice(videoDevice),
     m_sdlTexture(NULL),
     m_width(0),
     m_height(0),
     m_bpp(0)
{
   if(surface)
   {
      m_width = surface->w;
      m_height = surface->h;
      m_bpp = surface->format->BitsPerPixel;
      
      convertSurfaceToTexture(surface);
   }
}

CTextureSDL::~CTextureSDL()
{
   freeSurface();
}

bool CTextureSDL::allocateFromBuffer(uint8_t *pixelBuffer, 
                                          uint32_t width, 
                                          uint32_t height,
                                          uint8_t bpp)
{
   freeSurface();
   
   std::shared_ptr<uint8_t> pixelBufferPtr(pixelBuffer);
   m_bpp = bpp;
   m_width = width;
   m_height = height;

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
   
   SDL_Surface *surface = SDL_CreateRGBSurfaceFrom((void *)pixelBuffer,
                                                   width,
                                                   height,
                                                   m_bpp,
                                                   pitch,
                                                   rmask,
                                                   gmask,
                                                   bmask,
                                                   amask);

   bool ok = false;

   if(surface != NULL)
   {
      ok = convertSurfaceToTexture(surface);
   }
   else
   {
      LOGGER_ERROR("Unable to create SDL surface. sdlError=" << SDL_GetError() << ", pixelFormat=" << (int)m_bpp);
   }
   
   return ok;
}

bool CTextureSDL::allocateFromFile(const std::string &fileName,
                                        const std::string &type)
{
   bool ok = false;
   freeSurface();
   
   if(type == "bmp")
   {
      SDL_Surface *surface = SDL_LoadBMP(fileName.c_str());
      if(surface)
      {
         m_width = surface->w;
         m_height = surface->h;
         m_bpp = surface->format->BitsPerPixel;
         
         ok = convertSurfaceToTexture(surface);
      }
   }
   
   return ok;
}

uint8_t CTextureSDL::getBitsPerPixels() const
{
   return m_bpp;
}

uint32_t CTextureSDL::getHeight() const
{
   return m_height;
}

uint32_t CTextureSDL::getWidth() const
{
   return m_width;
}

void CTextureSDL::lock()
{
   if(m_sdlTexture)
   {
      void *pixelPtr;
      int pitch;
      SDL_LockTexture(m_sdlTexture, NULL, &pixelPtr, &pitch);
   }
}

void CTextureSDL::unlock()
{
   if(m_sdlTexture)
   {
      SDL_UnlockTexture(m_sdlTexture);
   }
}

bool CTextureSDL::isNull() const
{
   return (m_sdlTexture == NULL);
}

IVideoDevice *CTextureSDL::getVideoDevice() const
{
   return m_videoDevice;
}

SDL_Texture *CTextureSDL::getSDLTexture() const
{
   return m_sdlTexture;
}

CColour CTextureSDL::getPixelAt(const CPointI &pos) const
{
   CColour colour;
   
   if(m_sdlTexture)
   {
      
   }
   
   return colour;
}

void CTextureSDL::freeSurface()
{
   if(m_sdlTexture)
   {
      SDL_DestroyTexture(m_sdlTexture);
   }
   
   m_sdlTexture = NULL;
   m_width = m_height = m_bpp = 0;
}

bool CTextureSDL::convertSurfaceToTexture(SDL_Surface *surface)
{
   if(surface)
   {
      m_sdlTexture = SDL_CreateTextureFromSurface(m_videoDevice->getSDLRenderer(),
                                                  surface);
      SDL_FreeSurface(surface);

      if(m_sdlTexture == NULL)
      {
         LOGGER_ERROR("Unable to create SDL texture. sdlError=" << SDL_GetError());
      }
      else
      {
         return true;
      }
   }
   else
   {
      LOGGER_ERROR("NULL Surface.");
   }
   
   return false;
}
