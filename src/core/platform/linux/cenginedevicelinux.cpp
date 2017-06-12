#include <unistd.h>

#include <cstddef>

#include "logging.h"
#include "cvideodevicesdl.h"
#include "cenginedevicelinux.h"

static IEngineDevice *l_engineDeviceInstance = NULL;

CEngineDeviceLinux::CEngineDeviceLinux()
   : m_videoDevice(NULL)
{
}

CEngineDeviceLinux::~CEngineDeviceLinux()
{
   releaseVideoDevice();
}

bool CEngineDeviceLinux::run()
{
   usleep(100000);
   return true;
}

IVideoDevice *CEngineDeviceLinux::getVideoDevice()
{
   return m_videoDevice;
}

std::list<CSizeI> CEngineDeviceLinux::getVideoModeList()
{
   return std::list<CSizeI>();
}

bool CEngineDeviceLinux::setRenderer(IVideoDevice::DeviceType renderType,
                                     const CSizeI &resolution)
{
   releaseVideoDevice();
   
   switch(renderType)
   {
      case IVideoDevice::DeviceTypeSdl:
      {
         m_videoDevice = new CVideoDeviceSDL(resolution);
         return true;
      }
      break;
      default:
      break;
   }
   
   return false;
}

IEngineDevice *IEngineDevice::instance()
{
   if(l_engineDeviceInstance == NULL)
   {
      l_engineDeviceInstance = new CEngineDeviceLinux();
   }
   
   return l_engineDeviceInstance;
}

void CEngineDeviceLinux::releaseVideoDevice()
{
   if(m_videoDevice)
   {
      delete m_videoDevice;
      m_videoDevice = NULL;
   }
}
