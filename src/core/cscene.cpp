#include "logging.h"

#include "ienginedevice.h"
#include "cevent.h"
#include "cpainttool.h"

#include "csceneitem.h"
#include "cscene.h"
#include "ctransform.h"

CScene::CScene(const CRectF &windowRect, const CPointF &sceneOffset)
   :  m_windowRect(windowRect),
      m_sceneRect(sceneOffset, windowRect.getSize())
{
}

CScene::~CScene()
{
   removeAll();
}

bool CScene::addItem(CSceneItem *item)
{
   if(item)
   {
      if(!itemExists(item))
      {
         m_items[item->getZIndex()].insert(item);
         
         item->setScene(this);
         
         // Send message to all items that they were added to the scene.
         CEvent::UMessage msg;
         msg.customType = this;
         postEvent(item, CEvent(CEvent::EventTypeSceneAdded, msg, 0));
         
         // Update item on the screen.
         updateItem(item);
         
         return true;
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
   
   return false;
}

bool CScene::removeItem(CSceneItem *item)
{
   bool ok = false;
   
   if(item)
   {
      // remove the item from the view
      removeItem(m_viewableItems, item, item->getZIndex());
      
      // remove the item from the scene.
      removeItem(m_items, item, item->getZIndex());
      
      item->setScene(NULL);
   }
   
   return ok;
}

void CScene::removeAll()
{
   for(auto it0=m_items.begin(); it0!=m_items.end(); it0++)
   {
      for(auto it1=it0->second.begin(); it1!=it0->second.end(); it1++)
      {
         removeItem(*it1);
      }
   }
}

bool CScene::itemExists(CSceneItem *item)
{
   for(auto it0 = m_items.begin(); it0 != m_items.end(); it0++)
   {
      for(auto it1 = it0->second.begin(); it1 != it0->second.end(); it1++)
      {
         if((*it1)->hasDescendant(item))
         {
            return true;
         }
      }
   }
   
   return false;
}

CPointF CScene::getPosition() const
{
   return m_windowRect.getPosition();
}

CSizeF CScene::getSize() const
{
   return m_windowRect.getSize();
}

void CScene::setScenePosition(const CPointF &scenePosition)
{
   m_sceneRect = CRectF(scenePosition, m_windowRect.getSize());
   
   reloadViewableItems();
}

void CScene::updateItem(CSceneItem *item)
{
   if(item)
   {
      std::set<CSceneItem *> &viewableItems_t = m_viewableItems[item->getZIndex()];
      
      if(item->intersectsRect(m_sceneRect.toFloat()))
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

void CScene::reloadViewableItems()
{
   m_viewableItems.clear();
   
   for(auto it0 = m_items.begin(); it0 != m_items.end(); it0++)
   {
      for(auto it1 = it0->second.begin(); it1 != it0->second.end(); it1++)
      {
         updateItem(*it1);
      }
   }
}

void CScene::redraw()
{
   CPaintTool *paintTool = IEngineDevice::instance()->getVideoDevice()->getScreenPaintTool();
   CPaintTool::SPaintSettings paintSettings;
   paintSettings.bgColour = m_bgColour;
   
   CRectF localRect(CPointF(0,0), m_windowRect.getSize());
   
   paintTool->save();
   paintTool->setPaintSettings(paintSettings);
   paintTool->drawRect(m_windowRect);
   
   paintTool->setTransform(CTransform(m_windowRect.getPosition() - m_sceneRect.getPosition()));
   paintTool->setClipArea(m_windowRect);
   
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

std::vector<CSceneItem *> CScene::getViewableItems(int32_t zIndex) const
{
   std::vector<CSceneItem *> result;
   
   auto items_it = m_viewableItems.find(zIndex);
   if(items_it != m_viewableItems.end())
   {
      result.reserve(items_it->second.size());
      for(auto item_it = items_it->second.begin(); item_it != items_it->second.end(); item_it++)
      {
         result.push_back(*item_it);
      }
   }
   
   return result;
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
