#include "cpaintdevicesdl.h"

int CPaintDeviceSDL::getWidth() const
{
   if(pSurface)
   {
      return pSurface->width;
   }
   return 0;
}

int CPaintDeviceSDL::getHeight() const
{
   if(pSurface)
   {
      return pSurface->height;
   }
   return 0;
}

void CPaintDeviceSDL::drawRect(const CRectI &rect)
{
}

CPaintDeviceSDL::CPaintDeviceSDL(SDL_Surface *pSurface)
   : m_pSurface(pSurface)
{
}

CPaintDeviceSDL::CPaintDeviceSDL(CPixmap *pPixmap)
{
   if(pPixmap && pPixmap->getBuffer())
   {
      uint32_t pitch = (pPixmap->getWidth() * pPixmap->getBpp());
      SDL_CreateRGBSurfaceFrom(pPixmap->getBuffer(),
                               pPixmap->getWidth(),
                               pPixmap->getHeight(),
                               pPixmap->getBpp(),
                               pitch,
                               0xff000000,
                               0x00ff0000,
                               0x0000ff00,
                               0x000000ff);
   }
}
