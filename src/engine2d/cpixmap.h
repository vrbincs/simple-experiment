#ifndef CPIXMAP_H
   #define CPIXMAP_H

class <csize.h>

class CPixmap
{
public:
   CPixmap(int width, int height, int bpp = 32);
   CPixmap(const CSizeI &size, int bpp = 32);
   
   void *getBuffer();
   
   CSizeI getSize() const;
   int getWidth() const;
   int getHeight() const;
   int getBpp() const;
   
   virtual ~CPixmap();
private:
   CSizeI m_size;
   int m_bitsPerPixel;
   uint8_t *m_pPixelBuffer;
   
   bool allocateBuffer();
};

#endif // CPIXMAP
