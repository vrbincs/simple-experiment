#ifndef CVIDEODEVICESDL_H
   #define CVIDEODEVICESDL_H

#include <ipaintdevice.h>
#include <ivideodevice.h>
#include <csize.h>

#include <ipaintsurface.h>
#include <cpaintsurfacesdl.h>

class CVideoDeviceSDL : public IVideoDevice
{
public:
   CVideoDeviceSDL(const CSizeI &resolution);
   ~CVideoDeviceSDL();
   
   DeviceType type() const;
   
   IPaintSurface *createPaintSurface() const;
   IPaintDevice *createPaintDevice(IPaintSurface *paintSurface) const;
   IPaintDevice *getPaintDevice();
   
   bool start();
   bool end();
};

#endif // CVIDEODEVICESDL_H
