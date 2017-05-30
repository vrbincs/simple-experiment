#include <map>

#include "logging.h"

#include "cdrawingtool.h"
#include "cevent.h"
#include "cgobject.h"

class CGObjectPriv
{
public:
   CGObjectPriv()
      : m_scene(NULL)
   {
   }
   
   bool addChild(CGObject *child)
   {
      auto it_child = m_children.find(child);
      if(it_child == m_children.end())
      {
         m_children.insert(std::pair<CGObject *, CGObject *>(child, child));
         return true;
      }
      else
      {
         return false;
      }
   }
   
   bool removeChild(CGObject *child)
   {
      return m_children.erase(child);
   }
   
   CScene *getScene() const;
   
   std::map<CGObject *, CGObject *> m_children;
   CScene *m_scene;
   friend class CGObject;
};

static CGObjectPriv *m_cgobject = new CGObjectPriv();


CGObject::CGObject(CGObject *parent)
   : m_parent(NULL),
     m_cgobjectPriv(new CGObjectPriv())
{
   setParent(parent);
}

CGObject::~CGObject()
{
}

bool CGObject::setParent(CGObject *parent)
{
   if(m_parent)
   {
      m_parent->m_cgobjectPriv->removeChild(this);
   }
   
   m_parent = NULL;
   
   if(parent)
   {
      if(!parent->m_cgobjectPriv->addChild(this))
      {
         return false;
      }
   }
   
   m_parent = parent;
   
   return true;
}

CGObject *CGObject::getParent() const
{
   return m_parent;
}

void CGObject::update()
{
   CScene *scene = getScene();
   
   if(scene)
   {
      scene->updateObject(this);
   }
}

CScene *CGObject::getScene() const
{
   return m_cgobjectPriv->m_scene;
}

void CGObject::onEvent(CEvent &event)
{
}
