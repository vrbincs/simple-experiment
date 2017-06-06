#include "logging.h"

#include "cengine2d.h"
#include "cpixmap.h"

static IVideoDevice *getVideoDevice()
{
   IVideoDevice *videoDevice = NULL;
   IEngineDevice *engine = CEngine2d::instance();
   
   if(engine)
   {
      videoDevice = engine->getVideoDevice();
   }
   
   return videoDevice;
}

CPixmap::CPixmap(int width, int height, int bpp)
   : m_size(width, height),
     m_bitsPerPixel(bpp),
     m_pixelBuffer(NULL)
{
   allocateBuffer();
}

CPixmap::CPixmap(const CSizeI &size, int bpp)
   : m_size(size),
     m_bitsPerPixel(bpp),
     m_pixelBuffer(NULL)
{
   allocateBuffer();
}

CPixmap::~CPixmap()
{
   delete m_pixelBuffer;
}

const void *CPixmap::getBuffer()
{
   if(m_pixelBuffer)
   {
      return m_pixelBuffer->getBuffer();
   }
   
   return NULL;
}
   
CSizeI CPixmap::getSize() const
{
   return m_size;
}

int CPixmap::getWidth() const
{
   return m_size.getWidth();
}

int CPixmap::getHeight() const
{
   return m_size.getHeight();
}

int CPixmap::getBpp() const
{
   return m_bitsPerPixel;
}

CPixelBuffer *CPixmap::getPixelBuffer()
{
   return m_pixelBuffer;
}

bool CPixmap::allocateBuffer()
{
   if(getVideoDevice())
   {
      m_pixelBuffer = getVideoDevice()->allocatePixmap(getWidth(), 
                                                       getHeight(),
                                                       getBpp());
   }
   else
   {
      LOGGER_ERROR("Pixmap buffer cannot be created before CEngine2d is constructed.");
   }
   
   return m_pixelBuffer;
}

