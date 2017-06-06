#ifndef IPAINTSURFACE_H
   #define IPAINTSURFACE_H

#include <crect.h>

class IPaintSurface
{
public:
   virtual ~IPaintSurface() {}
   
   virtual int getHeight() const = 0;
   virtual int getWidth() const = 0;
};

#endif // IPAINTSURFACE_H
