#include "logging.h"

#include "cpainttool.h"

CPaintTool::CPaintTool(CPixmap *pixmap)
   : m_pPixmap(NULL)
{
   start(m_pPixmap);
}

CPaintTool::~CPaintTool()
{
   end();
}

bool CPaintTool::start(CPixmap *pixmap)
{
   if(m_pPixmap)
   {
      if(pixmap)
      {
         m_pPixmap  = pixmap;
         return true;
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
   if(m_pPixmap)
   {
      IPaintDevice *paintDevice = m_pPixmap->getPaintDevice();
      
      if(paintDevice)
      {
         paintDevice->drawRect(rect);
      }
      else
      {
         LOGGER_WARN("No paint device associate with the pixamap has been found.");
      }
   }
   else
   {
      LOGGER_WARN("Unable to draw rectangle without valid pixmap.");
   }
}

bool CPaintTool::end()
{
   m_pPixmap = NULL;
   return true;
}
