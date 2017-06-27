#include <SDL.h>

#include "logging.h"

#include "cpaintsurfacesdl.h"
#include "cpaintdevicesdl.h"
#include "crenderdevicesdl.h"
#include "cvideodevicesdl.h"
#include "cpixmap.h"
#include "cpainttool.h"

static SDL_Window *l_sdlWindow = NULL;
static SDL_Renderer *l_sdlRenderer = NULL;
static CPaintTool *l_screenPaintTool = NULL;

CVideoDeviceSDL::CVideoDeviceSDL(const CSizeI &resolution)
{
   if(l_sdlWindow != NULL)
   {
      LOGGER_ERROR("SDL windows has already been initialized.");
      return;
   }
   
   l_sdlWindow = SDL_CreateWindow("simple-experiment",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  resolution.getWidth(),
                                  resolution.getHeight(),
                                  /*SDL_WINDOW_FULLSCREEN |*/ SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
         
   if(!l_sdlWindow)
   {
      LOGGER_ERROR("Unable to create SDL render window. err=" << SDL_GetError());
      return;
   }
   
   l_sdlRenderer = SDL_CreateRenderer(l_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
            
   if(!l_sdlRenderer)
   {
      LOGGER_ERROR("Failed creating SDL renderer. err=" << SDL_GetError());
      return;
   }
   
   clearRenderBuffer();
   SDL_RenderPresent(l_sdlRenderer);

   l_screenPaintTool = new CPaintTool(new CRenderDeviceSDL(l_sdlRenderer));
   if(l_screenPaintTool == NULL)
   {
      LOGGER_ERROR("Failed to create paint tool for the renderer.");
      return;
   }
   l_screenPaintTool->setClipArea(CRectI(0,0,resolution.getWidth(), resolution.getHeight()));
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
   
   if(l_screenPaintTool)
   {
      delete l_screenPaintTool;
      l_screenPaintTool = NULL;
   }
   
   SDL_Quit();
}

IVideoDevice::DeviceType CVideoDeviceSDL::type() const
{
   return DeviceTypeSdl;
}

IPaintSurface *CVideoDeviceSDL::createPaintSurface()
{
   return new CPaintSurfaceSDL(this);
}

IPaintDevice *CVideoDeviceSDL::createPaintDevice(IPaintSurface *paintSurface) const
{
   return new CPaintDeviceSDL(paintSurface);
}

CPaintTool *CVideoDeviceSDL::getScreenPaintTool() const
{
   return l_screenPaintTool;
}

bool CVideoDeviceSDL::start(const CColour *colour)
{
   if(l_screenPaintTool)
   {
      l_screenPaintTool->reset();
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
