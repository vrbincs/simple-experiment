#ifndef CPAINTDEVICESDL_H
   #define CPAINTDEVICESDL_H

#include <SDL.h>

#include <ipaintdevice.h>

class Pixmap;

class CPaintSurfaceSDL : public IPaintDevice
{
public:
   int getHeight() const;
   int getWidth() const;
private:
   SDL_Surface *m_pSurface;
   
   CPaintDeviceSDL(SDL_Surface *pSurface);
   CPaintDeviceSDL(CPixmap *pixmap);
   
   friend class CVideoDeviceSDL;
};

#endif //CPAINTDEVICESDL_H
