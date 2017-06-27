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
      : m_scene(NULL)
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

CPointI CSceneItem::getPos() const
{
   CPointI position = m_position;
   
   const CSceneItem *parent = this;
   while((parent->getParent() != NULL))
   {
      position += parent->getPosition();
   }
   
   return position;
}

CPointI CSceneItem::getPosition() const
{
   return m_position;
}

CPointI &CSceneItem::getPosition()
{
   return m_position;
}

void CSceneItem::setPosition(const CPointI &pos)
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

void CSceneItem::update()
{
   CScene *scene = getScene();
   
   if(scene)
   {
      scene->updateItem(this);
   }
}

CScene *CSceneItem::getScene() const
{
   return m_sceneItemPriv->m_scene;
}

bool CSceneItem::onEvent(const CEvent &event)
{
   switch(event.type())
   {
      case CEvent::EventTypeSceneAdded:
      {
         m_sceneItemPriv->m_scene = reinterpret_cast<CScene *>(event.message().customType);
      }
      break;
      default:
      break;
   }
   return false;
}

void CSceneItem::repaintAll(CPaintTool *paintTool, const CRectI &updateRegion)
{
   // First repaint the parent.
   repaint(paintTool, updateRegion);
   
   CTransform &transform = paintTool->getTransform();
   transform.translate(getPosition());
   
   for(auto it1 = childIteratorBegin(); it1 != childIteratorEnd(); it1++)
   {
      (*it1)->repaintAll(paintTool, updateRegion);
   }
}
