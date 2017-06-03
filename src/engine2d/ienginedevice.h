#ifndef IENGINEDEVICE_H
   #define IENGINEDEVICE_H

#include <list>
#include <csize.h>
#include <ivideodevice.h>

class IVideoDevice;

class IEngineDevice
{
public:
   virtual ~IEngineDevice(){}
   
   virtual bool run() = 0;
   virtual IVideoDevice *getVideoDevice() = 0;
   virtual std::list<CSizeI> getVideoModeList() = 0;
   virtual bool supportsRender(IVideoDevice::DeviceType renderType) = 0;
private:
   virtual bool start(IVideoDevice::DeviceType renderType,
                      const CSizeI &resolution) = 0;
   static IEngineDevice *instance();
   
   friend class CEngine2d;
};

#endif // IENGINEDEVICE_H
