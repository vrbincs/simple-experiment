#include "cdrawingtool.h"
#include "cgobject.h"

#include <map>

class CGObjectPriv
{
public:
   CGObjectPriv();
   
   bool addChild(CGObject *child)
   {
      return false;
   }
   
   bool removeChild(CGObject *child)
   {
      return false;
   }
   
   std::map<CGObject *, CGObject *> m_children;
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
   
   if(parent)
   {
      if(!parent->m_cgobjectPriv->addChild(this))
      {
         return false;
      }
   }
   
   return true;
}
