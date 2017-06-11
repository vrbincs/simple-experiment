#include <cstddef>

#include "logging.h"
#include "cengine2d.h"

static IEngineDevice *l_engineDevice = CEngine2d::instance();

CEngine2d::~CEngine2d()
{
}

IEngineDevice *CEngine2d::createDevice(IVideoDevice::DeviceType renderType,
                                       const CSizeI &resolution)
{
   if(l_engineDevice)
   {
      if(!l_engineDevice->setRenderer(renderType, resolution))
      {
         LOGGER_WARN("The render type not supported on your engine device.");
      }
   }
   else
   {
      LOGGER_WARN("Engine device is not available.");
   }
   
   return l_engineDevice;
}

IEngineDevice *CEngine2d::instance()
{
   if(l_engineDevice == NULL)
   {
      l_engineDevice = IEngineDevice::instance();
   }
   
   return l_engineDevice;
}


CEngine2d::CEngine2d()
{
}

bool registerEngineDevice(IEngineDevice *engineDevice)
{
   if(l_engineDevice == NULL)
   {
      l_engineDevice = engineDevice;
      return true;
   }
   else
   {
      LOGGER_ERROR("There can only be one engine device!");
      return false;
   }
}
