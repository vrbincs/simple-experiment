#ifndef CVIDEODEVICESDL_H
   #define CVIDEODEVICESDL_H

#include <SDL.h>

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
   IPaintDevice *createPaintDevice(IPaintDevice *) const;
   IPaintDevice *getPaintDevice();
   
   bool start();
   bool end();
private:
   CPaintSurfaceSDL *m_basePaintSurface;
   SDL_Window *m_window;
   SDL_Renderer *m_renderer;
};

#endif // CVIDEODEVICESDL_H
