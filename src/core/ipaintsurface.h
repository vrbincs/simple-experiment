#ifndef IPAINTSURFACE_H
   #define IPAINTSURFACE_H

#include <string>
#include <crect.h>

class CPixmap;
class IVideoDevice;

class IPaintSurface
{
public:
   virtual ~IPaintSurface() {}   
   virtual uint8_t getBitsPerPixels() const = 0;
   virtual uint32_t getHeight() const = 0;
   virtual uint32_t getWidth() const = 0;
   virtual void lock() = 0;
   virtual void unlock() = 0;
   virtual IVideoDevice *getVideoDevice() const = 0;
private:
   virtual bool allocateFromBuffer(uint8_t *pixelBuffer,
                                   uint32_t width,
                                   uint32_t height,
                                   uint8_t bpp) = 0;
   virtual bool allocateFromFile(const std::string &fileName,
                                 const std::string &type) = 0;
   friend class CPixmap;
};

#endif // IPAINTSURFACE_H
