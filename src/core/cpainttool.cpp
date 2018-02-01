#include <stack>

#include "logging.h"
LOGGING_INIT("CEngine2D")

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
      CTransform m_transform;
      CRectF m_clipArea;
   };
   
   CRectF clipRect(CPointF &position,
                   const CRectF &srcRect)
   {
      CRectF clipped = CRectF(0,0,srcRect.getWidth(), srcRect.getHeight());
      position += m_paintToolSettings.m_transform.getPosition();
      clipped.translate(position);
      
      CRectF clippedGlob = clipped.intersection(m_paintToolSettings.m_clipArea);
      CPointF offset((clippedGlob.getX()-clipped.getX()),
                     (clippedGlob.getY()-clipped.getY()));
      
      clipped = CRectF(offset + srcRect.getPosition(), clippedGlob.getSize());
      position += offset;
      
      return clipped;
   }
   
   CRectF tranformRect(const CRectF &rect)
   {
      CRectF rectRet = rect;
      
      rectRet.translate(m_paintToolSettings.m_transform.getPosition());
      
      return rectRet;
   }
   
   void saveSettings()
   {
      m_savedSettings.push(m_paintToolSettings);
   }
   
   void restoreSettings()
   {
      if(!m_savedSettings.empty())
      {
         m_paintToolSettings = m_savedSettings.top();
         m_savedSettings.pop();
      }
      else
      {
         LOGGER_INFO("Unable to restore paint tool settings.");
      }
   }
   
   void setClipArea(const CRectF &clipRect)
   {
      m_paintToolSettings.m_clipArea = clipRect;
   }
   
   SPaintToolSettings m_paintToolSettings;   
   std::stack<SPaintToolSettings> m_savedSettings;
};

CPaintTool::CPaintTool(CPixmap *pixmap)
   : m_pPaintDevice(NULL),
     m_paintToolPriv(new CPaintToolPriv())
{
   if(pixmap)
   {
      m_paintToolPriv->m_paintToolSettings.m_clipArea = CRectF(0,0,pixmap->getWidth(), pixmap->getHeight());
      start(pixmap);
   }
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
   m_paintToolPriv->saveSettings();
}

void CPaintTool::restore()
{
   m_paintToolPriv->restoreSettings();
}

void CPaintTool::setPaintSettings(const SPaintSettings &paintSettings)
{
   m_paintToolPriv->m_paintToolSettings.m_paintSettings = paintSettings;
}

void CPaintTool::setClipArea(const CRectF &clip)
{
   m_paintToolPriv->setClipArea(clip);
}

void CPaintTool::drawRect(const CRectF &rect)
{
   if(m_pPaintDevice)
   {
      m_pPaintDevice->drawRect(m_paintToolPriv->tranformRect(rect), 
                               m_paintToolPriv->m_paintToolSettings.m_paintSettings.bgColour);
   }
   else
   {
      LOGGER_WARN("No paint device associate with the pixamap has been found.");
   }
}

void CPaintTool::drawPixmap(const CPixmap &pixmap,
                            const CPointF &pos,
                            const CRectF *srcRect)
{
   
   if(m_pPaintDevice)
   {
      CRectF sourceRect(CPointF(0,0), pixmap.getSize().toFloat());
      if(srcRect)
      {
         sourceRect = *srcRect;
      }
      
      CPointF posTmp = pos;
      CRectF clippedRect = m_paintToolPriv->clipRect(posTmp, sourceRect);
      
      m_pPaintDevice->drawSurface(*pixmap.getPaintSurface(), 
                                  posTmp,
                                  &clippedRect);
   }
   else
   {
      LOGGER_WARN("No paint device associate with the pixamap has been found.");
   }
}

void CPaintTool::drawText(const std::string &text, const CRectF &rect)
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

void CPaintTool::setTransform(const CTransform &transform)
{
   m_paintToolPriv->m_paintToolSettings.m_transform = transform;
}

CTransform CPaintTool::getTransform() const
{
   return m_paintToolPriv->m_paintToolSettings.m_transform;
}

CTransform &CPaintTool::getTransform()
{
   return m_paintToolPriv->m_paintToolSettings.m_transform;
}


