#include <SDL.h>

#include "logging.h"
#include "cpaintsurfacesdl.h"
#include "cpaintdevicesdl.h"
#include "cvideodevicesdl.h"

static CPaintSurfaceSDL *l_screenSurface = NULL;
static SDL_Window *l_sdlWindow = NULL;
static SDL_Renderer *l_sdlRenderer = NULL;

CVideoDeviceSDL::CVideoDeviceSDL(const CSizeI &resolution)
{
   if(l_screenSurface == NULL)
   {
      if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
      {
         l_sdlWindow = SDL_CreateWindow("simple-experiment",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        resolution.getWidth(),
                                        resolution.getHeight(),
                                        /*SDL_WINDOW_FULLSCREEN |*/ SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
         
         if(l_sdlWindow)
         {
            l_sdlRenderer = SDL_CreateRenderer(l_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
            
            if(l_sdlRenderer)
            {
               SDL_SetRenderDrawColor(l_sdlRenderer, 0, 255, 0, 255);
               SDL_RenderClear(l_sdlRenderer);
               SDL_RenderPresent(l_sdlRenderer);
            }
            else
            {
               LOGGER_ERROR("Failed creating SDL renderer. err=" << SDL_GetError());
            }
         }
         else
         {
            LOGGER_ERROR("Unable to create SDL render window. err=" << SDL_GetError());
         }
      }
      else
      {
         LOGGER_ERROR("Unable to initialize SDL. err=" << SDL_GetError());
      }
   }
   else
   {
      LOGGER_ERROR("SDL screen has already been initialized.");
   }
}

CVideoDeviceSDL::~CVideoDeviceSDL()
{
   delete l_screenSurface;
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

IPaintSurface *CVideoDeviceSDL::getScreenSurface()
{
   return NULL;
}

bool CVideoDeviceSDL::start()
{
   return false;
}

bool CVideoDeviceSDL::end()
{
   if(l_screenSurface)
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
