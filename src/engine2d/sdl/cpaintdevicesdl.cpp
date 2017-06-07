#include "logging.h"

#include "cpixmap.h"
#include "cpaintsurfacesdl.h"
#include "cpaintdevicesdl.h"

CPaintDeviceSDL::CPaintDeviceSDL(CPixmap *pixmap)
   : m_pPixmap(pixmap)
{
}

CPaintDeviceSDL::~CPaintDeviceSDL()
{
}

bool CPaintDeviceSDL::start(CPixmap *pixmap)
{
   if(!m_pPixmap)
   {
      m_pPixmap = pixmap;
      return true;
   }
   else
   {
      return false;
      LOGGER_WARN("This paint device has already stared");
   }
}

void CPaintDeviceSDL::drawRect(const CRectI &rect)
{
}

bool CPaintDeviceSDL::end()
{
   if(m_pPixmap)
   {
      CPaintSurfaceSDL *paintSurface = dynamic_cast<CPaintSurfaceSDL *>(m_pPixmap->getPaintSurface());
      
      if(paintSurface)
      {
         SDL_Flip(paintSurface->getSDLSurface());
      }
   }
   
   return true;
}
