#ifndef CPIXMAP_H
   #define CPIXMAP_H

#include <cstdint>
#include <cstddef>
#include <string>

#include <csize.h>
#include <cpoint.h>
#include <ccolour.h>

class IVideoDevice;
class IPaintSurface;

class CPixmap
{
public:
   CPixmap();
   CPixmap(uint8_t *pixelBuffer, int width, int height, int bpp = 32);
   CPixmap(uint8_t *pixelBuffer, const CSizeI &size, int bpp = 32);
   CPixmap(IPaintSurface *paintSurface);
   CPixmap(const std::string &fileName, const std::string &fileType);
   
   virtual ~CPixmap();
   
   CSizeI getSize() const;
   int getWidth() const;
   int getHeight() const;
   int getBpp() const;
   
   bool isNull() const;
   
   CColour getPixelAt(const CPointI &pos);
private:
   IPaintSurface *m_paintSurface;
   
   void free();
   bool allocatePaintSurface(uint8_t *pixelBuffer, 
                             int width,
                             int height,
                             int bpp);
   
   IPaintSurface *getPaintSurface() const;
   
   friend class CPaintTool;
};

#endif // CPIXMAP
