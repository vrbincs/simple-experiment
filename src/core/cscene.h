#ifndef CSCENE_H
   #define CSCENE_H

class CSceneItem;

#include <map>
#include <set>
#include <deque>

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
   
   bool itemExists(CSceneItem *item);
   
   CPointI getPosition() const;
   CSizeI getSize() const;
   
   void setSceneRect(const CRectI &sceneRect);
   
   /**
    * \brief a call to this function will repaint all visible items in
    * the view.
    */
   void redraw();
   
   void setBackgroundColor(const CColour &bgColour);
   
   std::deque<CSceneItem *> getCollisionItems(CSceneItem *);
   
   friend class CSceneItem;
protected:
   /**
    * \brief a CSceneItem calls this function when it needs to be 
    * repainted.
    * 
    * \param[in] a pointer to CSceneItem;
    */
   virtual void updateItem(CSceneItem *item);
   virtual void updateItem(CSceneItem *item, int32_t zIndexOld);
   
   bool removeItem(std::map<int32_t, std::set<CSceneItem *> > &container,
                   CSceneItem *item,
                   int32_t zIndex);
   
   void postEvent(CSceneItem *item, const CEvent &event);
   
   const std::map<int32_t, std::set<CSceneItem *> > &getItems() const;
   const std::map<int32_t, std::set<CSceneItem *> > &getViewableItems() const;
private:
   CRectI m_rect;
   std::map<int32_t, std::set<CSceneItem *> > m_items;                 /*< the container hold pointer to items. */
   std::map<int32_t, std::set<CSceneItem *> > m_viewableItems;         /*< a map of items inside theh viewable area. */
   
   CColour m_bgColour;
};

#endif // CSCENE_H
