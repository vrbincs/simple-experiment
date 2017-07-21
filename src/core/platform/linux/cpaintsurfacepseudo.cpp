#include "cvideodevicepseudo.h"
#include "cpaintsurfacepseudo.h"

CPaintSurfacePseudo::CPaintSurfacePseudo(CVideoDevicePseudo *videoDevice)
   : m_bpp(0),
     m_width(0),
     m_height(0),
     m_videoDevice(videoDevice),
     m_pixelBuffer(NULL)
{
}

uint8_t CPaintSurfacePseudo::getBitsPerPixels() const
{
   return m_bpp;
}

uint32_t CPaintSurfacePseudo::getHeight() const
{
   return m_height;
}

uint32_t CPaintSurfacePseudo::getWidth() const
{
   return m_width;
}

void CPaintSurfacePseudo::lock()
{
}

void CPaintSurfacePseudo::unlock()
{
}

bool CPaintSurfacePseudo::isNull() const
{
   return (m_pixelBuffer == NULL);
}

IVideoDevice *CPaintSurfacePseudo::getVideoDevice() const
{
   return m_videoDevice;
}

bool CPaintSurfacePseudo::allocateFromBuffer(uint8_t *pixelBuffer,
                                             uint32_t width,
                                             uint32_t height,
                                             uint8_t depth)
{
   m_pixelBuffer = pixelBuffer;
   m_width = width;
   m_height = height;
   m_bpp = depth;
   
   return true;
}
                                
bool CPaintSurfacePseudo::allocateFromFile(const std::string &fileName,
                                           const std::string &type)
{
   return false;
}
