#ifndef CVIDEODEVICESDL_H
   #define CVIDEODEVICESDL_H

#include <ivideodevice.h>
#include <csize.h>

class CVideoDeviceSDL : public IVideoDevice
{
public:
   CVideoDeviceSDL(const CSizeI &resolution);
   ~CVideoDeviceSDL();
   
   DeviceType type() const;
private:
   CSizeI m_resolution;
};

#endif // CVIDEODEVICESDL_H
