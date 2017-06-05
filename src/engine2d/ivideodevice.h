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
   
   virtual IPaintDevice *getPaintDevice() = 0;
   virtual IPaintDevice *createPaintDevice(CPixmap *pixmap) = 0;
   
   /**
    * \brief Draw image on the device
    */
   //virtual void drawImage() = 0;
};

#endif // IVIDEODEVICE_H
