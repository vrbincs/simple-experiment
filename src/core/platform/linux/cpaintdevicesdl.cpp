#include "logging.h"

#include "cpixmap.h"
#include "cpaintsurfacesdl.h"
#include "cpaintdevicesdl.h"
#include "cvideodevicesdl.h"

CPaintDeviceSDL::CPaintDeviceSDL(IPaintSurface *destSurface)
   : m_pDestSurface(NULL),
     m_pSdlRenderer(NULL)
{
   m_pDestSurface = dynamic_cast<CPaintSurfaceSDL *>(destSurface);
   
   if(m_pDestSurface == NULL)
   {
      LOGGER_ERROR("The destination surface is NULL. No painting can be performed.");
      return;
   }
   
   if(m_pDestSurface->m_videoDevice)
   {
      m_pSdlRenderer = m_pDestSurface->m_videoDevice->getSDLRenderer();
   }
   
   if(m_pSdlRenderer == NULL)
   {
      LOGGER_ERROR("SDL renderer not found");
   }
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

void CPaintDeviceSDL::drawRect(const CRectI &rect,
                               const CColour &colour)
{   
   LOGGER_WARN("Not implemented");
}

void CPaintDeviceSDL::drawSurface(const IPaintSurface &paintSurface,
                                  const CPointI &pos,
                                  const CRectI *srcRect)
{
   LOGGER_WARN("Not implemented");
}

void CPaintDeviceSDL::drawText(const std::string &text, const CRectI &rect, const CColour &colour)
{
   LOGGER_WARN("Not implemented");
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
