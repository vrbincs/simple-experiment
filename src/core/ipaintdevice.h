#ifndef IPAINTDEVICE_H
   #define IPAINTDEVICE_H

#include <crect.h>
#include <cpixmap.h>

class IVideoDevice;

class IPaintDevice
{
public:
   virtual ~IPaintDevice() {}
   
   virtual bool start(IPaintSurface *destSurface) = 0;
   virtual void drawRect(const CRectI &rect) = 0;
   virtual void drawSurface(const IPaintSurface &paintSurface,
                            const CPointI &pos) = 0;
   virtual bool end() = 0;
};

#endif // IPAINTDEVICE_H
