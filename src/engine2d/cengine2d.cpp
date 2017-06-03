#include <cstddef>

#include "cengine2d.h"
#include "cenginedevicelinux.h"

static IEngineDevice *engineDevice = NULL;

CEngine2d::~CEngine2d()
{
   releaseDevice();
}

IEngineDevice *CEngine2d::createDevice(IVideoDevice::DeviceType renderType,
                                       const CSizeI &resolution)
{
   return engineDevice;
}

void CEngine2d::releaseDevice()
{
   if(engineDevice)
   {
      delete engineDevice;
   }
}

CEngine2d::CEngine2d()
{
}
