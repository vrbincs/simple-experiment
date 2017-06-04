#ifndef CVIDEODEVICESDL_H
   #define CVIDEODEVICESDL_H

#include <ipaintdevice.h>
#include <ivideodevice.h>
#include <csize.h>

class CVideoDeviceSDL : public IVideoDevice
{
public:
   CVideoDeviceSDL(const CSizeI &resolution);
   ~CVideoDeviceSDL();
   
   DeviceType type() const;
   
   IPaintDevice *getPaintDevice();
   IPaintDevice *createPaintDevice(const CSizeI &size);
private:
   IPaintDevice *m_paintDevice;
};

#endif // CVIDEODEVICESDL_H
