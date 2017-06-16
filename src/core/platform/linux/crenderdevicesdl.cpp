#include "logging.h"

#include "cpixmap.h"
#include "cpaintsurfacesdl.h"
#include "cvideodevicesdl.h"
#include "crenderdevicesdl.h"

CRenderDeviceSDL::CRenderDeviceSDL(SDL_Renderer *render)
   : m_pSdlRenderer(render)
{
   if(m_pSdlRenderer)
   {
      LOGGER_ERROR("SDL renderer not found");
   }
}

CRenderDeviceSDL::~CRenderDeviceSDL()
{
}

bool CRenderDeviceSDL::start(IPaintSurface *destSurface)
{
   LOGGER_INFO("This rendering device (CRenderDeviceSDL) is only\
                capable drawing on the framebuffer. The destination\
                surface is ignored.");
   return true;
}

void CRenderDeviceSDL::drawRect(const CRectI &rect)
{
   SDL_SetRenderDrawColor(m_pSdlRenderer, 255, 0, 0, 255);
   SDL_Rect sdlRect;
   
   setSdlRect(sdlRect, rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
   
   SDL_RenderFillRect(m_pSdlRenderer, &sdlRect);
}

void CRenderDeviceSDL::drawSurface(const IPaintSurface &paintSurface,
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

bool CRenderDeviceSDL::end()
{
   return true;
}
