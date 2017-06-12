#include <SDL.h>

#include "logging.h"
#include "cpaintsurfacesdl.h"
#include "cpaintdevicesdl.h"
#include "cvideodevicesdl.h"

static SDL_Window *l_sdlWindow = NULL;
static SDL_Renderer *l_sdlRenderer = NULL;
static CPaintSurfaceSDL *l_sdlPaintSurface = NULL;
static CPaintDeviceSDL *l_sdlPaintDevice = NULL;

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
   
   
   SDL_SetRenderDrawColor(l_sdlRenderer, 0, 0, 0, 255);
   SDL_RenderClear(l_sdlRenderer);
   SDL_RenderPresent(l_sdlRenderer);
   
   l_sdlPaintSurface = dynamic_cast<CPaintSurfaceSDL *>(createPaintSurface());
   
   if(!(l_sdlPaintSurface && l_sdlPaintSurface->allocate(resolution.getWidth(),
                                                         resolution.getHeight(),
                                                         32)))
   {
      LOGGER_ERROR("Failed to create paint surface.");
      return;
   }
   
   l_sdlPaintDevice = dynamic_cast<CPaintDeviceSDL *>(createPaintDevice(l_sdlPaintSurface));
   
   if(!l_sdlPaintDevice)
   {
      LOGGER_ERROR("Failed to create screen paint device.");
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

IPaintDevice *CVideoDeviceSDL::getScreenPaintDevice() const
{
   return l_sdlPaintDevice;
}

bool CVideoDeviceSDL::start()
{
   if(l_sdlRenderer)
   {
      SDL_SetRenderDrawColor(l_sdlRenderer, 0, 0, 0, 255);
      SDL_RenderClear(l_sdlRenderer);
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
