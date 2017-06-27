#include "logging.h"

#include "ienginedevice.h"
#include "cevent.h"

#include "csceneitem.h"
#include "cscene.h"

CScene::CScene(const CRectI &sceneRect)
   : m_rect(sceneRect),
     m_dirtyRegions(new std::map<CSceneItem *, CRectI>()),
     m_dirtyObjects(new std::map<CSceneItem *, CRectI>())
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
      auto itemIt = m_dirtyObjects->find(item);
      if(itemIt != m_dirtyObjects->end())
      {
         m_dirtyObjects->erase(itemIt);
      }
      
      m_dirtyObjects->insert(std::pair<CSceneItem *, CRectI>(item, item->itemRegion()));
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
   
   // repaint the dirty areas
   for(auto it = m_dirtyRegions->begin(); it != m_dirtyRegions->end();)
   {
      it++;
   }
   
   // at the end, repaint the objects
   for(auto it = m_dirtyObjects->begin(); it != m_dirtyObjects->end(); it++)
   {
      it->first->repaint(paintTool, it->second);
   }
   
   // swap the pointers of of dirty regions and dirty objects.
   m_dirtyRegions->clear();
   auto tmpDirtyRegions = m_dirtyRegions;
   m_dirtyRegions = m_dirtyObjects;
   m_dirtyObjects = tmpDirtyRegions;
}
