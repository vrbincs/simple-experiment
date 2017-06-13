#ifndef CVIDEODEVICESDL_H
   #define CVIDEODEVICESDL_H

#include <ipaintdevice.h>
#include <ivideodevice.h>
#include <csize.h>

#include <ipaintsurface.h>
#include <cpaintsurfacesdl.h>
#include <ccolour.h>

class CPaintDeviceSDL;

class CVideoDeviceSDL : public IVideoDevice
{
public:
   CVideoDeviceSDL(const CSizeI &resolution);
   ~CVideoDeviceSDL();
   
   DeviceType type() const;
   
   IPaintSurface *createPaintSurface();
   IPaintDevice *createPaintDevice(IPaintSurface *paintSurface) const;
   IPaintDevice *getScreenPaintDevice() const;
   
   bool start(const CColour &colour = CColour(0,0,0,255));
   bool end();
private:
   SDL_Renderer *getSDLRenderer() const;
   friend class CPaintSurfaceSDL;
   friend class CPaintDeviceSDL;
};

#endif // CVIDEODEVICESDL_H
