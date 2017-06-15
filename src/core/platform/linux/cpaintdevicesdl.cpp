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

void CPaintDeviceSDL::drawRect(const CRectI &rect)
{   
   SDL_SetRenderDrawColor(m_pSdlRenderer, 255, 0, 0, 255);
   SDL_Rect sdlRect;
   
   setSdlRect(sdlRect, rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
   
   SDL_RenderFillRect(m_pSdlRenderer, &sdlRect);
}

void CPaintDeviceSDL::drawSurface(const IPaintSurface &paintSurface,
                                  const CPointI &pos)
{
   const CPaintSurfaceSDL *paintSurfaceSdl = dynamic_cast<const CPaintSurfaceSDL *>(&paintSurface);
   if(paintSurfaceSdl)
   {
      SDL_Rect sdlRect;
      setSdlRect(sdlRect, 
                 pos.getX(),
                 pos.getY(),
                 paintSurface.getWidth(),
                 paintSurface.getHeight());
      
      LOGGER_ERROR("RECT=" << pos.getX() << ":" << pos.getY() << ":" << paintSurface.getWidth() << ":" << paintSurface.getHeight());
      
      if(SDL_RenderCopy(m_pSdlRenderer,
                        paintSurfaceSdl->getSDLTexture(),
                        NULL,
                        &sdlRect) != 0)
      {
         LOGGER_ERROR("Unable to render texture. err=" << SDL_GetError());
      }
   }
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
