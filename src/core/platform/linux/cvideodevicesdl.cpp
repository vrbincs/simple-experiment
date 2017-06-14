#include <SDL.h>

#include "logging.h"
#include "cpaintsurfacesdl.h"
#include "cpaintdevicesdl.h"
#include "cvideodevicesdl.h"
#include "ccolour.h"

static SDL_Window *l_sdlWindow = NULL;
static SDL_Renderer *l_sdlRenderer = NULL;
static CPaintSurfaceSDL *l_sdlPaintSurface = NULL;

CVideoDeviceSDL::CVideoDeviceSDL(const CSizeI &resolution)
{
   if(l_sdlWindow != NULL)
   {
      LOGGER_ERROR("SDL windows has already been initialized.");
      return;
   }
   
   if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
   {
      LOGGER_ERROR("Unable to initialize SDL. err=" << SDL_GetError());
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
   
   l_sdlPaintSurface = new CPaintSurfaceSDL(this, SDL_GetWindowSurface(l_sdlWindow));
   if(!l_sdlPaintSurface)
   {
      LOGGER_ERROR("Failed to create paint surface.");
      return;
   }
}

CVideoDeviceSDL::~CVideoDeviceSDL()
{
   if(l_sdlRenderer)
   {
      SDL_DestroyRenderer(l_sdlRenderer);
   }
   
   if(l_sdlWindow)
   {
      SDL_DestroyWindow(l_sdlWindow);
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

IPaintSurface *CVideoDeviceSDL::getScreenSurface() const
{
   return l_sdlPaintSurface;
}

bool CVideoDeviceSDL::start(const CColour &colour)
{
   if(l_sdlRenderer)
   {
      clearRenderBuffer(colour);
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
