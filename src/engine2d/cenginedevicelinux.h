#ifndef CENGINEDEVICESDL_H
   #define CENGINEDEVICESDL_H

#include <ienginedevice.h>

class CEngineDeviceLinuxPriv;

class CEngineDeviceLinux : public IEngineDevice
{
public:
   CEngineDeviceLinux();
   virtual ~CEngineDeviceLinux();
   
   IVideoDevice *getVideoDevice();
   std::list<CSizeI> getVideoModeList();
private:
   CEngineDeviceLinuxPriv *m_engineDevicePriv;
};

#endif
