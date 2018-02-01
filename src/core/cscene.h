#ifndef CSCENE_H
   #define CSCENE_H

class CSceneItem;

#include <map>
#include <set>
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
    * \param[in] item: pointer to a scene item;
    * 
    * \return returns true, if the \p item was successfully added to
    * the scene; false otherwise. An item already in scene hierachy will
    * not be added again and this function will return false.
    */
   bool addItem(CSceneItem *item);
   
   /**
    * \brief removed an item from the scene.
    * \param[in] item: pointer to a scene item;
    * 
    * \return returns true if the \p item was successfully removed from
    * the scene; false otherwise.
    */
   bool removeItem(CSceneItem *item);
   
   /**
    * \brief remove all items from the scene.
    */
   void removeAll();
   
   /**
    * \brief traverse over the graph in order to find the requested item.
    * \param[in] item: pointer to a scene item.
    * 
    * \return returns true if item exists; false otherwise.
    */
   bool itemExists(CSceneItem *item);
   
   /**
    * \brief get position of the scene window on the screen.
    * \brief returns position of the scene window on the screen.
    */
   CPointF getPosition() const;
   
   /**
    * \brief get size of the scene window.
    * \brief returns size of the scene window.
    */
   CSizeF getSize() const;
   
   /**
    * \brief set scene position
    * \param[in] scenePosition: scene position
    */
   void setScenePosition(const CPointF &scenePosition);
   
   /**
    * \brief a call to this function will repaint all visible items in
    * the view.
    */
   void redraw();
   
   void setBackgroundColor(const CColour &bgColour);
   
   void getCollisionItems(CSceneItem *item, std::vector<CSceneItem *> &collided);
   
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
