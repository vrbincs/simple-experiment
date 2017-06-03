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
   bool supportsRender(IVideoDevice::DeviceType renderType);

private:
   bool start(IVideoDevice::DeviceType renderType, const CSizeI &resolution);
   IEngineDevice *instance();
   
   CEngineDeviceLinux();
   CEngineDeviceLinuxPriv *m_engineDevicePriv;
   friend class CEngineDeviceLinuxPriv;
};

#endif
