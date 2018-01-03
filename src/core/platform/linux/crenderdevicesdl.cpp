#include <SDL_ttf.h>

#include "logging.h"

#include "cpixmap.h"
#include "ctexturesdl.h"
#include "cvideodevicesdl.h"
#include "crenderdevicesdl.h"

CRenderDeviceSDL::CRenderDeviceSDL(SDL_Renderer *render)
   : m_pSdlRenderer(render)
{
   if(m_pSdlRenderer == NULL)
   {
      LOGGER_ERROR("SDL renderer not found.");
   }
   
   if(TTF_Init() == -1)
   {
      printf("SDL True Type renderer failed to initialize: %s\n", TTF_GetError());
      exit(2);
   }
}

CRenderDeviceSDL::~CRenderDeviceSDL()
{
   TTF_Quit();
}

bool CRenderDeviceSDL::start(IPaintSurface *destSurface)
{
   LOGGER_INFO("This rendering device (CRenderDeviceSDL) is only\
                capable drawing on the framebuffer. The destination\
                surface is ignored.");
   return true;
}

void CRenderDeviceSDL::drawRect(const CRectF &rect,
                                const CColour &colour)
{
   SDL_SetRenderDrawColor(m_pSdlRenderer,
                          colour.getRed(),
                          colour.getGreen(),
                          colour.getBlue(),
                          colour.getAlpha());
   SDL_Rect sdlRect;
   
   setSdlRect(sdlRect, rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
   
   SDL_RenderFillRect(m_pSdlRenderer, &sdlRect);
}

void CRenderDeviceSDL::drawSurface(const IPaintSurface &paintSurface,
                                   const CPointF &pos,
                                   const CRectF *srcRect)
{
   const CTextureSDL *paintSurfaceSdl = dynamic_cast<const CTextureSDL *>(&paintSurface);
   
   if(paintSurfaceSdl)
   {
      SDL_Rect *sdlRectSrc = NULL;
      SDL_Rect sdlRectDest;
      
      setSdlRect(sdlRectDest,
                 pos.getX(),
                 pos.getY(),
                 paintSurface.getWidth(),
                 paintSurface.getHeight());
      
      if(srcRect)
      {
         sdlRectSrc = new SDL_Rect();
         setSdlRect(*sdlRectSrc, 
                    srcRect->getX(),
                    srcRect->getY(),
                    srcRect->getWidth(),
                    srcRect->getHeight());
         
         sdlRectDest.w = srcRect->getWidth();
         sdlRectDest.h = srcRect->getHeight();
      }
      
      if(SDL_RenderCopy(m_pSdlRenderer,
                        paintSurfaceSdl->getSDLTexture(),
                        sdlRectSrc,
                        &sdlRectDest) != 0)
      {
         LOGGER_ERROR("Unable to render texture. err=" << SDL_GetError());
      }
      
      delete sdlRectSrc;
   }
}

void CRenderDeviceSDL::drawText(const std::string &text,
                                const CRectF &rect,
                                const CColour &colour)
{
   TTF_Font *ttf = TTF_OpenFont("font.ttf", 54);
   
   if(ttf)
   {
      SDL_Color penColour;
      penColour.r = colour.getRed();
      penColour.g = colour.getGreen();
      penColour.b = colour.getBlue();
      penColour.a = colour.getAlpha();
      
      SDL_Surface *surfaceText = TTF_RenderUTF8_Solid(ttf, text.c_str(), penColour);
      if(surfaceText)
      {
         SDL_Texture *sdlTexture = SDL_CreateTextureFromSurface(m_pSdlRenderer,
                                                                surfaceText);

         if(sdlTexture)
         {
            SDL_Rect sdlRect;
            setSdlRect(sdlRect, 
                       rect.getX(),
                       rect.getY(),
                       surfaceText->w,
                       surfaceText->h);
            
            if(SDL_RenderCopy(m_pSdlRenderer,
                              sdlTexture,
                              NULL,
                              &sdlRect) != 0)
            {
               LOGGER_ERROR("Unable to render texture. err=" << SDL_GetError());
            }
            
            SDL_DestroyTexture(sdlTexture);
         }
         
         SDL_FreeSurface(surfaceText);
      }
      
      TTF_CloseFont(ttf);
   }
   else
   {
      LOGGER_ERROR("Unable to load TTF font.");
   }
}

bool CRenderDeviceSDL::end()
{
   return true;
}
