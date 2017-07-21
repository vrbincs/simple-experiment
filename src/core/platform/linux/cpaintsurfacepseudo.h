#ifndef CPAINTSURFACEPSEUDO_H
   #define CPAINTSURFACEPSEUDO_H

#include <ipaintsurface.h>

class IVideoDevice;
class CVideoDevicePseudo;

class CPaintSurfacePseudo : public IPaintSurface
{
public:
   CPaintSurfacePseudo(CVideoDevicePseudo *videoDevice = NULL);
   
   uint8_t getBitsPerPixels() const override;
   uint32_t getHeight() const override;
   uint32_t getWidth() const override;
   void lock() override;
   void unlock() override;
   bool isNull() const override;
private:
   IVideoDevice *getVideoDevice() const override;
   bool allocateFromBuffer(uint8_t *pixelBuffer,
                                   uint32_t width,
                                   uint32_t height,
                                   uint8_t depth) override;
                                   
   bool allocateFromFile(const std::string &fileName,
                         const std::string &type) override;

   uint8_t m_bpp;
   uint32_t m_width;
   uint32_t m_height;
   CVideoDevicePseudo *m_videoDevice;
   uint8_t *m_pixelBuffer;
};

#endif // CPAINTSURFACEPSEUDO_H
