#include <SDL.h>

#include "logging.h"

#include "ctexturesdl.h"
#include "cpaintdevicesdl.h"
#include "crenderdevicesdl.h"
#include "cvideodevicesdl.h"
#include "cpixmap.h"
#include "cpainttool.h"

static SDL_Window *l_sdlWindow = NULL;
static SDL_Renderer *l_sdlRenderer = NULL;
static CPaintTool *l_windowPainter = NULL;

CVideoDeviceSDL::CVideoDeviceSDL(const CSizeI &resolution)
{
   if(l_sdlWindow != NULL)
   {
      LOGGER_ERROR("SDL windows has already been initialized.");
      return;
   }
   
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
   
   uint32_t windowFlags = (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
   if(resolution.isZero())
   {
      windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
   }
   
   l_sdlWindow = SDL_CreateWindow("simple-experiment",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  resolution.getWidth(),
                                  resolution.getHeight(),
                                  windowFlags);
         
   if(!l_sdlWindow)
   {
      LOGGER_ERROR("Unable to create SDL render window. err=" << SDL_GetError());
      return;
   }
   
   l_sdlRenderer = SDL_CreateRenderer(l_sdlWindow, 
                                      -1,
                                      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

   // This call will enable SDL to syncronize frame rate with the frequency
   // of the monitor. There are two effects of this:
   // - remedy tearing
   // - fixed refresh rate
   if(SDL_GL_SetSwapInterval(1) != 0)
   {
      LOGGER_ERROR("Unable to set SWAP interval.");
   }
   
   if(!l_sdlRenderer)
   {
      LOGGER_ERROR("Failed creating SDL renderer. err=" << SDL_GetError());
      return;
   }
   
   clearRenderBuffer();
   SDL_RenderPresent(l_sdlRenderer);

   SDL_DisplayMode mode;
   SDL_GetCurrentDisplayMode(0, &mode);
   
   l_windowPainter = new CPaintTool(new CRenderDeviceSDL(l_sdlRenderer));
   if(l_windowPainter == NULL)
   {
      LOGGER_ERROR("Failed to create paint tool for the renderer.");
      return;
   }
   
   l_windowPainter->setClipArea(CRectF(0,0,mode.w, mode.h));
}

CVideoDeviceSDL::~CVideoDeviceSDL()
{
   if(l_sdlRenderer)
   {
      SDL_DestroyRenderer(l_sdlRenderer);
      l_sdlRenderer = NULL;
   }
   
   if(l_sdlWindow)
   {
      SDL_DestroyWindow(l_sdlWindow);
      l_sdlWindow = NULL;
   }
   
   if(l_windowPainter)
   {
      delete l_windowPainter;
      l_windowPainter = NULL;
   }
   
   SDL_Quit();
}

IVideoDevice::DeviceType CVideoDeviceSDL::type() const
{
   return DeviceTypeSdl;
}

IPaintSurface *CVideoDeviceSDL::createPaintSurface()
{
   return new CTextureSDL(this);
}

IPaintDevice *CVideoDeviceSDL::createPaintDevice(IPaintSurface *paintSurface) const
{
   return new CPaintDeviceSDL(paintSurface);
}

CPaintTool *CVideoDeviceSDL::getScreenPaintTool() const
{
   return l_windowPainter;
}

bool CVideoDeviceSDL::start(const CColour *colour)
{
   if(l_windowPainter)
   {
      l_windowPainter->save();
   }
   
   if(l_sdlRenderer && colour)
   {
      clearRenderBuffer(*colour);
   }
   return false;
}

bool CVideoDeviceSDL::end()
{
   if(l_sdlRenderer)
   {
      SDL_RenderPresent(l_sdlRenderer);
      
      l_windowPainter->restore();
      return true;
   }
   else
   {
      return false;
   }
}

SDL_Renderer *CVideoDeviceSDL::getSDLRenderer() const
{
   return l_sdlRenderer;
}

void CVideoDeviceSDL::clearRenderBuffer(const CColour &colour)
{
   if(l_sdlRenderer)
   {
      SDL_SetRenderDrawColor(l_sdlRenderer, 
                             colour.getRed(),
                             colour.getGreen(),
                             colour.getBlue(),
                             colour.getAlpha());
      SDL_RenderClear(l_sdlRenderer);
   }
}
