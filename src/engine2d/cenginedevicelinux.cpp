#include <cstddef>

#include "cenginedevicelinux.h"

class CEngineDeviceLinuxPriv
{
   virtual ~CEngineDeviceLinuxPriv(){}
protected:
   CEngineDeviceLinuxPriv(){}
   
   friend class CEngineDeviceLinux;
};

CEngineDeviceLinux::CEngineDeviceLinux()
   : m_engineDevicePriv(new CEngineDeviceLinuxPriv())
{
}

CEngineDeviceLinux::~CEngineDeviceLinux()
{
}

IVideoDevice *CEngineDeviceLinux::getVideoDevice()
{
   return NULL;
}

std::list<CSizeI> CEngineDeviceLinux::getVideoModeList()
{
   return std::list<CSizeI>();
}
