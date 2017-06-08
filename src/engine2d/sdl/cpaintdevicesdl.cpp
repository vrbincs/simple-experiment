#include "logging.h"

#include "cpixmap.h"
#include "cpaintsurfacesdl.h"
#include "cpaintdevicesdl.h"

CPaintDeviceSDL::CPaintDeviceSDL(CPixmap *pixmap)
   : m_pDestPixmap(pixmap)
{
}

CPaintDeviceSDL::~CPaintDeviceSDL()
{
}

bool CPaintDeviceSDL::start(CPixmap *pixmap)
{
   if(m_pDestPixmap == NULL)
   {
      m_pDestPixmap = pixmap;
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
   if(m_pDestPixmap)
   {
      CPaintSurfaceSDL *paintSurface = dynamic_cast<CPaintSurfaceSDL *>(m_pDestPixmap->getPaintSurface());
      
      if(paintSurface)
      {
         SDL_Flip(paintSurface->getSDLSurface());
      }
   }
   
   return true;
}

IPaintSurface *CPaintDeviceSDL::createPaintSurface() const
{
   return new CPaintSurfaceSDL();
}

IPaintDevice *CPaintDeviceSDL::getPaintDevice() const
{
   
}
