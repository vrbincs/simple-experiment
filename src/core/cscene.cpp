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
   CRectF localRect(0,0,m_rect.getWidth(), m_rect.getHeight());
   
   if(item)
   {
      if(localRect.intersects(item->itemRegion()))
      {
         m_viewableItems.insert(item);
      }
      else
      {
         m_viewableItems.erase(item);
      }
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
   LOGGER_INFO(m_viewableItems.size());
   
   CPaintTool *paintTool = IEngineDevice::instance()->getVideoDevice()->getScreenPaintTool();
   CPaintTool::SPaintSettings paintSettings;
   paintSettings.bgColour = m_bgColour;
   
   CRectF localRect(0,0,m_rect.getWidth(), m_rect.getHeight());
   
   paintTool->save();
   paintTool->setTransform(CTransform(m_rect.getPosition().toFloat()));
   paintTool->setPaintSettings(paintSettings);
   paintTool->drawRect(localRect);
   paintTool->setClipArea(m_rect.toFloat());
   
   for(auto it1 = m_viewableItems.begin(); it1 != m_viewableItems.end(); it1++)
   {
      (*it1)->repaintAll(paintTool, localRect);
   }
   
   paintTool->restore();
}

void CScene::setBackgroundColor(const CColour &bgColour)
{
   m_bgColour = bgColour;
}
