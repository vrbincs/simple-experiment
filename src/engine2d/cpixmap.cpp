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

CPixmap::CPixmap()
   : m_paintSurface(NULL)
{
   allocatePaintSurface(0,0,32);
}

CPixmap::CPixmap(int width, int height, int bpp)
   : m_paintSurface(NULL)
{
   allocatePaintSurface(width, height, bpp);
}

CPixmap::CPixmap(const CSizeI &size, int bpp)
   : m_paintSurface(NULL)
{
   allocatePaintSurface(size.getWidth(), size.getHeight(), bpp);
}

CPixmap::CPixmap(IPaintSurface *paintSurface)
   : m_paintSurface(paintSurface)
{
}

CPixmap::~CPixmap()
{
   delete m_paintSurface;
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

bool CPixmap::allocatePaintSurface(int width, int height, int bpp)
{
   IVideoDevice *videoDevice = getVideoDevice();
   
   if(videoDevice)
   {
      m_paintSurface = videoDevice->createPaintSurface();
      
      if(m_paintSurface)
      {
         if(m_paintSurface->allocate(width, height, bpp))
         {
            return true;
         }
         else
         {
            TLOG_ERROR("Out of memory. Unable to allocate paint surface.");
         }
      }
      else
      {
         TLOG_ERROR("Paint surface not initialized.");
      }
   }
   else
   {
      LOGGER_ERROR("Pixmap buffer cannot be created before CEngine2d is constructed.");
   }
   
   return false;
}

