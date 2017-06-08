#ifndef CPAINTSURFACESDL_H
   #define CPAINTSURFACESDL_H

#include <SDL.h>

#include <ipaintsurface.h>

class CVideoDeviceSDL;

class CPaintSurfaceSDL : public IPaintSurface
{
public:
   ~CPaintSurfaceSDL();
   
   bool allocate(uint32_t width, uint32_t height, uint8_t bpp);
   
   uint8_t getBitsPerPixels() const;
   uint32_t getHeight() const;
   uint32_t getWidth() const;
   void lock();
   void unlock();
   
   SDL_Surface *getSDLSurface();
protected:
   CPaintSurfaceSDL(CVideoDeviceSDL *, SDL_Surface *surface = NULL);
   
   void freeSurface();
private:
   CPaintSurfaceSDL *m_videoDevice;
   SDL_Surface *m_sdlSurface;
   uint32_t m_width;
   uint32_t m_height;
   uint8_t m_bpp;
   
   friend class CVideoDeviceSDL;
};

#endif // CPAINTSURFACESDL_H
