#ifndef IVIDEODEVICE_H
   #define IVIDEODEVICE_H

#include <ipaintdevice.h>
#include <cpixmap.h>

class IVideoDevice
{
public:
   enum DeviceType
   {
      DeviceTypeSdl
   };
   
   virtual ~IVideoDevice(){}
   
   virtual DeviceType type() const = 0;   
   virtual IPaintSurface *createPaintSurface() const = 0;
   virtual IPaintDevice *createPaintDevice(IPaintSurface *paintSurface) const = 0;
   virtual IPaintDevice *getPaintDevice() = 0;

   virtual bool start() = 0;
   virtual bool end() = 0;
};

#endif // IVIDEODEVICE_H
