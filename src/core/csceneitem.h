#ifndef CSCENEITEM_H
   #define CSCENEITEM_H

#include <crect.h>

class CPaintTool;
class CSceneItemPriv;
class CEvent;

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
   virtual CRectI itemRegion() const = 0;
   
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
protected:
   /**
    * \brief This is the exciting part of the object where all painting
    * is carried out. Make sure that drawing is confined inside the 
    * region returned by itemRegion()
    */
   virtual void repaint(CPaintTool *paintTool) = 0;
   
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
   
   virtual void onEvent(CEvent &event);
private:
   CSceneItem *m_parent;
   CSceneItemPriv *m_sceneItemPriv;
   
   friend class CScene;
   /**
    * \brief Copy constructor is disable as we do not want an object to be part
    * two different composite objects
    */
   CSceneItem(const CSceneItem &copyObj);
   
   void setScene(CScene *scene);
};

#endif // CSCENEITEM_H
