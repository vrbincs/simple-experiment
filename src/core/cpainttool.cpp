#include "logging.h"

#include "ivideodevice.h"
#include "ipaintsurface.h"
#include "ipaintdevice.h"
#include "cpainttool.h"
#include "cpixmap.h"

CPaintTool::CPaintTool(CPixmap *pixmap)
   : m_pPaintDevice(NULL)
{
   start(pixmap);
}

CPaintTool::CPaintTool(IPaintDevice *paintDevice)
   : m_pPaintDevice(paintDevice)
{
}

CPaintTool::~CPaintTool()
{
   end();
}

bool CPaintTool::start(CPixmap *pixmap)
{
   if(!m_pPaintDevice)
   {
      IPaintSurface *paintSurface = pixmap->getPaintSurface();
      if(paintSurface)
      {
         IVideoDevice *videoDevice = paintSurface->getVideoDevice();
         
         if(videoDevice)
         {
            m_pPaintDevice = videoDevice->createPaintDevice(paintSurface);
            
            if(m_pPaintDevice)
            {
               return true;
            }
            else
            {
               LOGGER_WARN("Error while creating a paint device.");
            }
         }
         else
         {
            LOGGER_WARN("Unable to get video device.");
         }
      }
      else
      {
         LOGGER_ERROR("Invalid pixmap");
      }
   }
   else
   {
      LOGGER_ERROR("This paint tool has already associated pixmap.");
   }
   
   return false;
}

void CPaintTool::drawRect(const CRectI &rect)
{
   if(m_pPaintDevice)
   {
      m_pPaintDevice->drawRect(rect);
   }
   else
   {
      LOGGER_WARN("No paint device associate with the pixamap has been found.");
   }
}

void CPaintTool::drawPixmap(const CPixmap &pixmap, const CPointI &pos)
{
   if(m_pPaintDevice)
   {
      m_pPaintDevice->drawSurface(*pixmap.getPaintSurface(), pos);
   }
   else
   {
      LOGGER_WARN("No paint device associate with the pixamap has been found.");
   }
}

bool CPaintTool::end()
{
   delete m_pPaintDevice;
   m_pPaintDevice = NULL;
   
   return true;
}
