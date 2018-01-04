#ifndef CVIDEODEVICESDL_H
   #define CVIDEODEVICESDL_H

#include <map>
#include <SDL.h>

#include <ivideodevice.h>

#include <csize.h>
#include <ccolour.h>

class CPixmap;

class CVideoDeviceSDL : public IVideoDevice
{
public:
   ~CVideoDeviceSDL();
   
   DeviceType type() const;
   
   IPaintSurface *createPaintSurface();
   IPaintDevice *createPaintDevice(IPaintSurface *paintSurface) const;
   CPaintTool *getScreenPaintTool() const;
   SDL_Renderer *getSDLRenderer() const;
   
   bool start(const CColour *colour = NULL);
   bool end();
   
   static CVideoDeviceSDL *create(const CSizeI &resolution,
                                  const std::map<std::string, std::string> &params = std::map<std::string, std::string>(),
                                  bool *ok = NULL); 
private:
   CVideoDeviceSDL(const CSizeI &resolution,
                   const std::map<std::string, std::string> &params,
                   bool &ok);

   void clearRenderBuffer(const CColour &colour = CColour(0,0,0,255));
};

#endif // CVIDEODEVICESDL_H
