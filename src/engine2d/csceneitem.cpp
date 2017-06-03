#include <map>


#include "logging.h"

#include "cdrawingtool.h"
#include "cevent.h"
#include "cscene.h"
#include "csceneitem.h"

class CSceneItemPriv
{
public:
   CSceneItemPriv()
      : m_scene(NULL)
   {
   }
   
   bool addChild(CSceneItem *child)
   {
      auto it_child = m_children.find(child);
      if(it_child == m_children.end())
      {
         m_children.insert(std::pair<CSceneItem *, CSceneItem *>(child, child));
         return true;
      }
      else
      {
         return false;
      }
   }
   
   bool removeChild(CSceneItem *child)
   {
      return m_children.erase(child);
   }
   
   CScene *getScene() const;
   
   std::map<CSceneItem *, CSceneItem *> m_children;
   CScene *m_scene;
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

void CSceneItem::update()
{
   CScene *scene = getScene();
   
   if(scene)
   {
      scene->updateObject(this);
   }
}

CScene *CSceneItem::getScene() const
{
   return m_sceneItemPriv->m_scene;
}

void CSceneItem::onEvent(CEvent &event)
{
}
