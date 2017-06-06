#ifndef CPIXELBUFFERSDL_H
   #define CPIXELBUFFERSDL_H

#include <SDL.h>

#include <cpixelbuffer.h>

class CPixelBufferSDL : public CPixelBuffer
{
public:
   CPixelBufferSDL(SDL_Surface *surface);
   CPixelBufferSDL(uint32_t width, uint32_t height, uint8_t bpp);
   ~CPixelBufferSDL();
   void *getBuffer();
   void *release();
   void lock();
   void unlock();
   SDL_Surface *getSurface();
private:
   SDL_Surface *m_sdlSurface;
};

#endif // CPIXELBUFFERSDL_H
