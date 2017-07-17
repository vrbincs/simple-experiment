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
      if(!itemExists(item))
      {
         m_items[item->getZIndex()].insert(item);
         
         // Send message to all items that they were added to the scene.
         CEvent::UMessage msg;
         msg.customType = this;
         postEvent(item, CEvent(CEvent::EventTypeSceneAdded, msg, 0));
         
         // Update item on the screen.
         updateItem(item);
      }
      else
      {
         LOGGER_WARN("Trying to add an existing item to the scene.");
      }
   }
   else
   {
      LOGGER_WARN("Attempt to add an invalid item.");
   }
}

bool CScene::itemExists(CSceneItem *item)
{
   for(auto it0=m_items.begin(); it0!=m_items.end(); it0++)
   {
      if(it0->second.find(item) != it0->second.end())
      {
         return true;
      }
   }
   
   return false;
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
      
      if(item->intersectsRect(localRect))
      {
         auto item_t = viewableItems_t.find(item);
         if(item_t == viewableItems_t.end())
         {
            viewableItems_t.insert(item);
         }
      }
      else
      {
         viewableItems_t.erase(item);
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
      // Remove the item from the viewable items
      removeItem(m_viewableItems, item, zIndexOld);
      
      // Remove the item from the ordered map
      removeItem(m_items, item, zIndexOld),
      
      // Add item to the scene.
      addItem(item);
   }
}

bool CScene::removeItem(std::map<int32_t, std::set<CSceneItem *> > &container,
                        CSceneItem *item,
                        int32_t zIndex)
{
   int32_t n = 0;
   auto itemListAtZIndex_it = container.find(zIndex);
   
   if(itemListAtZIndex_it != container.end())
   {
       n = itemListAtZIndex_it->second.erase(item);
   }
   
   return n;
}

void CScene::postEvent(CSceneItem *item, const CEvent &event)
{
   item->onEvent(event);
   
   for(auto it0 = item->childIteratorBegin(); it0 != item->childIteratorEnd(); it0++)
   {
      postEvent(*it0, event);
   }
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
   
   // Viewable items are ordered by zIndex, so we traverse over all of
   // them, layer by layer
   for(auto it0 = m_viewableItems.begin(); it0 != m_viewableItems.end(); it0++)
   {
      for(auto it1 = it0->second.begin(); it1 != it0->second.end(); it1++)
      {
         (*it1)->repaintAll(paintTool, localRect);
      }
   }
   
   paintTool->restore();
}

const std::map<int32_t, std::set<CSceneItem *> > &CScene::getItems() const
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

std::deque<CSceneItem *> CScene::getCollisionItems(CSceneItem *item)
{
   std::deque<CSceneItem *> collidedItems;
   CRectF itemRegion = item->itemRegion();
   
   auto items_it = m_items.find(item->getZIndex());
   
   if(items_it != m_items.end())
   {
      for(auto it0 = items_it->second.begin(); it0 != items_it->second.end(); it0++)
      {
         if(item != *it0)
         {
            (*it0)->intersectsRect(itemRegion, collidedItems);
         }
      }
   }
   
   return collidedItems;
}
