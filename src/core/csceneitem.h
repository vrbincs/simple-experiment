#ifndef CSCENEITEM_H
   #define CSCENEITEM_H

#include <crect.h>
#include <set>
#include <deque>

class CPaintTool;
class CSceneItemPriv;
class CEvent;
class CScene;

/**
 * \class The base class that represents a graphical item. It allows to
 * build a tree of items in child parent manner. It implements the
 * composite pattern.
 */
class CSceneItem
{
public:
   /**
    * \brief constructor
    */
   CSceneItem(CSceneItem *parent = NULL);
   
   /**
    * \brief virtual destructor
    */
   virtual ~CSceneItem();
   
   /**
    * \brief Every object has position and size. This is the essential
    * information for the optimizer to only updates certain parts of
    * the visible drawing region and not the entire one.
    */
   virtual CRectF itemRegion() const = 0;
   
   /**
    * \brief set parent
    * \return return true if the child was added successfully to the
    * parent; false, otherwise.
    */
   bool setParent(CSceneItem *parent);
   
   /**
    * \brief return a pointer to the parent object;
    * \return return a pointer to the parent object;
    */
   CSceneItem *getParent() const;
      
   /**
    * \brief return relative position from the top parent
    */
   CPointF getPos() const;
   
   
   CPointF getPosition() const;
   CPointF &getPosition();
   void setPosition(const CPointF &pos);
   
   const std::set<CSceneItem *>::iterator childIteratorBegin() const;
   const std::set<CSceneItem *>::iterator childIteratorEnd() const;
   
   int32_t getZIndex() const;
   void setZIndex(int32_t zIndex);
   
   bool intersectsRect(const CRectF &rect);
   
   /**
    * \brief get a list of items that intersects with the given 
    * rectangle.
    * \param[in] rect: This rectangle is used to find items that
    * intersets with it.
    * \param[in] intersectedItems: A list of scene items that are 
    * intersecting with the rectangle
    * \return returns true if more than one item intersects with the
    * rectangle.
    */
   bool intersectsRect(const CRectF &rect, std::deque<CSceneItem *> &intersectedItems);
protected:
   /**
    * \brief This is the exciting part of the object where all painting
    * is carried out. Make sure that drawing is confined inside the 
    * region returned by itemRegion()
    */
   virtual void repaint(CPaintTool *paintTool, const CRectF &updateRegion) = 0;
   
   /**
    * \brief This tells the scene that this object needs to be
    * re-painted. This will add the item to the list of items that
    * needs to be repained only if it is in the current scene view.
    */
   void update();
   
   /**
    * \brief Get the pointer to the scene.
    */
   CScene *getScene() const;
   
   virtual bool onEvent(const CEvent &event);
private:
   CSceneItem *m_parent;
   CSceneItemPriv *m_sceneItemPriv;
   CPointF m_position;
   
   friend class CScene;
   /**
    * \brief Copy constructor is disable as we do not want an object to be part
    * two different composite objects
    */
   CSceneItem(const CSceneItem &copyObj);
   
   void setScene(CScene *scene);
   void repaintAll(CPaintTool *paintTool, const CRectF &updateRegion);
   
   CSceneItem *getRoot();
};

#endif // CSCENEITEM_H
