#include <cstddef>

#include "cvideodevicesdl.h"
#include "cenginedevicelinux.h"

class CEngineDeviceLinuxPriv
{
public:
   virtual ~CEngineDeviceLinuxPriv(){}
   
   static CEngineDeviceLinux *createInstance()
   {
      return new CEngineDeviceLinux();
   }
   
   
   void releaseVideoDevice()
   {
      if(m_videoDevice)
      {
         delete m_videoDevice;
         m_videoDevice = NULL;
      }
   }
   
   bool createSDLDevice(const CSizeI &resolution)
   {
      m_videoDevice = new CVideoDeviceSDL(resolution);
      return m_videoDevice;
   }
protected:
   CEngineDeviceLinuxPriv()
      : m_videoDevice(NULL)
   {}
   friend class CEngineDeviceLinux;
   IVideoDevice *m_videoDevice;
};

static IEngineDevice *l_engineDeviceInstance = CEngineDeviceLinuxPriv::createInstance();

CEngineDeviceLinux::CEngineDeviceLinux()
   : m_engineDevicePriv(new CEngineDeviceLinuxPriv())
{
}

CEngineDeviceLinux::~CEngineDeviceLinux()
{
}

bool CEngineDeviceLinux::run()
{
   return false;
}

IVideoDevice *CEngineDeviceLinux::getVideoDevice()
{
   return NULL;
}

std::list<CSizeI> CEngineDeviceLinux::getVideoModeList()
{
   return std::list<CSizeI>();
}

bool CEngineDeviceLinux::supportsRender(IVideoDevice::DeviceType renderType)
{
   switch(renderType)
   {
      default:
         return false;
   }
}

bool CEngineDeviceLinux::start(IVideoDevice::DeviceType renderType, 
                               const CSizeI &resolution)
{
   m_engineDevicePriv->releaseVideoDevice();
   
   switch(renderType)
   {
      DeviceTypeSdl:
      {
         return m_engineDevicePriv->createSDLDevice(resolution);
      }
      break;
      default:
      break;
   }
   return false;
}

IEngineDevice *IEngineDevice::instance()
{
   return l_engineDeviceInstance;
}
