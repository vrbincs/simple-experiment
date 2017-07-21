#ifndef CPAINTSURFACESDL_H
   #define CPAINTSURFACESDL_H

#include <SDL.h>

#include <ipaintsurface.h>

class CVideoDeviceSDL;

class CPaintSurfaceSDL : public IPaintSurface
{
public:
   ~CPaintSurfaceSDL();
   
   uint8_t getBitsPerPixels() const override;
   uint32_t getHeight() const override;
   uint32_t getWidth() const override;
   void lock() override;
   void unlock() override;
   bool isNull() const override;
   
   IVideoDevice *getVideoDevice() const;
   
   SDL_Surface *getSDLSurface() const;
   SDL_Texture *getSDLTexture() const;
protected:
   CPaintSurfaceSDL(CVideoDeviceSDL *videoDevice,
                    SDL_Surface *surface = NULL);
   
   void freeSurface();
private:
   CVideoDeviceSDL *m_videoDevice;
   SDL_Surface *m_sdlSurface;
   SDL_Texture *m_sdlTexture;
   uint32_t m_width;
   uint32_t m_height;
   uint8_t m_bpp;
   uint8_t *m_pixelBuffer;
   
   bool createTexture();
   bool allocateFromBuffer(uint8_t *pixelBuffer,
                           uint32_t width,
                           uint32_t height,
                           uint8_t bpp) override;
   bool allocateFromFile(const std::string &fileName,
                        const std::string &type) override;
   
   friend class CVideoDeviceSDL;
   friend class CPaintDeviceSDL;
};

#endif // CPAINTSURFACESDL_H
