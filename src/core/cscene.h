#ifndef CSCENE_H
   #define CSCENE_H

class CSceneItem;

#include <map>
#include <set>
#include <deque>
#include <vector>

#include <crect.h>
#include <cpoint.h>
#include <csize.h>
#include <ccolour.h>
#include <celement.h>

class CEvent;

class CScene : public CElement
{
public:
   CScene(const CRectF &windowRect, 
          const CPointF &scenePosition = CPointF(0,0));
   
   ~CScene();
   /**
    * \brief adds an item to the scene.
    */
   bool addItem(CSceneItem *item);
   bool removeItem(CSceneItem *item);
   void removeAll();
   
   bool itemExists(CSceneItem *item);
   
   CPointF getPosition() const;
   CSizeF getSize() const;
   
   void setScenePosition(const CPointF &scenePosition);
   
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
   
   void reloadViewableItems();
   
   const std::map<int32_t, std::set<CSceneItem *> > &getItems() const;
   const std::map<int32_t, std::set<CSceneItem *> > &getViewableItems() const;
   
   std::vector<CSceneItem *> getViewableItems(int32_t zIndex) const;
private:
   CRectF m_windowRect;
   CRectF m_sceneRect;
   std::map<int32_t, std::set<CSceneItem *> > m_items;                 /*< the container hold pointer to items. */
   std::map<int32_t, std::set<CSceneItem *> > m_viewableItems;         /*< a map of items inside theh viewable area. */
   
   CColour m_bgColour;
};

#endif // CSCENE_H
