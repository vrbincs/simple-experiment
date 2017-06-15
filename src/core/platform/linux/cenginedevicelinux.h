#ifndef CENGINEDEVICESDL_H
   #define CENGINEDEVICESDL_H

#include <ienginedevice.h>

class CEngineDeviceLinuxPriv;

class CEngineDeviceLinux : public IEngineDevice
{
public:
   CEngineDeviceLinux();
   virtual ~CEngineDeviceLinux();
   
   bool run();
   IVideoDevice *getVideoDevice();
   
   bool setRenderer(IVideoDevice::DeviceType renderType,
                    const CSizeI &resolution);
private:
   IVideoDevice *m_videoDevice;
   void releaseVideoDevice();
   
   friend class IEngineDevice;
};

#endif
