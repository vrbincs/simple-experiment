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
   
   virtual CPixelBuffer *allocatePixmap(uint32_t width, 
                                        uint32_t height,
                                        uint8_t depth) = 0;

   virtual IPaintDevice *getPaintDevice() = 0;
};

#endif // IVIDEODEVICE_H
