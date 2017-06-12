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
      LOGGER_ERROR("Destination surface is NULL. No painting can be performed.");
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

void CPaintDeviceSDL::drawRect(const CRectI &rect)
{   
   SDL_SetRenderDrawColor(m_pSdlRenderer, 255, 0, 0, 255);
   SDL_Rect sdlRect;
   
   sdlRect.x = rect.getX();
   sdlRect.y = rect.getY();
   sdlRect.w = rect.getWidth();
   sdlRect.h = rect.getHeight();
   
   SDL_RenderFillRect(m_pSdlRenderer, &sdlRect);
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
