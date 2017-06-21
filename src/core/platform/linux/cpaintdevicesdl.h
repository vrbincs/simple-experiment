#ifndef CPAINTDEVICESDL_H
   #define CPAINTDEVICESDL_H

#include <SDL.h>

#include <ipaintdevice.h>

class IPaintSurface;

class CPaintDeviceSDL : public IPaintDevice
{
public:
   CPaintDeviceSDL(IPaintSurface *destSurface);
   ~CPaintDeviceSDL();
   
   bool start(IPaintSurface *destSurface);
   void drawRect(const CRectI &rect);
   void drawSurface(const IPaintSurface &paintSurface,
                    const CPointI &pos,
                    const CRectI *srcRect);
   void drawText(const std::string &text,
                 const CRectI &rect,
                 const CColour &colour);
   
   bool end();
private:
   CPaintSurfaceSDL *m_pDestSurface;
   SDL_Renderer *m_pSdlRenderer;
   
   inline void setSdlRect(SDL_Rect &sdlRect,
                          int x,
                          int y,
                          int width,
                          int height);
};


inline void CPaintDeviceSDL::setSdlRect(SDL_Rect &sdlRect,
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

#endif //CPAINTDEVICESDL_H
