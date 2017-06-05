#ifndef IPAINTDEVICE_H
   #define IPAINTDEVICE_H

#include <crect.h>

class IPaintDevice
{
public:
   virtual ~IPaintDevice() {}
   
   virtual int getHeight() const = 0;
   virtual int getWidth() const = 0;
   
   virtual void drawRect(const CRectI &rect) = 0;
};

#endif // IPAINTDEVICE_H
