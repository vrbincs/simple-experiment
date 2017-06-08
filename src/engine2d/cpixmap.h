#ifndef CPIXMAP_H
   #define CPIXMAP_H

#include <cstdint>
#include <cstddef>

#include <csize.h>

class IVideoDevice;
class IPaintSurface;

class CPixmap
{
public:
   CPixmap();
   CPixmap(int width, int height, int bpp = 32);
   CPixmap(const CSizeI &size, int bpp = 32);
   CPixmap(IPaintSurface *paintSurface);
   
   CSizeI getSize() const;
   int getWidth() const;
   int getHeight() const;
   int getBpp() const;
   
   IVideoDevice *getVideoDevice();
   
   virtual ~CPixmap();
private:
   IPaintSurface *m_paintSurface;
   bool allocatePaintSurface(int width, int height, int bpp);
   
   IPaintSurface *getPaintSurface();
   friend class CPaintTool;
};

#endif // CPIXMAP
