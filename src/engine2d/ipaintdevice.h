#ifndef IPAINTDEVICE_H
   #define IPAINTDEVICE_H

#include <crect.h>
#include <cpixmap.h>

class IPaintDevice
{
public:
   virtual ~IPaintDevice() {}
   
   virtual bool start(CPixmap *pixmap) = 0;
   virtual void drawRect(const CRectI &rect) = 0;
   virtual bool end() = 0;
   
   virtual IPaintSurface *createPaintSurface() const = 0;
};

#endif // IPAINTDEVICE_H
