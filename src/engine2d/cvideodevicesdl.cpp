#include "cvideodevicesdl.h"

CVideoDeviceSDL::CVideoDeviceSDL(const CSizeI &resolution)
   : m_resolution(resolution)
{
}

CVideoDeviceSDL::~CVideoDeviceSDL()
{
}

IVideoDevice::DeviceType CVideoDeviceSDL::type() const
{
   return DeviceTypeSdl;
}
