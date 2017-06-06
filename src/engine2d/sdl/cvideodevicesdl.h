#ifndef CVIDEODEVICESDL_H
   #define CVIDEODEVICESDL_H

#include <ipaintdevice.h>
#include <ivideodevice.h>
#include <csize.h>

#include <cpixelbuffer.h>
#include <cpixelbuffersdl.h>

class CVideoDeviceSDL : public IVideoDevice
{
public:
   CVideoDeviceSDL(const CSizeI &resolution);
   ~CVideoDeviceSDL();
   
   DeviceType type() const;
   
   CPixelBuffer *allocatePixmap(uint32_t width, uint32_t height, uint8_t depth);
   IPaintDevice *getPaintDevice();
private:
   CPixelBufferSDL *m_basePixelBuffer;
   IPaintDevice *m_paintDevice;
};

#endif // CVIDEODEVICESDL_H
