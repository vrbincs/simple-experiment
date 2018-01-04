#include "logging.h"

#include "cengine2d.h"
#include "ipaintsurface.h"
#include "cpixmap.h"

static IVideoDevice *acquireVideoDevice()
{
   IVideoDevice *videoDevice = NULL;
   IEngineDevice *engine = CEngine2d::instance();
   
   if(engine)
   {
      videoDevice = engine->getVideoDevice();
   }
   
   return videoDevice;
}

CPixmap::CPixmap()
   : m_paintSurface(NULL)
{
   allocatePaintSurface(NULL, 0, 0, 32);
}

CPixmap::CPixmap(uint8_t *pixelBuffer, int width, int height, int bpp)
   : m_paintSurface(NULL)
{
   allocatePaintSurface(pixelBuffer, width, height, bpp);
}

CPixmap::CPixmap(uint8_t *pixelBuffer, const CSizeI &size, int bpp)
   : m_paintSurface(NULL)
{
   allocatePaintSurface(pixelBuffer, size.getWidth(), size.getHeight(), bpp);
}

CPixmap::CPixmap(IPaintSurface *paintSurface)
   : m_paintSurface(paintSurface)
{
}

CPixmap::CPixmap(const std::string &fileName, const std::string &fileType)
{
   IVideoDevice *videoDevice = acquireVideoDevice();
   
   if(videoDevice)
   {
      m_paintSurface = videoDevice->createPaintSurface();
      
      if(m_paintSurface)
      {
         if(m_paintSurface->allocateFromFile(fileName, fileType))
         {
            return;
         }
         else
         {
            LOGGER_WARN("Unable to allocate surface from file. fileName=" << fileName << ", fileType=" << fileType );
         }
      }
      
      free();
   }
   else
   {
      LOGGER_ERROR("Unable to acquire a video device.");
   }
}

CPixmap::~CPixmap()
{
   free();
}

CSizeI CPixmap::getSize() const
{
   return CSizeI(m_paintSurface->getWidth(), m_paintSurface->getHeight());
}

int CPixmap::getWidth() const
{
   return m_paintSurface->getWidth();
}

int CPixmap::getHeight() const
{
   return m_paintSurface->getHeight();
}

int CPixmap::getBpp() const
{
   return m_paintSurface->getBitsPerPixels();
}

void CPixmap::free()
{
   delete m_paintSurface;
   m_paintSurface = NULL;
}

bool CPixmap::allocatePaintSurface(uint8_t *pixelBuffer,
                                   int width,
                                   int height,
                                   int bpp)
{
   IVideoDevice *videoDevice = acquireVideoDevice();
   
   if(videoDevice)
   {
      m_paintSurface = videoDevice->createPaintSurface();
      
      if(m_paintSurface)
      {
         if(m_paintSurface->allocateFromBuffer(pixelBuffer, width, height, bpp))
         {
            return true;
         }
         else
         {
            LOGGER_ERROR("Out of memory. Unable to allocate paint surface.");
         }
      }
      else
      {
         LOGGER_ERROR("Paint surface not initialized.");
      }
      
     free();
   }
   else
   {
      LOGGER_ERROR("Pixmap buffer cannot be created before CEngine2d is constructed.");
   }
   
   return false;
}

bool CPixmap::isNull() const
{
   return m_paintSurface ? false : true;
}

CColour CPixmap::getPixelAt(const CPointI &pos)
{
   return m_paintSurface->getPixelAt(pos);
}

IPaintSurface *CPixmap::getPaintSurface() const
{
   return m_paintSurface;
}
