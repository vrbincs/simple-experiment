#include "logging.h"

#include "ienginedevice.h"
#include "cevent.h"
#include "cpainttool.h"

#include "csceneitem.h"
#include "cscene.h"
#include "ctransform.h"

CScene::CScene(const CRectI &sceneRect)
   : m_rect(sceneRect)
{
}

void CScene::addItem(CSceneItem *item)
{
   if(item)
   {
      m_items.insert(item);
      
      // Send message to all items that they were added to the scene.
      CEvent::UMessage msg;
      msg.customType = this;
      postEvent(item, CEvent(CEvent::EventTypeSceneAdded, msg, 0));
      
      // Update item on the screen.
      updateItem(item);
   }
   else
   {
      LOGGER_WARN("Attempt to add an invalid item.");
   }
}

void CScene::updateItem(CSceneItem *item)
{
   if(item)
   {
      // nothing to do
   }
   else
   {
      LOGGER_WARN("Attempt to update an invalid item.");
   }
}

void CScene::postEvent(CSceneItem *item, const CEvent &event)
{
   item->onEvent(event);
}

void CScene::redraw()
{
   CPaintTool *paintTool = IEngineDevice::instance()->getVideoDevice()->getScreenPaintTool();
   
   paintTool->reset();
   
   CPaintTool::SPaintSettings paintSettings;
   paintSettings.bgColour = m_bgColour;
   
   CRectI localRect(0,0,m_rect.getWidth(), m_rect.getHeight());
   
   paintTool->setTransform(CTransform(m_rect.getPosition()));
   paintTool->setPaintSettings(paintSettings);
   paintTool->drawRect(localRect);
   paintTool->setClipArea(m_rect);
   
   for(auto it1 = m_items.begin(); it1 != m_items.end(); it1++)
   {
      if(localRect.intersects((*it1)->itemRegion()))
      {
         (*it1)->repaintAll(paintTool, localRect);
      }
   }
   
   paintTool->reset();
}

void CScene::setBackgroundColor(const CColour &bgColour)
{
   m_bgColour = bgColour;
}
