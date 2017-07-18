#include <set>

#include "logging.h"

#include "cevent.h"
#include "cscene.h"
#include "csceneitem.h"
#include "ctransform.h"
#include "cpainttool.h"

class CSceneItemPriv
{
public:
   CSceneItemPriv()
      : m_scene(NULL),
        m_zIndex(0)
   {
   }
   
   bool addChild(CSceneItem *child)
   {
      m_children.insert(child);
      return true;
   }
   
   bool removeChild(CSceneItem *child)
   {
      return m_children.erase(child);
   }
   
   CScene *getScene() const;
   
   std::set<CSceneItem *> m_children;
   CScene *m_scene;
   int32_t m_zIndex;
   friend class CSceneItem;
};

static CSceneItemPriv *m_cgobject = new CSceneItemPriv();


CSceneItem::CSceneItem(CSceneItem *parent)
   : m_parent(NULL),
     m_sceneItemPriv(new CSceneItemPriv())
{
   setParent(parent);
}

CSceneItem::~CSceneItem()
{
   if(m_sceneItemPriv->m_scene)
   {
      m_sceneItemPriv->m_scene->removeItem(this);
   }
   
   for(auto it0 = m_sceneItemPriv->m_children.begin(); it0 != m_sceneItemPriv->m_children.end(); it0++)
   {
      delete *it0;
   }
}

bool CSceneItem::setParent(CSceneItem *parent)
{
   if(m_parent)
   {
      m_parent->m_sceneItemPriv->removeChild(this);
   }
   
   m_parent = NULL;
   
   if(parent)
   {
      if(!parent->m_sceneItemPriv->addChild(this))
      {
         return false;
      }
   }
   
   m_parent = parent;
   
   return true;
}

CSceneItem *CSceneItem::getParent() const
{
   return m_parent;
}

CPointF CSceneItem::getPos() const
{
   CPointF position;
   
   const CSceneItem *parent = this;
   do
   {
      position += parent->getPosition();
      
   }while((parent = parent->getParent()) != NULL);
   
   return position;
}

CPointF CSceneItem::getPosition() const
{
   return m_position;
}

CPointF &CSceneItem::getPosition()
{
   return m_position;
}

void CSceneItem::setPosition(const CPointF &pos)
{
   m_position = pos;
   update();
}

const std::set<CSceneItem *>::iterator CSceneItem::childIteratorBegin() const
{
   return m_sceneItemPriv->m_children.begin();
}
const std::set<CSceneItem *>::iterator CSceneItem::childIteratorEnd() const
{
   return m_sceneItemPriv->m_children.end();
}

int32_t CSceneItem::getZIndex() const
{
   return m_sceneItemPriv->m_zIndex;
}

void CSceneItem::setZIndex(int32_t zIndex)
{
   int32_t zIndex_t = m_sceneItemPriv->m_zIndex;
   m_sceneItemPriv->m_zIndex = zIndex;
   
   CScene *scene = getScene();
   if(scene)
   {
      scene->updateItem(this, zIndex_t);
   }
}

bool CSceneItem::intersectsRect(const CRectF &rect)
{
   CRectF region = CRectF(getPos(), itemRegion().getSize());
   
   if(region.intersects(rect))
   {
      return true;
   }
   
   for(auto it = childIteratorBegin(); it != childIteratorEnd(); it++)
   {
      if((*it)->intersectsRect(rect))
      {
         return true;
      }
   }
   
   return false;
}

bool CSceneItem::intersectsRect(const CRectF &rect, 
                                std::deque<CSceneItem *> &itersectedItems)
{
   CRectF region = itemRegion();
   region.setPosition(getPos());
   
   if(itemRegion().intersects(rect))
   {
      itersectedItems.push_back(this);
   }
   
   for(auto it = childIteratorBegin(); it != childIteratorEnd(); it++)
   {
      (*it)->intersectsRect(rect, itersectedItems);
   }
   
   return itersectedItems.size();
}

void CSceneItem::update()
{
   CScene *scene = getScene();
   
   if(scene)
   {
      scene->updateItem(getRoot());
   }
   else
   {
      LOGGER_TRACE("The item has not been added to the scene yet.");
   }
}

CScene *CSceneItem::getScene() const
{
   return m_sceneItemPriv->m_scene;
}

bool CSceneItem::onEvent(const CEvent &event)
{
   return false;
}

void CSceneItem::setScene(CScene *scene)
{
   m_sceneItemPriv->m_scene = scene;
}

void CSceneItem::repaintAll(CPaintTool *paintTool, const CRectF &updateRegion)
{
   // First repaint the parent.
   repaint(paintTool, updateRegion);
   paintTool->save();
   CTransform &transform = paintTool->getTransform();
   transform.translate(getPosition());
   
   for(auto it1 = childIteratorBegin(); it1 != childIteratorEnd(); it1++)
   {
      (*it1)->repaintAll(paintTool, updateRegion);
   }
   paintTool->restore();
}

CSceneItem *CSceneItem::getRoot()
{
   CSceneItem *item = this;
   
   while(item->getParent() != NULL)
   {
      item = item->getParent();
   }
   
   return item;
}
