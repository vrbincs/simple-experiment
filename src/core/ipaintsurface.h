#ifndef IPAINTSURFACE_H
   #define IPAINTSURFACE_H

#include <crect.h>

class IPaintSurface
{
public:
   virtual ~IPaintSurface() {}
   
   virtual bool allocate(uint32_t width, uint32_t height, uint8_t bpp) = 0;
   
   virtual uint8_t getBitsPerPixels() const = 0;
   virtual uint32_t getHeight() const = 0;
   virtual uint32_t getWidth() const = 0;
   virtual void lock() = 0;
   virtual void unlock() = 0;
};

#endif // IPAINTSURFACE_H
