#include "cvideodevicepseudo.h"

CVideoDevicePseudo::CVideoDevicePseudo(const CSizeI &resolution)
   : m_resolution(resolution)
{
   
}

IVideoDevice::DeviceType CVideoDevicePseudo::type() const
{
   return IVideoDevice::DeviceTypePseudo;
}

IPaintSurface *CVideoDevicePseudo::createPaintSurface()
{
   return NULL;
}

IPaintDevice *CVideoDevicePseudo::createPaintDevice(IPaintSurface *paintSurface) const
{
   return NULL;
}

CPaintTool *CVideoDevicePseudo::getScreenPaintTool() const
{
   return NULL;
}

bool CVideoDevicePseudo::start(const CColour *colour)
{
   return false;
}

bool CVideoDevicePseudo::end()
{
   return false;
}
