#ifndef CPAINTDEVICESDL_H
   #define CPAINTDEVICESDL_H

#include <SDL.h>

#include <ipaintdevice.h>

class IPaintSurface;
class CTextureSDL;

class CPaintDeviceSDL : public IPaintDevice
{
public:
   CPaintDeviceSDL(IPaintSurface *destSurface);
   ~CPaintDeviceSDL();
   
   bool start(IPaintSurface *destSurface);
   void drawRect(const CRectF &rect,
                 const CColour &colour);
   void drawSurface(const IPaintSurface &paintSurface,
                    const CPointF &pos,
                    const CRectF *srcRect);
   void drawText(const std::string &text,
                 const CRectF &rect,
                 const CColour &colour);
   
   bool end();
private:
   CTextureSDL *m_pDestSurface;
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
