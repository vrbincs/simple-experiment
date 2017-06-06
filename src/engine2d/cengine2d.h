#ifndef CENGINE2D_H
   #define CENGINE2D_H

#include <csize.h>
#include <ienginedevice.h>
#include <ivideodevice.h>

class CEngine2d
{
public:
   virtual ~CEngine2d();
   static IEngineDevice *createDevice(IVideoDevice::DeviceType renderType,
                                      const CSizeI &resolution);

   static IEngineDevice *instance();
private:
   CEngine2d();
};

#endif // CENGINE2D_H
