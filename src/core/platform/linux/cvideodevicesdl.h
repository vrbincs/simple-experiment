#ifndef CVIDEODEVICESDL_H
   #define CVIDEODEVICESDL_H

#include <SDL.h>

#include <ivideodevice.h>

#include <csize.h>
#include <ccolour.h>

class CPixmap;

class CVideoDeviceSDL : public IVideoDevice
{
public:
   CVideoDeviceSDL(const CSizeI &resolution);
   ~CVideoDeviceSDL();
   
   DeviceType type() const;
   
   IPaintSurface *createPaintSurface();
   IPaintDevice *createPaintDevice(IPaintSurface *paintSurface) const;
   CPaintTool *getScreenPaintTool() const;
   SDL_Renderer *getSDLRenderer() const;
   
   bool start(const CColour &colour = CColour(0,0,0,255));
   bool end();
private:
   void clearRenderBuffer(const CColour &colour = CColour(0,0,0,255));
};

#endif // CVIDEODEVICESDL_H
