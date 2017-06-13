#ifndef IVIDEODEVICE_H
   #define IVIDEODEVICE_H

#include <ipaintdevice.h>
#include <cpixmap.h>
#include <ccolour.h>

class IVideoDevice
{
public:
   enum DeviceType
   {
      DeviceTypeSdl
   };
   
   virtual ~IVideoDevice(){}
   
   virtual DeviceType type() const = 0;   
   virtual IPaintSurface *createPaintSurface() = 0;
   virtual IPaintDevice *createPaintDevice(IPaintSurface *paintSurface) const = 0;
   
   virtual IPaintDevice *getScreenPaintDevice() const = 0;

   virtual bool start(const CColour &colour = CColour(0,0,0,255)) = 0;
   virtual bool end() = 0;
};

#endif // IVIDEODEVICE_H
