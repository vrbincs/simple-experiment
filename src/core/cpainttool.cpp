#include "logging.h"

#include "ivideodevice.h"
#include "ipaintsurface.h"
#include "cpainttool.h"

CPaintTool::CPaintTool(CPixmap *pixmap)
   : m_pPaintDevice(NULL)
{
   start(pixmap);
}

CPaintTool::~CPaintTool()
{
   end();
}

bool CPaintTool::start(CPixmap *pixmap)
{
   if(!m_pPaintDevice)
   {
      if(pixmap)
      {
         IVideoDevice *videoDevice = pixmap->getVideoDevice();
         
         if(videoDevice)
         {
            m_pPaintDevice = videoDevice->createPaintDevice(pixmap->getPaintSurface());
            
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

bool CPaintTool::end()
{
   delete m_pPaintDevice;
   m_pPaintDevice = NULL;
   
   return true;
}
