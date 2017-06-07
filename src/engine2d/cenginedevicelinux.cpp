#include <unistd.h>

#include <cstddef>

#include "logging.h"
#include "cvideodevicesdl.h"
#include "cenginedevicelinux.h"

class CEngineDeviceLinuxPriv
{
public:
   IVideoDevice *m_videoDevice;
   
   
   CEngineDeviceLinuxPriv()
      : m_videoDevice(NULL)
   {
   }
   
   virtual ~CEngineDeviceLinuxPriv()
   {
      delete m_videoDevice;
   }
   
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
   sleep(1);
   return true;
}

IVideoDevice *CEngineDeviceLinux::getVideoDevice()
{
   return m_engineDevicePriv->m_videoDevice;
}

std::list<CSizeI> CEngineDeviceLinux::getVideoModeList()
{
   return std::list<CSizeI>();
}

bool CEngineDeviceLinux::supportsRender(IVideoDevice::DeviceType renderType)
{
   switch(renderType)
   {
      case IVideoDevice::DeviceTypeSdl:
      {
         return true;
      }
      break;
      default:
      {
         return false;
      }
   }
}

bool CEngineDeviceLinux::start(IVideoDevice::DeviceType renderType, 
                               const CSizeI &resolution)
{
   m_engineDevicePriv->releaseVideoDevice();
   
   switch(renderType)
   {
      case IVideoDevice::DeviceTypeSdl:
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
