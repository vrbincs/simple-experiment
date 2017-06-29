#ifndef CRENDERDEVICESDL_H
   #define CRENDERDEVICESDL_H

#include <SDL.h>

#include <ipaintdevice.h>
#include <ccolour.h>

class IPaintSurface;

class CRenderDeviceSDL : public IPaintDevice
{
public:
   CRenderDeviceSDL(SDL_Renderer *render);
   ~CRenderDeviceSDL();
   
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
   SDL_Renderer *m_pSdlRenderer;
   
   inline void setSdlRect(SDL_Rect &sdlRect,
                          int x,
                          int y,
                          int width,
                          int height);

   inline void CColourToSDLColor(const CColour &colour, SDL_Color &sdlColor);
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

inline void CRenderDeviceSDL::CColourToSDLColor(const CColour &colour, 
                                                SDL_Color &sdlColor)
{
   sdlColor.r = colour.getRed();
   sdlColor.g = colour.getGreen();
   sdlColor.b = colour.getBlue();
   sdlColor.a = colour.getAlpha();
}

#endif //CRENDERDEVICESDL_H
