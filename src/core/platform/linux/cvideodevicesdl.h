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
   
   IPaintSurface *createPaintSurface();
   IPaintDevice *createPaintDevice(IPaintSurface *paintSurface) const;
   IPaintSurface *getScreenSurface();
   
   bool start();
   bool end();
private:
   SDL_Renderer *getSDLRenderer() const;
   friend class CPaintSurfaceSDL;
};

#endif // CVIDEODEVICESDL_H
