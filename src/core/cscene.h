#ifndef CSCENE_H
   #define CSCENE_H

class CSceneItem;

#include <map>
#include <set>

#include <crect.h>
#include <cpoint.h>
#include <csize.h>
#include <ccolour.h>

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
   
   /**
    * \brief a call to this function will repaint all visible items in
    * the view.
    */
   void redraw();
   
   void setBackgroundColor(const CColour &bgColour);
   
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
   std::set<CSceneItem *> m_viewableItems; /*< The items inside theh viewable area. */
   CColour m_bgColour;
};

#endif // CSCENE_H
