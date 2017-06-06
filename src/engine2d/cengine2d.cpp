#include <cstddef>

#include "logging.h"
#include "cengine2d.h"
#include "cenginedevicelinux.h"

static IEngineDevice *l_activeEngineDevice = NULL;

CEngine2d::~CEngine2d()
{
}

IEngineDevice *CEngine2d::createDevice(IVideoDevice::DeviceType renderType,
                                       const CSizeI &resolution)
{
   IEngineDevice *device = IEngineDevice::instance();
   
   if(device)
   {
      if(device->supportsRender(renderType))
      {
         if(device->start(renderType, resolution))
         {
            l_activeEngineDevice = device;
         }
         else
         {
            LOGGER_ERROR("Unable to start the engine.");
         }
      }
      else
      {
         LOGGER_WARN("The render type not supported on your engine device.");
      }
   }
   else
   {
      LOGGER_WARN("Engine device not available.");
   }
   
   return l_activeEngineDevice;
}

IEngineDevice *CEngine2d::instance()
{
   return l_activeEngineDevice;
}


CEngine2d::CEngine2d()
{
}

void registerEngineDevice(IEngineDevice *engineDevice)
{
}
