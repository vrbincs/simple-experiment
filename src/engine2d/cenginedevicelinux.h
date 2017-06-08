#ifndef CENGINEDEVICESDL_H
   #define CENGINEDEVICESDL_H

#include <ienginedevice.h>

class CEngineDeviceLinuxPriv;

class CEngineDeviceLinux : public IEngineDevice
{
public:
   virtual ~CEngineDeviceLinux();
   
   bool run();
   IVideoDevice *getVideoDevice();
   std::list<CSizeI> getVideoModeList();
   
   bool setRenderer(IVideoDevice::DeviceType renderType,
                    const CSizeI &resolution);
private:
   IVideoDevice *m_videoDevice;
   
   CEngineDeviceLinux();
   void releaseVideoDevice();
   
   friend class IEngineDevice;
};

#endif
