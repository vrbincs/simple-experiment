#include "cpainttool.h"
#include "cvideodevicepseudo.h"
#include "cpaintdevicepseudo.h"
#include "cpaintsurfacepseudo.h"

static CPaintTool *l_paintTool = NULL;

CVideoDevicePseudo::CVideoDevicePseudo(const CSizeI &resolution)
   : m_resolution(resolution)
{
   l_paintTool = new CPaintTool(new CPaintDevicePseudo());
}

CVideoDevicePseudo::~CVideoDevicePseudo()
{
   delete l_paintTool;
   l_paintTool = NULL;
}

IVideoDevice::DeviceType CVideoDevicePseudo::type() const
{
   return IVideoDevice::DeviceTypePseudo;
}

IPaintSurface *CVideoDevicePseudo::createPaintSurface()
{
   return new CPaintSurfacePseudo(this);
}

IPaintDevice *CVideoDevicePseudo::createPaintDevice(IPaintSurface *paintSurface) const
{
   return NULL;
}

CPaintTool *CVideoDevicePseudo::getScreenPaintTool() const
{
   return l_paintTool;
}

bool CVideoDevicePseudo::start(const CColour *colour)
{
   return false;
}

bool CVideoDevicePseudo::end()
{
   return false;
}
