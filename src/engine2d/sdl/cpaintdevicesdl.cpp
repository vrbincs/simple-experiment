#include "logging.h"

#include "cpixmap.h"
#include "cpaintsurfacesdl.h"
#include "cpaintdevicesdl.h"

CPaintDeviceSDL::CPaintDeviceSDL(IPaintSurface *destSurface)
   : m_pDestSurface(NULL)
{
   m_pDestSurface = dynamic_cast<CPaintSurfaceSDL *>(destSurface);
}

CPaintDeviceSDL::~CPaintDeviceSDL()
{
}

bool CPaintDeviceSDL::start(IPaintSurface *destSurface)
{
   m_pDestSurface = dynamic_cast<CPaintSurfaceSDL *>(destSurface);
   
   if(m_pDestSurface != NULL)
   {
      m_pDestSurface->lock();
      return true;
   }
   else
   {
      LOGGER_WARN("The destination surface is invalid.");
      return false;
   }
}

void CPaintDeviceSDL::drawRect(const CRectI &rect)
{
}

bool CPaintDeviceSDL::end()
{
   if(m_pDestSurface)
   {
      m_pDestSurface->unlock();
      return true;
   }
   else
   {
      return false;
   }
}
