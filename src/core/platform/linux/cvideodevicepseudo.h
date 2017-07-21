#ifndef CVIDEODEVICEPSEUDO_H
   #define CVIDEODEVICEPSEUDO_H

#include <cstddef>

#include <ivideodevice.h>
#include <csize.h>

class IPaintSurface;
class IPaintDevice;
class CPaintTool;
class CColour;

class CVideoDevicePseudo : public IVideoDevice
{
public:
   CVideoDevicePseudo(const CSizeI &resolution);
   ~CVideoDevicePseudo();
   
   DeviceType type() const override;
   IPaintSurface *createPaintSurface() override;
   IPaintDevice *createPaintDevice(IPaintSurface *paintSurface) const override;
   CPaintTool *getScreenPaintTool() const override;
   bool start(const CColour *colour = NULL) override;
   bool end() override;
private:
   CSizeI m_resolution;
};

#endif // CVIDEODEVICEPSEUDO_H
