#ifndef CSCENE_H
   #define CSCENE_H

class CSceneItem;

#include <crect.h>
#include <cpoint.h>
#include <csize.h>
#include <map>
#include <set>

class CEvent;

class CScene
{
public:
   CScene(const CRectI &sceneRect);
   
   /**
    * \brief adds an item to the scene.
    */
   void addItem(CSceneItem *item);
   
   CPointI getPosition() const;
   CSizeI getSize() const;
   
   void redraw();
   
   friend class CSceneItem;
protected:
   /**
    * \brief a CSceneItem calls this function when it needs to be 
    * repainted.
    * 
    * \param[in] a pointer to CSceneItem;
    */
   void updateItem(CSceneItem *item);
   
   void postEvent(CSceneItem *item, const CEvent &event);
private:
   CRectI m_rect;
   
   std::set<CSceneItem *> m_items; /*< the container hold pointer to items. */
   std::map<CSceneItem *, CRectI> *m_dirtyRegions; /*< this is used for update
                                                     of dirty regions */
   std::map<CSceneItem *, CRectI> *m_dirtyObjects;  /*< Objects that need to be
                                                       repainted */
};

#endif // CSCENE_H
