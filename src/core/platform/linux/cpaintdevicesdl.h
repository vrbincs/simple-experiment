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
   bool end();
private:
   CPaintSurfaceSDL *m_pDestSurface;
   SDL_Renderer *m_pSdlRenderer;
};

#endif //CPAINTDEVICESDL_H
