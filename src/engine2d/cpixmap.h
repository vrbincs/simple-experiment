#ifndef CPIXMAP_H
   #define CPIXMAP_H

#include <cstdint>
#include <cstddef>

#include <csize.h>
#include <cpixelbuffer.h>

class CPixmap
{
public:
   CPixmap(int width, int height, int bpp = 32);
   CPixmap(const CSizeI &size, int bpp = 32);
   
   const void *getBuffer();
   
   CSizeI getSize() const;
   int getWidth() const;
   int getHeight() const;
   int getBpp() const;
   CPixelBuffer *getPixelBuffer();
   
   virtual ~CPixmap();
private:
   CSizeI m_size;
   int m_bitsPerPixel;
   CPixelBuffer *m_pixelBuffer;
   
   bool allocateBuffer();
};

#endif // CPIXMAP
