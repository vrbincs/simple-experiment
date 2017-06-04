#ifndef IPAINTDEVICE_H
   #define IPAINTDEVICE_H

#include <cpixmap.h>

class IPaintDevice
{
public:
   virtual ~IPaintDevice() {}
   
   virtual int height() const = 0;
};

#endif // IPAINTDEVICE_H
