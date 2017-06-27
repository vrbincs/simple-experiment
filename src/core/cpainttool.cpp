#include "logging.h"

#include "ivideodevice.h"
#include "ipaintsurface.h"
#include "ipaintdevice.h"
#include "cpainttool.h"
#include "cpixmap.h"
#include "ccolour.h"
#include "ctransform.h"

class CPaintToolPriv
{
public:
   struct SPaintToolSettings
   {
      CPaintTool::SPaintSettings m_paintSettings;
      CTransfrom m_transform;
   };
   
   SPaintToolSettings m_paintToolSettings;
};

CPaintTool::CPaintTool(CPixmap *pixmap)
   : m_pPaintDevice(NULL),
     m_paintToolPriv(new CPaintToolPriv())
{
   start(pixmap);
}

CPaintTool::CPaintTool(IPaintDevice *paintDevice)
   : m_pPaintDevice(paintDevice),
     m_paintToolPriv(new CPaintToolPriv())
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

bool CPaintTool::end()
{
   delete m_pPaintDevice;
   m_pPaintDevice = NULL;
   
   return true;
}

void CPaintTool::save()
{
   
}

void CPaintTool::reset()
{
   m_paintToolPriv->m_paintToolSettings = CPaintToolPriv::SPaintToolSettings();
}

void CPaintTool::setPaintSettings(const SPaintSettings &paintSettings)
{
   m_paintToolPriv->m_paintToolSettings.m_paintSettings = paintSettings;
}

void CPaintTool::drawRect(const CRectI &rect)
{
   if(m_pPaintDevice)
   {
      m_pPaintDevice->drawRect(rect, 
                               m_paintToolPriv->m_paintToolSettings.m_paintSettings.bgColour);
   }
   else
   {
      LOGGER_WARN("No paint device associate with the pixamap has been found.");
   }
}

void CPaintTool::drawPixmap(const CPixmap &pixmap,
                            const CPointI &pos,
                            const CRectI *srcRect)
{
   if(m_pPaintDevice)
   {
      CPointI posTmp = pos;
      posTmp += m_paintToolPriv->m_paintToolSettings.m_transform.getPosition();
      m_pPaintDevice->drawSurface(*pixmap.getPaintSurface(), 
                                  posTmp,
                                  srcRect);
   }
   else
   {
      LOGGER_WARN("No paint device associate with the pixamap has been found.");
   }
}

void CPaintTool::drawText(const std::string &text, const CRectI &rect)
{
   if(m_pPaintDevice)
   {
      m_pPaintDevice->drawText(text, rect, CColour(255,0,0));
   }
   else
   {
      LOGGER_WARN("No paint device associate with the pixamap has been found.");
   }
}

void CPaintTool::setTransform(const CTransfrom &transform)
{
   m_paintToolPriv->m_paintToolSettings.m_transform = transform;
}

CTransfrom CPaintTool::getTransform() const
{
   return m_paintToolPriv->m_paintToolSettings.m_transform;
}

CTransfrom &CPaintTool::getTransform()
{
   return m_paintToolPriv->m_paintToolSettings.m_transform;
}


