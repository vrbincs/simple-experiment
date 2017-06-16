#ifndef CRENDERDEVICESDL_H
   #define CRENDERDEVICESDL_H

#include <SDL.h>

#include <ipaintdevice.h>

class IPaintSurface;

class CRenderDeviceSDL : public IPaintDevice
{
public:
   CRenderDeviceSDL(SDL_Renderer *render);
   ~CRenderDeviceSDL();
   
   bool start(IPaintSurface *destSurface);
   void drawRect(const CRectI &rect);
   void drawSurface(const IPaintSurface &paintSurface,
                    const CPointI &pos);
   bool end();
private:
   SDL_Renderer *m_pSdlRenderer;
   
   inline void setSdlRect(SDL_Rect &sdlRect,
                          int x,
                          int y,
                          int width,
                          int height);
};


inline void CRenderDeviceSDL::setSdlRect(SDL_Rect &sdlRect,
                                        int x,
                                        int y,
                                        int width,
                                        int height)
{
   sdlRect.x = x;
   sdlRect.y = y;
   sdlRect.w = width;
   sdlRect.h = height;
}

#endif //CRENDERDEVICESDL_H
