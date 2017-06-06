#include "logging.h"

#include "cpixmap.h"
#include "cpixelbuffersdl.h"
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
      CPixelBufferSDL *pixmapBuffer = dynamic_cast<CPixelBufferSDL *>(m_pPixmap->getPixelBuffer());
      
      if(pixmapBuffer)
      {
         SDL_Flip(pixmapBuffer->getSurface());
      }
   }
}
