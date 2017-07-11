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

CPointI CScene::getPosition() const
{
   return CPointI();
}

CSizeI CScene::getSize() const
{
   return CSizeI();
}

void CScene::setSceneRect(const CRectI &sceneRect)
{
   m_rect = sceneRect;
}

void CScene::updateItem(CSceneItem *item)
{
   CRectF localRect(0,0,m_rect.getWidth(), m_rect.getHeight());
   
   if(item)
   {
      std::set<CSceneItem *> &viewableItems_t = m_viewableItems[item->getZIndex()];
      
      if(item->intersects(localRect))
      {
         auto item_t = viewableItems_t.find(item);
         if(item_t == viewableItems_t.end())
         {
            viewableItems_t.insert(item);
         }
         
         m_dirtyItems.insert(std::pair<CSceneItem *, CRectF>(item, item->itemRegion()));
      }
      else
      {
         viewableItems_t.erase(item);
         m_dirtyItems.erase(item);
      }
   }
   else
   {
      LOGGER_WARN("Attempt to update an invalid item.");
   }
}

void CScene::updateItem(CSceneItem *item, int32_t zIndexOld)
{
   if(item)
   {
      m_viewableItems[zIndexOld].erase(item);
      updateItem(item);
   }
}

void CScene::postEvent(CSceneItem *item, const CEvent &event)
{
   item->onEvent(event);
}

void CScene::redraw()
{
   CPaintTool *paintTool = IEngineDevice::instance()->getVideoDevice()->getScreenPaintTool();
   CPaintTool::SPaintSettings paintSettings;
   paintSettings.bgColour = m_bgColour;
   
   CRectF localRect(0,0,m_rect.getWidth(), m_rect.getHeight());
   
   paintTool->save();
   paintTool->setTransform(CTransform(m_rect.getPosition().toFloat()));
   paintTool->setPaintSettings(paintSettings);
   paintTool->drawRect(localRect);
   paintTool->setClipArea(m_rect.toFloat());
   
   for(auto it0 = m_viewableItems.begin(); it0 != m_viewableItems.end(); it0++)
   {
      for(auto it1 = it0->second.begin(); it1 != it0->second.end(); it1++)
      {
         (*it1)->repaintAll(paintTool, localRect);
      }
   }
   
   m_dirtyItems.clear();
   paintTool->restore();
}

const std::set<CSceneItem *> &CScene::getItems() const
{
   return m_items;
}

const std::map<int32_t, std::set<CSceneItem *> > &CScene::getViewableItems() const
{
   return m_viewableItems;
}

void CScene::setBackgroundColor(const CColour &bgColour)
{
   m_bgColour = bgColour;
}
