#ifndef CTEXTURESDL_H
   #define CTEXTURESDL_H

#include <SDL.h>

#include <ipaintsurface.h>

class CVideoDeviceSDL;

class CTextureSDL : public IPaintSurface
{
public:
   ~CTextureSDL();
   
   uint8_t getBitsPerPixels() const override;
   uint32_t getHeight() const override;
   uint32_t getWidth() const override;
   void lock() override;
   void unlock() override;
   bool isNull() const override;
   
   IVideoDevice *getVideoDevice() const override;
   
   SDL_Texture *getSDLTexture() const;
   CColour getPixelAt(const CPointI &pos) const override;
protected:
   CTextureSDL(CVideoDeviceSDL *videoDevice,
                    SDL_Surface *surface = NULL);
   
   void freeSurface();
private:
   CVideoDeviceSDL *m_videoDevice;
   SDL_Texture *m_sdlTexture;
   uint32_t m_width;
   uint32_t m_height;
   uint8_t m_bpp;
   
   bool convertSurfaceToTexture(SDL_Surface *surface);
   bool allocateFromBuffer(uint8_t *pixelBuffer,
                           uint32_t width,
                           uint32_t height,
                           uint8_t bpp) override;
   bool allocateFromFile(const std::string &fileName,
                        const std::string &type) override;
   
   friend class CVideoDeviceSDL;
   friend class CPaintDeviceSDL;
};

#endif // CTEXTURESDL_H
